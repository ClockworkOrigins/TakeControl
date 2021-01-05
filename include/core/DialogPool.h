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

#include "core/CoreParameters.h"
#include "core/CoreTypes.h"

#include "utils/Singleton.h"

#include <QList>
#include <QObject>

namespace tc {
namespace core {

	class TC_CORE_API DialogPool : public QObject, public utils::Singleton<DialogPool> {
		Q_OBJECT

		friend class utils::Singleton<DialogPool>;

	public:
		void setDialogs(const QList<DialogPtr> & dialogs);
		QList<DialogPtr> getDialogs() const;

		void addDialog(const DialogPtr & dialog);
		void removeDialog(const DialogPtr & dialog);

	signals:
		void dialogsChanged();
		void dialogAdded(const DialogPtr & dialog);
		void dialogRemoved(const DialogPtr & dialog);
		void changedIdentifier(const QString & before, const QString & after);

	public slots:
		void changeIdentifier(const QString & before, const QString & after);

	private:
		QList<DialogPtr> _dialogs;
	};

} /* namespace core */
} /* namespace tc */
