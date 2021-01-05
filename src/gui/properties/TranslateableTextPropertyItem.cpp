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

#include "properties/TranslateableTextPropertyItem.h"

#include "core/TranslateableText.h"
#include "core/TranslateableTextPool.h"

#include "core/properties/TranslateableTextProperty.h"

#include <QComboBox>
#include <QCompleter>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QPainter>
#include <QVBoxLayout>

using namespace tc::core;
using namespace tc::gui;

TranslateableTextPropertyItem::TranslateableTextPropertyItem() : PropertyItem() {
    _graphicsProxyWidget = new QGraphicsProxyWidget(this);

    _comboBox = new QComboBox();
    _comboBox->setFixedWidth(180);
    _comboBox->setEditable(true);

    _label = new QLabel();
    _label->setFixedWidth(180);
    _label->setMinimumHeight(180);
    _label->setWordWrap(true);
    _label->setAlignment(Qt::AlignTop);
    _label->setContentsMargins(2, 2, 2, 2);

    auto * w = new QWidget();
    w->setFixedWidth(180);
    w->setContentsMargins(0, 0, 0, 0);
	
    auto * l = new QVBoxLayout();
    l->setContentsMargins(0, 0, 0, 0);

    l->addWidget(_comboBox);
    l->addWidget(_label);

    w->setLayout(l);

	_graphicsProxyWidget->setWidget(w);

    _boundingRect = _graphicsProxyWidget->boundingRect();

    connect(TranslateableTextPool::instance(), &TranslateableTextPool::translateableTextsChanged, this, &TranslateableTextPropertyItem::updateTranslateableTexts);
    connect(TranslateableTextPool::instance(), &TranslateableTextPool::translateableTextAdded, this, &TranslateableTextPropertyItem::updateTranslateableTexts);
    connect(TranslateableTextPool::instance(), &TranslateableTextPool::translateableTextRemoved, this, &TranslateableTextPropertyItem::updateTranslateableTexts);
    connect(TranslateableTextPool::instance(), &TranslateableTextPool::changedIdentifier, this, [this](const QString & before, const QString & after) {
        if (_property->getValue() != before) return;

        _property->_value = after;

        QSignalBlocker sb(_comboBox);
    	
        _comboBox->setCurrentText(after);
    });

    updateTranslateableTexts();
}

void TranslateableTextPropertyItem::configure(const IPropertyPtr & prop) {
    _property = std::dynamic_pointer_cast<TranslateableTextProperty>(prop);

    const auto text = _property->getValue();

    _comboBox->setCurrentText(text);

    connect(_comboBox, QOverload<const QString &>::of(&QComboBox::currentTextChanged), _property.get(), &TranslateableTextProperty::setValue);
    connect(_comboBox, QOverload<const QString &>::of(&QComboBox::currentTextChanged), this, [this]() {
        const auto texts = TranslateableTextPool::instance()->getTranslateableTexts();
        const auto it = std::find_if(texts.begin(), texts.end(), [this](const TranslateableTextPtr & translateableText) {
            return translateableText->getKey() == _property->getValue();
        });

        const auto defaultLanguage = TranslateableTextPool::instance()->getDefaultLanguage();

        disconnect(_currentConnection);

        if (it == texts.end()) {
            _label->setText(QString());
            return;
        }

        auto tt = *it;
    	
        _label->setText(tt->getTranslation(defaultLanguage));

    	_currentConnection = connect(tt.get(), &TranslateableText::translationChanged, this, [this, defaultLanguage](const QString & l, const QString & t) {
            if (l != defaultLanguage) return;

            _label->setText(t);
    	});
    });
    connect(_property.get(), &TranslateableTextProperty::valueChanged, _comboBox, [this]() {
        _comboBox->setCurrentText(_property->getValue());
	});
}

QRectF TranslateableTextPropertyItem::boundingRect() const {
    return _boundingRect;
}

void TranslateableTextPropertyItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    _graphicsProxyWidget->paint(painter, option, widget);
}

void TranslateableTextPropertyItem::updateTranslateableTexts() {
    const auto translateableTexts = TranslateableTextPool::instance()->getTranslateableTexts();

    QStringList options;
    for (const auto & c : translateableTexts) {
        options << c->getKey();
    }
    options.sort();

    _comboBox->clear();
    _comboBox->insertItems(0, options);

    updateCompleter(options);
}

void TranslateableTextPropertyItem::updateCompleter(const QStringList & options) {
    auto * completer = new QCompleter(options, _comboBox);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    completer->setFilterMode(Qt::MatchContains);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);

    _comboBox->setCompleter(completer);
}
