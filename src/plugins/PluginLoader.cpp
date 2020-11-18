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

#include "plugins/PluginLoader.h"

#include "core/IGamePlugin.h"

#include <QApplication>
#include <QDir>
#include <QPluginLoader>

using namespace tc::core;
using namespace tc::plugins;

PluginLoader::PluginLoader() {
	loadGamePlugins();
}

QList<IGamePlugin *> PluginLoader::getGamePlugins() const {
	return _gamePlugins;
}

const IGamePlugin * PluginLoader::getGamePlugin(const QString & type) const {
	for (const auto * plugin : _gamePlugins) {
		if (plugin->getName() == type) return plugin;
	}

	return nullptr;
}

void PluginLoader::loadGamePlugins() {
	const QDir pluginsDir = QDir(qApp->applicationDirPath() + "/plugins/game");
	for (const QString & fileName : pluginsDir.entryList(QDir::Files)) {
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		QObject * plugin = loader.instance();
		
		if (!plugin) continue; // TODO: log error
		
		_gamePlugins.push_back(qobject_cast<IGamePlugin *>(plugin));
	}
}
