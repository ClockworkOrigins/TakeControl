/*
	This file is part of TakeControl.

    TakeControl is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TakeControl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TakeControl.  If not, see <http://www.gnu.org/licenses/>.
 */
// Copyright 2020 Clockwork Origins

#include "MainWindow.h"

#include "CharacterTab.h"
#include "DialogTab.h"
#include "NewProjectDialog.h"
#include "TakeControlConfig.h"
#include "TranslateableTextTab.h"

#include "core/CharacterPool.h"
#include "core/Config.h"
#include "core/ConditionFactory.h"
#include "core/DialogPool.h"
#include "core/IGamePlugin.h"
#include "core/NodeFactory.h"
#include "core/Project.h"
#include "core/TranslateableTextPool.h"

#include "gui/NodeItemFactory.h"
#include "gui/PropertyItemFactory.h"

#include "plugins/PluginLoader.h"

#include "utils/UndoStack.h"

#include <QApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>

using namespace tc::client;
using namespace tc::core;
using namespace tc::gui;
using namespace tc::plugins;
using namespace tc::utils;

MainWindow::MainWindow() : _pluginLoader(new PluginLoader()), _characterTab(nullptr), _dialogTab(nullptr) {
	adjustTitle();

	createFileMenu();
	createEditMenu();

	createTabs();

	initConnections();

	restoreSettings();
}

MainWindow::~MainWindow() {
	saveSettings();
}

void MainWindow::createNewProject() {
	const auto pluginList = _pluginLoader->getGamePlugins();

	QStringList gameList;

	for (const auto * plugin : pluginList) {
		gameList.append(plugin->getName());
	}
	
	NewProjectDialog dlg(gameList, this);

	_project = dlg.createNewProject();

	if (!_project) return;

	CharacterPool::instance()->setCharacters({});
	DialogPool::instance()->setDialogs({});
	TranslateableTextPool::instance()->setTranslateableTexts({});

	updatePlugin();
	
	emit projectLoaded();
}

void MainWindow::saveProject() {
	if (!_project) return;

	const auto characterList = CharacterPool::instance()->getCharacters();
	const auto dialogList = DialogPool::instance()->getDialogs();
	const auto textList = TranslateableTextPool::instance()->getTranslateableTexts();

	_project->setCharacters(characterList);
	_project->setDialogs(dialogList);
	_project->setTexts(textList);
	
	_project->save();

	UndoStack::instance()->setClean();
}

void MainWindow::loadProject() {
	QFileDialog dialog(this);
	dialog.setFilter(QDir::Filter::Files);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter("*.json");
	
	if (!dialog.exec()) return;

	loadProject(dialog.selectedFiles()[0]);
}

void MainWindow::exportProject() {
	if (!_project) return;

	const auto * usedPlugin = _pluginLoader->getGamePlugin(_project->getType());
	
	if (!usedPlugin) return;

	const auto exportSuccessful = usedPlugin->exportProject(_project);
	Q_UNUSED(exportSuccessful) // TODO: add some error handling
}

void MainWindow::createFileMenu() {
	auto * fileMenu = new QMenu(QApplication::tr("File"), this);

	auto * newProject = fileMenu->addAction(QApplication::tr("NewProject"));
	newProject->setShortcut(QKeySequence::StandardKey::New);
	connect(newProject, &QAction::triggered, this, &MainWindow::createNewProject);

	auto * openProject = fileMenu->addAction(QApplication::tr("OpenProject"));
	openProject->setShortcut(QKeySequence::StandardKey::Open);
	connect(openProject, &QAction::triggered, this, static_cast<void(MainWindow::*)()>(&MainWindow::loadProject));

	auto * saveProject = fileMenu->addAction(QApplication::tr("SaveProject"));
	saveProject->setShortcut(QKeySequence::StandardKey::Save);
	connect(saveProject, &QAction::triggered, this, &MainWindow::saveProject);
	connect(this, &MainWindow::projectLoaded, [saveProject]() {
		saveProject->setEnabled(true);
	});
	saveProject->setEnabled(false);

	fileMenu->addSeparator();

	auto * exportProject = fileMenu->addAction(QApplication::tr("Export"));
	connect(exportProject, &QAction::triggered, this, &MainWindow::exportProject);
	connect(this, &MainWindow::projectLoaded, [exportProject]() {
		exportProject->setEnabled(true);
	});
	exportProject->setEnabled(false);

	menuBar()->addMenu(fileMenu);
}

