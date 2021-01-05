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

#include <QStandardItemModel>

namespace tc {
namespace utils {

	class TC_UTILS_API EditableListViewModel : public QStandardItemModel {
		Q_OBJECT

    public:
        explicit EditableListViewModel(QObject * par);

	signals:
        void changedIdentifier(const QString & before, const QString & after);
		
	private:
        bool _inCommand;
		
		bool setData(const QModelIndex & index, const QVariant & value, int role) override;
	};

} /* namespace utils */
} /* namespace tc */
