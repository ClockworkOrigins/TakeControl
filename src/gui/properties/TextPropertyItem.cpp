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

#include "properties/TextPropertyItem.h"

#include "core/properties/TextProperty.h"

#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QPainter>

using namespace tc::core;
using namespace tc::gui;

TextPropertyItem::TextPropertyItem() : PropertyItem() {
    _graphicsProxyWidget = new QGraphicsProxyWidget(this);

    _lineEdit = new QLineEdit();
    _lineEdit->setFixedWidth(180);

    _graphicsProxyWidget->setWidget(_lineEdit);

    _boundingRect = _graphicsProxyWidget->boundingRect();
}

void TextPropertyItem::configure(const IPropertyPtr & prop) {
    _property = std::dynamic_pointer_cast<TextProperty>(prop);

    _lineEdit->setText(_property->getValue());

    connect(_lineEdit, &QLineEdit::textEdited, _property.get(), &TextProperty::setValue);
    connect(_property.get(), &TextProperty::valueChanged, _lineEdit, [this]() {
        _lineEdit->setText(_property->getValue());
	});
}

QRectF TextPropertyItem::boundingRect() const {
    return _boundingRect;
}

void TextPropertyItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    _graphicsProxyWidget->paint(painter, option, widget);
}