void MainWindow::createEditMenu() {
	auto * editMenu = new QMenu(QApplication::tr("Edit"), this);

	auto * redoAction = UndoStack::instance()->createRedoAction(editMenu, QApplication::tr("Redo"));
	redoAction->setShortcut(QKeySequence::Redo);

	editMenu->addAction(redoAction);

	auto * undoAction = UndoStack::instance()->createUndoAction(editMenu, QApplication::tr("Undo"));
	undoAction->setShortcut(QKeySequence::Undo);

	editMenu->addAction(undoAction);

	menuBar()->addMenu(editMenu);
}

void MainWindow::createTabs() {
	_characterTab = new CharacterTab(this);
	_dialogTab = new DialogTab(this);
	_translateableTextTab = new TranslateableTextTab(this);
	
	auto * tabWidget = new QTabWidget(this);
	tabWidget->addTab(_characterTab, QApplication::tr("Characters"));
	tabWidget->addTab(_dialogTab, QApplication::tr("Dialogs"));
	tabWidget->addTab(_translateableTextTab, QApplication::tr("Texts"));

	setCentralWidget(tabWidget);
}

void MainWindow::initConnections() {
	connect(this, &MainWindow::projectLoaded, UndoStack::instance(), &UndoStack::setClean);
	connect(this, &MainWindow::projectLoaded, UndoStack::instance(), &UndoStack::clear);
	
	connect(this, &MainWindow::projectLoaded, this, &MainWindow::adjustTitle);
	connect(UndoStack::instance(), &UndoStack::cleanChanged, this, &MainWindow::adjustTitle);
}

void MainWindow::loadProject(const QString & path) {
	_project = std::make_shared<Project>();

	if (!Project::supports(path)) return;

	QList<CharacterPtr> characters;
	QList<DialogPtr> dialogs;
	QList<TranslateableTextPtr> texts;

	_project->load(path, [this](const QString & type) {
		const auto * usedPlugin = _pluginLoader->getGamePlugin(type);
		return usedPlugin;
	});

	CharacterPool::instance()->setCharacters(_project->getCharacters());
	DialogPool::instance()->setDialogs(_project->getDialogs());
	TranslateableTextPool::instance()->setTranslateableTexts(_project->getTexts());

	updatePlugin();

	emit projectLoaded();
}

void MainWindow::adjustTitle() {
	auto title = QString("TakeControl %1").arg(VERSION_STRING);
	
	if (_project) {
		title.prepend(_project->getName() + " - ");

		if (!UndoStack::instance()->isClean()) {
			title.prepend("* ");
		}
	}
	
	setWindowTitle(title);
}

void MainWindow::updatePlugin() {
	const auto * usedPlugin = _pluginLoader->getGamePlugin(_project->getType());

	ConditionFactory::instance()->setActivePlugin(usedPlugin);
	NodeFactory::instance()->setActivePlugin(usedPlugin);
	NodeItemFactory::instance()->setActivePlugin(usedPlugin);
	PropertyItemFactory::instance()->setActivePlugin(usedPlugin);
	_dialogTab->setActivePlugin(usedPlugin);
	_translateableTextTab->setActivePlugin(usedPlugin);

	const auto languages = usedPlugin->getSupportedLanguages();
	if (!languages.isEmpty()) {
		TranslateableTextPool::instance()->setDefaultLanguage(languages[0]);
	}
}

void MainWindow::saveSettings() {
	Config::IniParser->beginGroup("WINDOWGEOMETRY");
		Config::IniParser->setValue("MainWindowGeometry", saveGeometry());
		Config::IniParser->setValue("MainWindowState", saveState());
	Config::IniParser->endGroup();
}

void MainWindow::restoreSettings() {
	Config::IniParser->beginGroup("WINDOWGEOMETRY");
		QByteArray arr = Config::IniParser->value("MainWindowGeometry", QByteArray()).toByteArray();
		if (!restoreGeometry(arr)) {
			Config::IniParser->remove("MainWindowGeometry");
		}
		arr = Config::IniParser->value("MainWindowState", QByteArray()).toByteArray();
		if (!restoreGeometry(arr)) {
			Config::IniParser->remove("MainWindowState");
		}
	Config::IniParser->endGroup();
}
