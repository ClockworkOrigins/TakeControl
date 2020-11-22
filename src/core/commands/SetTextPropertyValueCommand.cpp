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

#include "commands/SetTextPropertyValueCommand.h"

#include "properties/TextProperty.h"

#include <QApplication>

using namespace tc::core;

SetTextPropertyValueCommand::SetTextPropertyValueCommand(TextProperty * prop, const QString & value) : QUndoCommand(QApplication::tr("ChangeText")), _property(prop), _redoValue(value) {
    _undoValue = _property->getValue();
}

void SetTextPropertyValueCommand::redo() {
    _property->_value = _redoValue;
    emit _property->valueChanged();
}

void SetTextPropertyValueCommand::undo() {
    _property->_value = _undoValue;
    emit _property->valueChanged();
}
