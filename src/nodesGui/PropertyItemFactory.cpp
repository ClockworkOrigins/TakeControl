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

#include "nodesGui/PropertyItemFactory.h"

#include "nodes/interfaces/IProperty.h"

#include "nodesGui/CharacterPropertyItem.h"

#include "plugins/IGamePlugin.h"

using namespace tc;
using namespace tc::nodes;
using namespace tc::nodesGui;
using namespace tc::plugins;

PropertyItem * PropertyItemFactory::create(const IPropertyPtr & prop) const {
	const auto type = prop->getType();

	// handle special types we can handle ourselves

	PropertyItem * propertyItem = nullptr;

	if (type == "Character") {
		propertyItem = new CharacterPropertyItem();
	}

	// if no built-in node matches, try plugin nodes

	if (!propertyItem) {
		propertyItem = _activePlugin->createPropertyItem(type);
	}

	if (propertyItem) {
		propertyItem->configure(prop);
	}

	return propertyItem;
}

void PropertyItemFactory::setActivePlugin(const IGamePlugin * plugin) {
	_activePlugin = plugin;
}
