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

	class ChangeTranslateableTextValueCommand : public QUndoCommand {
	public:
        ChangeTranslateableTextValueCommand(const core::TranslateableTextPtr & tt, const QString & language, const QString & text);

	private:
		core::TranslateableTextPtr _translateableText;
        QString _language;
        QString _redoText;
        QString _undoText;

		void undo() override;
		void redo() override;
	};

} /* namespace commands */
} /* namespace client */
} /* namespace tc */
