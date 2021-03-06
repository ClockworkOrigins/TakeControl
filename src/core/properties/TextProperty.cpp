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

#include "properties/TextProperty.h"

#include "commands/SetTextPropertyValueCommand.h"

#include "utils/UndoStack.h"

#include <QJsonObject>

using namespace tc::core;
using namespace tc::utils;

TextProperty::TextProperty() : IProperty(), _value(getDefaultValue()) {}

void TextProperty::setValue(const QString & value) {
    if (_value == value) return;

    auto * cmd = new SetTextPropertyValueCommand(this, value);
    UndoStack::instance()->push(cmd);
}

QString TextProperty::getValue() const {
    return _value;
}

void TextProperty::read(const QJsonObject & json) {
    _value = json["value"].toString();
}

void TextProperty::write(QJsonObject & json) const {
	IProperty::write(json);
    json["value"] = _value;
}

QString TextProperty::getType() const {
	return "Text";
}

QString TextProperty::getDefaultValue() {
    return QString();
}
