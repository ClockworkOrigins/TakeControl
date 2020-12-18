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

#include "commands/RemoveNodeCommand.h"

#include "core/INode.h"
#include "core/Dialog.h"

#include <QApplication>

using namespace tc::client::commands;
using namespace tc::core;

RemoveNodeCommand::RemoveNodeCommand(const DialogPtr & dialog, const INodePtr & node) : QUndoCommand(QApplication::tr("RemoveConnection")), _dialog(dialog), _node(node) {}

void RemoveNodeCommand::redo() {
    _dialog->removeNode(_node);

    emit removedNode(_node);
}

void RemoveNodeCommand::undo() {
    _dialog->addNode(_node);

    emit addedNode(_node);
}
