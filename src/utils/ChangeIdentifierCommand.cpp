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
// Copyright 2021 Clockwork Origins

#include "ChangeIdentifierCommand.h"

#include <QApplication>

using namespace tc::utils;

ChangeIdentifierCommand::ChangeIdentifierCommand(const QString & before, const QString & after) : QUndoCommand(QApplication::tr("ChangeIdentifier")), _before(before), _after(after) {}

void ChangeIdentifierCommand::redo() {
    emit changedIdentifier(_before, _after);
}

void ChangeIdentifierCommand::undo() {
    emit changedIdentifier(_after, _before);
}
