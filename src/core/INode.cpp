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

#include "INode.h"

#include "PropertyFactory.h"

#include "IProperty.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>

using namespace tc::core;

void INode::read(const QJsonObject & json) {
    _properties.clear();
	
    QJsonArray propertyArray = json["properties"].toArray();

	for (const auto p : propertyArray) {
        const QJsonObject propertyJson = p.toObject();
        const QString type = propertyJson["type"].toString();

        IPropertyPtr prop = PropertyFactory::instance()->create(type);

        if (!prop) continue;

        prop->read(propertyJson);

        _properties << prop;
	}

    _identifier = json["id"].toInt();

	if (json.contains("x") && json.contains("y")) {
        const auto x = json["x"].toDouble();
        const auto y = json["y"].toDouble();

        _position = QPointF(x, y);
	}
}

void INode::write(QJsonObject & json) const {
	json["type"] = getType();

    QJsonArray propertyArray;

	for (const auto & p : _properties) {
        QJsonObject propertyJson;
        p->write(propertyJson);

        propertyArray << propertyJson;
	}

    if (!propertyArray.isEmpty()) {
        json["properties"] = propertyArray;
    }
	
    json["id"] = _identifier;

    json["x"] = _position.x();
    json["y"] = _position.y();
}

qint32 INode::getInputCount() const {
	return -1;
}

qint32 INode::getOutputCount() const {
	return 1;
}

QString INode::getOutputLabel(qint32) const {
	return QString();
}

QList<IPropertyPtr> INode::getProperties() const {
    return _properties;
}

void INode::setID(int id) {
    _identifier = id;
}

int INode::getID() const {
    return _identifier;
}

void INode::setPosition(const QPointF & pos) {
    _position = pos;
}

QPointF INode::getPosition() const {
    return _position;
}
