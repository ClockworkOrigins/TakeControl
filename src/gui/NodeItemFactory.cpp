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

#include "NodeItemFactory.h"

#include "NodeItem.h"

#include "core/IGamePlugin.h"
#include "core/INode.h"

using namespace tc::core;
using namespace tc::gui;

NodeItem * NodeItemFactory::create(const INodePtr & node) const {
	const auto type = node->getType();

	// handle special types we can handle ourselves

	NodeItem * nodeItem = nullptr;

	// if no built-in node matches, try plugin nodes

	if (!nodeItem && _activePlugin) {
		nodeItem = _activePlugin->createNodeItem(type);
	}

	if (!nodeItem) {
		nodeItem = new NodeItem();
	}

	nodeItem->configure(node);

	return nodeItem;
}

void NodeItemFactory::setActivePlugin(const IGamePlugin * plugin) {
	_activePlugin = plugin;
}
