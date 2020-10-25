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

#include "nodes/NodeFactory.h"

#include "nodes/implementations/AndNode.h"
#include "nodes/implementations/OrNode.h"

#include "plugins/IGamePlugin.h"

#include <QJsonObject>

using namespace tc;
using namespace tc::nodes;

INodePtr NodeFactory::create(const QJsonObject & json) const {
	if (!json.contains("type")) return nullptr;
	
	const auto nodeType = json["type"].toString();

	INodePtr nodePtr;
	
	if (nodeType == "And") {
		nodePtr = std::make_shared<AndNode>();
	}
	
	if (nodeType == "Or") {
		nodePtr = std::make_shared<OrNode>();
	}

	// if no built-in condition matches, try plugin conditions

	if (!nodePtr) {
		nodePtr = _activePlugin->createNode(nodeType, json);
	}

	if (nodePtr) {
		nodePtr->read(json);
	}

	return nodePtr;
}

void NodeFactory::setActivePlugin(const plugins::IGamePlugin * plugin) {
	_activePlugin = plugin;
}
