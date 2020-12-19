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

#include "PropertyItemFactory.h"

#include "properties/CharacterPropertyItem.h"
#include "properties/TextPropertyItem.h"
#include "properties/TranslateableTextPropertyItem.h"

#include "core/IGamePlugin.h"
#include "core/IProperty.h"

using namespace tc::core;
using namespace tc::gui;

PropertyItem * PropertyItemFactory::create(const IPropertyPtr & prop) const {
	const auto type = prop->getType();

	// handle special types we can handle ourselves

	PropertyItem * propertyItem = nullptr;

	if (type == "Character") {
		propertyItem = new CharacterPropertyItem();
	}

	if (type == "Text") {
		propertyItem = new TextPropertyItem();
	}

	if (type == "Translateable Text") {
		propertyItem = new TranslateableTextPropertyItem();
	}

	// if no built-in node matches, try plugin nodes

	if (!propertyItem && _activePlugin) {
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
