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

#include "Character.h"

#include "IGamePlugin.h"
#include "IProperty.h"
#include "PropertyFactory.h"

#include <QJsonArray>

using namespace tc::core;

Character::Character(const QString & identifier, const IGamePlugin * plugin) : _identifier(identifier) {
	fillProperties(plugin);
}

void Character::setIdentifier(const QString & identifier) {
	_identifier = identifier;
}

QString Character::getIdentifier() const {
	return _identifier;
}

QJsonObject Character::save() const {
	QJsonObject json;
	json["identifier"] = _identifier;

	QJsonArray propertiesArray;

	for (const auto & prop : _properties) {
		QJsonObject jsonProp;
		prop->write(jsonProp);

		propertiesArray << jsonProp;
	}

	if (propertiesArray.count() > 0) {
		json["properties"] = propertiesArray;
	}

	return json;
}

CharacterPtr Character::load(const QJsonObject & json, const IGamePlugin * plugin) {
	if (!json.contains("identifier")) return nullptr;
	
	QString identifier = json["identifier"].toString();
	
	auto c = std::make_shared<Character>(identifier, plugin);

	c->loadProperties(json);

	return c;
}

void Character::loadProperties(const QJsonObject & json) {
	if (!json.contains("properties")) return;

	QJsonArray propertyArray = json["properties"].toArray();

	int counter = 0;
	for (const auto p : propertyArray) {
		const QJsonObject propertyJson = p.toObject();
		const QString type = propertyJson["type"].toString();

		IPropertyPtr prop = PropertyFactory::instance()->create(type);

		if (!prop) continue;

		prop->read(propertyJson);

		// TODO: adjust when annotation/label for properties is introduced to properly merge them
		_properties[counter++] = prop;
	}
}

void Character::fillProperties(const IGamePlugin * plugin) {
	Q_ASSERT(_properties.isEmpty());

	if (!_properties.isEmpty()) return;
	
	const auto propertyList = plugin->getCharacterProperties();

	for (const auto & prop : propertyList) {
		const auto property = PropertyFactory::instance()->create(prop);

		Q_ASSERT(property);

		if (!property) continue;
		
		_properties << property;
	}
}
