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

#include "utils/UndoStack.h"

#include <QApplication>
#include <QMenuBar>

using namespace tc::client;
using namespace tc::plugins;
using namespace tc::projects;
using namespace tc::utils;

MainWindow::MainWindow() : _pluginLoader(new PluginLoader()) {
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

	auto project = dlg.createNewProject();

	// TODO: store project to work on
}

void MainWindow::createFileMenu() {
	QMenu * fileMenu = new QMenu(QApplication::tr("File"), this);

	QAction * newProject = fileMenu->addAction(QApplication::tr("NewProject"));
	connect(newProject, &QAction::triggered, this, &MainWindow::createNewProject);

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
	QTabWidget * tabWidget = new QTabWidget(this);
	tabWidget->addTab(new CharacterTab(this), QApplication::tr("Characters"));
	tabWidget->addTab(new DialogTab(this), QApplication::tr("Dialogs"));

	setCentralWidget(tabWidget);
}
