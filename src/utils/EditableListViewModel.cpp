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

#include "EditableListViewModel.h"

#include "ChangeIdentifierCommand.h"
#include "UndoStack.h"

using namespace tc::utils;

EditableListViewModel::EditableListViewModel(QObject * par) : QStandardItemModel(par) {}

bool EditableListViewModel::setData(const QModelIndex & index, const QVariant & value, int role) {
	if (role == Qt::EditRole) {
        auto * cmd = new ChangeIdentifierCommand(data(index).toString(), value.toString());

        connect(cmd, &ChangeIdentifierCommand::changedIdentifier, this, &EditableListViewModel::changedIdentifier);
        connect(cmd, &ChangeIdentifierCommand::changedIdentifier, this, [this, index](const QString &, const QString & after) {
            setData(index, after, Qt::DisplayRole);
        });
		
        UndoStack::instance()->push(cmd);
	}
    return QStandardItemModel::setData(index, value, role);
}
