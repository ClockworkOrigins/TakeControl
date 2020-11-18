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

#include <QDialog>
#include <QString>

class QComboBox;
class QDialogButtonBox;
class QLineEdit;

namespace tc {
namespace core {
	class Project;
	typedef std::shared_ptr<Project> ProjectPtr;
} /* namespace core */
namespace client {


	class NewProjectDialog : public QDialog {
		Q_OBJECT
		
	public:
		NewProjectDialog(QStringList games, QWidget * par);

		core::ProjectPtr createNewProject();

	private slots:
		void onSelectPathClicked();
		void validateSelection();

	private:
		QComboBox * _gamesCombobox;
		QLineEdit * _projectNameEdit;
		QLineEdit * _pathEdit;
		QDialogButtonBox * _dialogButtonBox;
	};

} /* namespace client */
} /* namespace tc */
