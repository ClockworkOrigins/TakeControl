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

#include "properties/CharacterPropertyItem.h"

#include "core/Character.h"
#include "core/CharacterPool.h"

#include "core/properties/CharacterProperty.h"

#include <QComboBox>
#include <QCompleter>
#include <QGraphicsProxyWidget>
#include <QPainter>

#include "core/TranslateableTextPool.h"

using namespace tc::core;
using namespace tc::gui;

CharacterPropertyItem::CharacterPropertyItem() : PropertyItem() {
    _graphicsProxyWidget = new QGraphicsProxyWidget(this);

    _comboBox = new QComboBox();
    _comboBox->setFixedWidth(180);
    _comboBox->setEditable(true);

    _graphicsProxyWidget->setWidget(_comboBox);

    _boundingRect = _graphicsProxyWidget->boundingRect();

    connect(CharacterPool::instance(), &CharacterPool::charactersChanged, this, &CharacterPropertyItem::updateCharacters);
    connect(CharacterPool::instance(), &CharacterPool::characterAdded, this, &CharacterPropertyItem::updateCharacters);
    connect(CharacterPool::instance(), &CharacterPool::characterRemoved, this, &CharacterPropertyItem::updateCharacters);
    connect(CharacterPool::instance(), &CharacterPool::changedIdentifier, this, [this](const QString & before, const QString & after) {
        if (_property->getValue() != before) return;

        _property->_value = after;

        QSignalBlocker sb(_comboBox);

        _comboBox->setCurrentText(after);
        });

    updateCharacters();
}

void CharacterPropertyItem::configure(const IPropertyPtr & prop) {
    _property = std::dynamic_pointer_cast<CharacterProperty>(prop);

    const auto text = _property->getValue();
	
    _comboBox->setCurrentText(text);

    connect(_comboBox, QOverload<const QString &>::of(&QComboBox::currentTextChanged), _property.get(), &CharacterProperty::setValue);
    connect(_property.get(), &CharacterProperty::valueChanged, _comboBox, [this]() {
        _comboBox->setCurrentText(_property->getValue());
    });
}

QRectF CharacterPropertyItem::boundingRect() const {
    return _boundingRect;
}

void CharacterPropertyItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    _graphicsProxyWidget->paint(painter, option, widget);
}

void CharacterPropertyItem::updateCharacters() {
    const auto characters = CharacterPool::instance()->getCharacters();

    QStringList options;
    for (const auto & c : characters) {
        options << c->getIdentifier();
    }
    options.sort();

    _comboBox->clear();
    _comboBox->insertItems(0, options);

    updateCompleter(options);
}

void CharacterPropertyItem::updateCompleter(const QStringList & options) {
    auto * completer = new QCompleter(options, _comboBox);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    completer->setFilterMode(Qt::MatchContains);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
	
    _comboBox->setCompleter(completer);
}
