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

#include "redskiesascensiondemoplugin/RedSkiesAscensionDemoPlugin.h"

using namespace tc::core;
using namespace tc::gui;
using namespace tc::plugins::redskiesascensiondemo;

QString RedSkiesAscensionDemoPlugin::getName() const {
	return "Red Skies: Ascension - Demo";
}

QStringList RedSkiesAscensionDemoPlugin::getSupportedNodes() const {
	return {
		"And",
		"Branching",
		"Exit Conversation",
		"Or",
		"Output",
		"Repeatable Dialog",
		"Translateable Text"
	};
}

IConditionPtr RedSkiesAscensionDemoPlugin::createCondition(const QString &, const QJsonObject &) const {
	return nullptr;
}

INodePtr RedSkiesAscensionDemoPlugin::createNode(const QString &) const {
	return nullptr;
}

NodeItem * RedSkiesAscensionDemoPlugin::createNodeItem(const QString &) const {
    return nullptr;
}

IPropertyPtr RedSkiesAscensionDemoPlugin::createProperty(const QString &) const {
    return nullptr;
}

PropertyItem * RedSkiesAscensionDemoPlugin::createPropertyItem(const QString &) const {
    return nullptr;
}

QStringList RedSkiesAscensionDemoPlugin::getSupportedLanguages() const {
	return {
		"English",
		"German"
	};
}

bool RedSkiesAscensionDemoPlugin::exportProject(const ProjectPtr &) const {
	return false; // TODO: implement somewhen in the future
}

QStringList RedSkiesAscensionDemoPlugin::getCharacterProperties() const {
	return {
		"Translateable Text"
	};
}

Q_PLUGIN_METADATA(IID "tc.game.IGamePlugin")
