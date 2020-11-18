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

#include "commands/AddNodeCommand.h"

#include "core/Dialog.h"
#include "core/NodeFactory.h"

#include <QApplication>

using namespace tc::client::commands;
using namespace tc::core;

AddNodeCommand::AddNodeCommand(const DialogPtr & dialog, const QString & nodeType) : QUndoCommand(QApplication::tr("AddNode")), _dialog(dialog) {
    _node = NodeFactory::instance()->create(nodeType);
}

void AddNodeCommand::redo() {
    _dialog->addNode(_node);

    emit addedNode(_node);
}

void AddNodeCommand::undo() {
    _dialog->removeNode(_node);

    emit removedNode(_node);
}
