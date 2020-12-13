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

#pragma once

#include "core/CoreTypes.h"

#include <QUndoCommand>

namespace tc {
namespace client {
namespace commands {

	class RemoveConnectionCommand : public QObject, public QUndoCommand {
		Q_OBJECT
		
	public:
		RemoveConnectionCommand(const core::DialogPtr & dialog, const core::ConnectionPtr & connection);

	signals:
		void addedConnection(const core::ConnectionPtr & connection);
		void removedConnection(const core::ConnectionPtr & connection);

	private:
		core::DialogPtr _dialog;
		core::ConnectionPtr _connection;

		void undo() override;
		void redo() override;
	};

} /* namespace commands */
} /* namespace client */
} /* namespace tc */
