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

#include <QMap>
#include <QWidget>

class QLineEdit;
class QListView;
class QSortFilterProxyModel;
class QVBoxLayout;

namespace tc {
namespace utils {
	class EditableListViewModel;
} /* namespace utils */
namespace client {
namespace commands {
	class AddTranslateableTextCommand;
} /* namespace commands */

	class TranslateableTextTab : public QWidget {
		Q_OBJECT
		
	public:
		explicit TranslateableTextTab(QWidget * par);

		void setActivePlugin(const core::IGamePlugin * plugin);

	private slots:
		void updateTranslateableTexts();
	
		void addTranslateableText();

		void addedTranslateableText(const core::TranslateableTextPtr & translateableText);
		void removedTranslateableText(const core::TranslateableTextPtr & translateableText);

	private:
		QListView * _translateableTextList;
		utils::EditableListViewModel * _translateableTextModel;
		QSortFilterProxyModel * _sortModel = nullptr;

		const core::IGamePlugin * _activePlugin = nullptr;

		QVBoxLayout * _lineEditLayout;
		QMap<QString, QLineEdit *> _lineEdits;

		QList<QWidget *> _widgets;

		core::TranslateableTextPtr _currentText;

		QMetaObject::Connection _currentConnection;

		void openText(const QModelIndex & idx);
		void openText(const core::TranslateableTextPtr & text);

		void updateText(const QString & language, const QString & text);
	};

} /* namespace client */
} /* namespace tc */
