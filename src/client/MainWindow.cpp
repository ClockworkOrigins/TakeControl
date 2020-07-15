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
#include "TakeControlConfig.h"

#include "plugins/IGamePlugin.h"
#include "plugins/PluginLoader.h"

#include "projects/NewProjectDialog.h"
#include "projects/Project.h"

#include "utils/UndoStack.h"

#include <QApplication>
#include <QFileDialog>
#include <QMenuBar>

using namespace tc::client;
using namespace tc::plugins;
using namespace tc::projects;
using namespace tc::utils;

MainWindow::MainWindow() : _pluginLoader(new PluginLoader()), _characterTab(nullptr) {
	setWindowTitle(QString("TakeControl %1").arg(QString::fromStdString(VERSION_STRING)));

	createFileMenu();
	createEditMenu();

	createTabs();
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

	_characterTab->setCharacters({});
	
	emit projectLoaded();
}

void MainWindow::saveProject() {
	if (!_project) return;

	const auto characterList = _characterTab->getCharacters();
	
	_project->save(characterList);
}

void MainWindow::loadProject() {
	QFileDialog dialog(this);
	dialog.setFilter(QDir::Filter::Files);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter("*.json");
	
	if (!dialog.exec()) return;

	loadProject(dialog.selectedFiles()[0]);
}

void MainWindow::createFileMenu() {
	QMenu * fileMenu = new QMenu(QApplication::tr("File"), this);

	QAction * newProject = fileMenu->addAction(QApplication::tr("NewProject"));
	newProject->setShortcut(QKeySequence::StandardKey::New);
	connect(newProject, &QAction::triggered, this, &MainWindow::createNewProject);

	QAction * openProject = fileMenu->addAction(QApplication::tr("OpenProject"));
	openProject->setShortcut(QKeySequence::StandardKey::Open);
	connect(openProject, &QAction::triggered, this, static_cast<void(MainWindow::*)()>(&MainWindow::loadProject));

	QAction * saveProject = fileMenu->addAction(QApplication::tr("SaveProject"));
	saveProject->setShortcut(QKeySequence::StandardKey::Save);
	connect(saveProject, &QAction::triggered, this, &MainWindow::saveProject);
	connect(this, &MainWindow::projectLoaded, [saveProject]() {
		saveProject->setEnabled(true);
	});
	saveProject->setEnabled(false);

	menuBar()->addMenu(fileMenu);
}

void MainWindow::createEditMenu() {
	QMenu * editMenu = new QMenu(QApplication::tr("Edit"), this);

	QAction * redoAction = UndoStack::instance()->createRedoAction(editMenu, QApplication::tr("Redo"));
	redoAction->setShortcut(QKeySequence::Redo);

	editMenu->addAction(redoAction);

	QAction * undoAction = UndoStack::instance()->createUndoAction(editMenu, QApplication::tr("Undo"));
	undoAction->setShortcut(QKeySequence::Undo);

	editMenu->addAction(undoAction);

	menuBar()->addMenu(editMenu);
}

void MainWindow::createTabs() {
	_characterTab = new CharacterTab(this);
	
	QTabWidget * tabWidget = new QTabWidget(this);
	tabWidget->addTab(_characterTab, QApplication::tr("Characters"));
	tabWidget->addTab(new DialogTab(this), QApplication::tr("Dialogs"));

	setCentralWidget(tabWidget);
}

void MainWindow::loadProject(const QString & path) {
	_project = std::make_shared<Project>();

	if (!Project::supports(path)) return;

	QList<std::shared_ptr<Character>> characters;
	
	_project->load(path, characters);

	_characterTab->setCharacters(characters);

	emit projectLoaded();
}
