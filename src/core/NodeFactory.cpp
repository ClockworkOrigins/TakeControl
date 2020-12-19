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

#include "NodeFactory.h"

#include "IGamePlugin.h"

#include "nodes/AndNode.h"
#include "nodes/BranchingNode.h"
#include "nodes/ExitConversationNode.h"
#include "nodes/OrNode.h"
#include "nodes/OutputNode.h"
#include "nodes/TextNode.h"
#include "nodes/TranslateableTextNode.h"

#include <QJsonObject>

using namespace tc::core;

INodePtr NodeFactory::create(const QJsonObject & json) const {
	if (!json.contains("type")) return nullptr;
	
	const auto nodeType = json["type"].toString();

	INodePtr nodePtr = create(nodeType);

	if (nodePtr) {
		nodePtr->read(json);
	}

	return nodePtr;
}

INodePtr NodeFactory::create(const QString & type) const {
	INodePtr nodePtr;

	if (type == "And") {
		nodePtr = std::make_shared<AndNode>();
	}

	if (type == "Branching") {
		nodePtr = std::make_shared<BranchingNode>();
	}

	if (type == "Exit Conversation") {
		nodePtr = std::make_shared<ExitConversationNode>();
	}

	if (type == "Or") {
		nodePtr = std::make_shared<OrNode>();
	}

	if (type == "Output") {
		nodePtr = std::make_shared<OutputNode>();
	}

	if (type == "Text") {
		nodePtr = std::make_shared<TextNode>();
	}

	if (type == "Translateable Text") {
		nodePtr = std::make_shared<TranslateableTextNode>();
	}

	// if no built-in node matches, try plugin nodes

	if (!nodePtr && _activePlugin) {
		nodePtr = _activePlugin->createNode(type);
	}

	return nodePtr;
}

void NodeFactory::setActivePlugin(const IGamePlugin * plugin) {
	_activePlugin = plugin;
}
