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

#include "DialogTab.h"

#include "utils/Dialog.h"

#include <QApplication>
#include <QStandardItemModel>

using namespace tc::client;
using namespace tc::client::commands;
using namespace tc::utils;

AddDialogCommand::AddDialogCommand(DialogTab * dialogTab) : QUndoCommand(QApplication::tr("AddDialog")), _dialogTab(dialogTab) {
	int number = 1;

	while (std::find_if(_dialogTab->_dialogs.begin(), _dialogTab->_dialogs.end(), [number](const std::shared_ptr<Dialog> & c) { return c->getName() == QString("New Dialog %1").arg(number); }) != _dialogTab->_dialogs.end()) {
		number++;
	}
	
	_dialog = std::make_shared<Dialog>(QString("New Dialog %1").arg(number));
}

void AddDialogCommand::redo() {
	_dialogTab->_dialogs.append(_dialog);

	_dialogTab->_dialogModel->appendRow(new QStandardItem(_dialog->getName()));
}

void AddDialogCommand::undo() {
	const int idx = _dialogTab->_dialogs.indexOf(_dialog);

	assert(idx == _dialogTab->_dialogs.size() - 1);

	_dialogTab->_dialogModel->removeRows(idx, 1);

	_dialogTab->_dialogs.pop_back();
}
