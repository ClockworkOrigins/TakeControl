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

#include "TranslateableTextTab.h"

#include "commands/AddTranslateableTextCommand.h"
#include "commands/ChangeTranslateableTextValueCommand.h"

#include "core/IGamePlugin.h"
#include "core/TranslateableText.h"
#include "core/TranslateableTextPool.h"

#include "utils/EditableListViewModel.h"
#include "utils/UndoStack.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

using namespace tc::client;
using namespace tc::client::commands;
using namespace tc::core;
using namespace tc::utils;

TranslateableTextTab::TranslateableTextTab(QWidget * par) : QWidget(par), _translateableTextList(nullptr), _translateableTextModel(nullptr) {
	auto * hl = new QHBoxLayout();

	{
		auto * vl = new QVBoxLayout();
		
		_translateableTextList = new QListView(this);
		_translateableTextList->setEditTriggers(QAbstractItemView::DoubleClicked);

		_translateableTextModel = new EditableListViewModel(this);

		_sortModel = new QSortFilterProxyModel(this);
		_sortModel->setSourceModel(_translateableTextModel);
		
		_translateableTextList->setModel(_sortModel);

		vl->addWidget(_translateableTextList);

		auto * pb = new QPushButton(QApplication::tr("AddText"), this);
		vl->addWidget(pb);

		connect(pb, &QPushButton::released, this, &TranslateableTextTab::addTranslateableText);

		hl->addLayout(vl, 1);
	}

	{
		_lineEditLayout = new QVBoxLayout();

		hl->addLayout(_lineEditLayout, 4);
	}

	setLayout(hl);

	connect(TranslateableTextPool::instance(), &TranslateableTextPool::translateableTextsChanged, this, &TranslateableTextTab::updateTranslateableTexts);
	connect(TranslateableTextPool::instance(), &TranslateableTextPool::translateableTextAdded, this, &TranslateableTextTab::addedTranslateableText);
	connect(TranslateableTextPool::instance(), &TranslateableTextPool::translateableTextRemoved, this, &TranslateableTextTab::removedTranslateableText);
	connect(_translateableTextList, &QListView::clicked, this, QOverload<const QModelIndex &>::of(&TranslateableTextTab::openText));
	connect(_translateableTextModel, &EditableListViewModel::changedIdentifier, TranslateableTextPool::instance(), &TranslateableTextPool::changeIdentifier);
	connect(_translateableTextModel, &EditableListViewModel::changedIdentifier, TranslateableTextPool::instance(), &TranslateableTextPool::changedIdentifier);
}

void TranslateableTextTab::setActivePlugin(const IGamePlugin * plugin) {
	_activePlugin = plugin;

	for (auto * w : _widgets) {
		w->deleteLater();
	}
	_widgets.clear();
	_lineEdits.clear();
	
	for (auto * o : _lineEditLayout->children()) {
		o->deleteLater();
	}

	if (!plugin) return;

	const auto languages = plugin->getSupportedLanguages();

	for (const auto & l : languages) {
		auto * w = new QWidget(this);
		
		auto * hl = new QHBoxLayout();

		auto * lbl = new QLabel(l, w);

		lbl->setFixedWidth(100);
		
		auto * le = new QLineEdit(w);

		connect(le, &QLineEdit::textChanged, this, [this, l, le]() {
			updateText(l, le->text());
		});
		

		hl->addWidget(lbl);
		hl->addWidget(le);

		w->setLayout(hl);

		_lineEditLayout->addWidget(w);
		_lineEdits.insert(l, le);

		_widgets << w;
	}

	_lineEditLayout->addStretch(1);
}

void TranslateableTextTab::updateTranslateableTexts() {
	_translateableTextModel->clear();
	
	for (const auto & c : TranslateableTextPool::instance()->getTranslateableTexts()) {
		_translateableTextModel->appendRow(new QStandardItem(c->getKey()));
	}
}

void TranslateableTextTab::addTranslateableText() {
	auto * cmd = new AddTranslateableTextCommand();	
	UndoStack::instance()->push(cmd);
}

void TranslateableTextTab::addedTranslateableText(const TranslateableTextPtr & translateableText) {
	_translateableTextModel->appendRow(new QStandardItem(translateableText->getKey()));
}

void TranslateableTextTab::removedTranslateableText(const TranslateableTextPtr & translateableText) {
	const auto itemList = _translateableTextModel->findItems(translateableText->getKey());

	for (const auto & item : itemList) {
		const auto idx = _translateableTextModel->indexFromItem(item);
		_translateableTextModel->removeRows(idx.row(), 1);
	}
}

void TranslateableTextTab::openText(const QModelIndex & idx) {
	Q_ASSERT(idx.model() == _sortModel);

	const auto sourceIdx = _sortModel->mapToSource(idx);

	const int row = sourceIdx.row();

	const auto dialogs = TranslateableTextPool::instance()->getTranslateableTexts();

	Q_ASSERT(row < dialogs.count());

	if (row >= dialogs.count()) return;

	openText(dialogs[row]);
}

void TranslateableTextTab::openText(const TranslateableTextPtr & text) {
	if (_currentText == text) return;

	_currentText = text;

	disconnect(_currentConnection);
	_currentConnection = connect(_currentText.get(), &TranslateableText::translationChanged, this, [this](const QString & l, const QString & t) {
		if (!_lineEdits.contains(l)) return;

		auto * le = _lineEdits.value(l);
		QSignalBlocker sb(le);
		le->setText(t);
	});

	auto texts = text->getTranslations();

	for (auto it = _lineEdits.begin(); it != _lineEdits.end(); ++it) {
		it.value()->blockSignals(true);
		it.value()->setText(QString());
	}

	for (auto it = texts.begin(); it != texts.end(); ++it) {
		const auto & language = it.key();
		const auto t = it.value();

		if (!_lineEdits.contains(language)) {
			_currentText->updateTranslation(language, QString()); // remove that language, not supported by plugin
			continue;
		}

		auto * le = _lineEdits.value(language);
		le->setText(t);
	}

	for (auto it = _lineEdits.begin(); it != _lineEdits.end(); ++it) {
		it.value()->blockSignals(false);
	}
}

void TranslateableTextTab::updateText(const QString & language, const QString & text) {
	if (!_currentText) return;
	
	auto * cmd = new ChangeTranslateableTextValueCommand(_currentText, language, text);
	UndoStack::instance()->push(cmd);
}
