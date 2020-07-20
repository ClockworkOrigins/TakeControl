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

#pragma once

#include <memory>

#include <QMainWindow>

namespace tc {
namespace plugins {
	class PluginLoader;
}
namespace projects {
	class Project;
	typedef std::shared_ptr<Project> ProjectPtr;
}
namespace client {

	class CharacterTab;
	class DialogTab;

	class MainWindow : public QMainWindow {
		Q_OBJECT
		
	public:
		MainWindow();

	signals:
		void projectLoaded();

	private slots:
		void createNewProject();
		void saveProject();
		void loadProject();

	private:
		plugins::PluginLoader * _pluginLoader;
		projects::ProjectPtr _project;

		CharacterTab * _characterTab;
		DialogTab * _dialogTab;

		void createFileMenu();
		void createEditMenu();
		void createTabs();

		void initConnections();

		void loadProject(const QString & path);

		void adjustTitle();
	};

} /* namespace client */
} /* namespace tc */
