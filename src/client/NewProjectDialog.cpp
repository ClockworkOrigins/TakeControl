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

#include "NewProjectDialog.h"

#include "core/Project.h"

#include <QApplication>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

using namespace tc::client;
using namespace tc::core;

NewProjectDialog::NewProjectDialog(QStringList games, QWidget * par) : QDialog(par) {
	QVBoxLayout * vl = new QVBoxLayout();

	QLabel * projectNameLabel = new QLabel(QApplication::tr("ProjectName"), this);
	_projectNameEdit = new QLineEdit(this);

	vl->addWidget(projectNameLabel);
	vl->addWidget(_projectNameEdit);

	QLabel * pathLabel = new QLabel(QApplication::tr("ProjectPath"), this);
	vl->addWidget(pathLabel);

	{
		QHBoxLayout * hl = new QHBoxLayout();

		_pathEdit = new QLineEdit(this);
		
		QPushButton * selectPathButton = new QPushButton("...", this);

		connect(selectPathButton, &QPushButton::released, this, &NewProjectDialog::onSelectPathClicked);

		hl->addWidget(_pathEdit, 1);
		hl->addWidget(selectPathButton);

		vl->addLayout(hl);
	}

	QLabel * gameLabel = new QLabel(QApplication::tr("Game"), this);
	_gamesCombobox = new QComboBox(this);

	std::sort(games.begin(), games.end());
	
	_gamesCombobox->addItems(games);

	vl->addWidget(gameLabel);
	vl->addWidget(_gamesCombobox);

	_dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
	vl->addWidget(_dialogButtonBox, 0, Qt::AlignBottom);

	connect(_projectNameEdit, &QLineEdit::textEdited, this, &NewProjectDialog::validateSelection);
	connect(_pathEdit, &QLineEdit::textEdited, this, &NewProjectDialog::validateSelection);
	connect(_gamesCombobox, &QComboBox::currentTextChanged, this, &NewProjectDialog::validateSelection);

	connect(_dialogButtonBox, &QDialogButtonBox::accepted, this, &NewProjectDialog::accept);
	connect(_dialogButtonBox, &QDialogButtonBox::rejected, this, &NewProjectDialog::reject);

	validateSelection();

	setLayout(vl);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

ProjectPtr NewProjectDialog::createNewProject() {
	if (!exec()) return ProjectPtr();

	return std::make_shared<Project>(_pathEdit->text(), _projectNameEdit->text(), _gamesCombobox->currentText());
}

void NewProjectDialog::onSelectPathClicked() {
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::DirectoryOnly);
	if (dialog.exec()) {
		_pathEdit->setText(dialog.selectedFiles()[0]);
		validateSelection();
	}
}

void NewProjectDialog::validateSelection() {
	bool valid = true;
	valid &= !_pathEdit->text().isEmpty();
	valid &= !_projectNameEdit->text().isEmpty();
	valid &= !_gamesCombobox->currentText().isEmpty();
	valid &= QDir(_pathEdit->text()).exists();

	auto * btn = _dialogButtonBox->button(QDialogButtonBox::Ok);
	btn->setEnabled(valid);
}
