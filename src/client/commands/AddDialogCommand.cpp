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

#include "commands/AddDialogCommand.h"

#include <cassert>

#include "core/Dialog.h"
#include "core/DialogPool.h"

#include <QApplication>
#include <QStandardItemModel>

using namespace tc::client::commands;
using namespace tc::core;

AddDialogCommand::AddDialogCommand() : QUndoCommand(QApplication::tr("AddDialog")) {
	int number = 1;

	const auto dialogs = DialogPool::instance()->getDialogs();

	while (std::find_if(dialogs.begin(), dialogs.end(), [number](const std::shared_ptr<Dialog> & c) {
		return c->getName() == QString("New Dialog %1").arg(number);
	}) != dialogs.end()) {
		number++;
	}
	
	_dialog = std::make_shared<Dialog>(QString("New Dialog %1").arg(number));
}

void AddDialogCommand::redo() {
	DialogPool::instance()->addDialog(_dialog);
}

void AddDialogCommand::undo() {
	DialogPool::instance()->removeDialog(_dialog);
}
