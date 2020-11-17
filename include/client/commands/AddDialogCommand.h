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

#include <memory>

#include <QUndoCommand>

namespace tc {
namespace utils {
	class Dialog;
	typedef std::shared_ptr<Dialog> DialogPtr;
} /* namespace utils */
namespace client {
	class DialogTab;
namespace commands {

	class AddDialogCommand : public QUndoCommand {
	public:
		AddDialogCommand(DialogTab * dialogTab);

	private:
		DialogTab * _dialogTab;
		utils::DialogPtr _dialog;

		void undo() override;
		void redo() override;
	};

} /* namespace commands */
} /* namespace client */
} /* namespace tc */
