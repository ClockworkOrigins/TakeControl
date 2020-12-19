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

#include "PropertyFactory.h"

#include "IGamePlugin.h"

#include "properties/CharacterProperty.h"
#include "properties/TextProperty.h"
#include "properties/TranslateableTextProperty.h"

using namespace tc::core;

IPropertyPtr PropertyFactory::create(const QString & type) const {
	IPropertyPtr propertyPtr;

	if (type == "Character") {
		propertyPtr = std::make_shared<CharacterProperty>();
	}

	if (type == "Text") {
		propertyPtr = std::make_shared<TextProperty>();
	}

	if (type == "Translateable Text") {
		propertyPtr = std::make_shared<TranslateableTextProperty>();
	}

	// if no built-in node matches, try plugin nodes

	if (!propertyPtr && _activePlugin) {
		propertyPtr = _activePlugin->createProperty(type);
	}

	return propertyPtr;
}

void PropertyFactory::setActivePlugin(const IGamePlugin * plugin) {
	_activePlugin = plugin;
}
