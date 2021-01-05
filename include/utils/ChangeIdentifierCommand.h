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

#pragma once

#include "utils/UtilsParameters.h"

#include <QUndoCommand>

namespace tc {
namespace utils {

	class TC_UTILS_API ChangeIdentifierCommand : public QObject, public QUndoCommand {
		Q_OBJECT

    public:
        ChangeIdentifierCommand(const QString & before, const QString & after);

	signals:
        void changedIdentifier(const QString & before, const QString & after);
		
	private:
        QString _before;
        QString _after;
		
        void undo() override;
        void redo() override;
	};

} /* namespace utils */
} /* namespace tc */
