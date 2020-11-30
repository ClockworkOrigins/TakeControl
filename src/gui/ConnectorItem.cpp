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

#include "ConnectorItem.h"

#include "GraphicsScene.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

using namespace tc::core;
using namespace tc::gui;

constexpr qreal DIMENSION = 15.0;

ConnectorItem::ConnectorItem(Type type, const INodePtr & node, int output) : QGraphicsItem(), _type(type), _node(node), _output(output) {
    setFlags(ItemStacksBehindParent);
    setAcceptHoverEvents(true);
}

QRectF ConnectorItem::boundingRect() const {
    return QRectF(0, -DIMENSION / 2, DIMENSION, DIMENSION);
}

ConnectorItem::Type ConnectorItem::getType() const {
    return _type;
}

INodePtr ConnectorItem::getNode() const {
    return _node;
}

int ConnectorItem::getOutput() const {
    return _output;
}

qreal ConnectorItem::getHeight() {
    return DIMENSION;
}

void ConnectorItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
	
    const auto br = boundingRect();
	
    if (isSelected()) {
        painter->setBrush(QBrush(QColor(68, 192, 255)));
    } else if (isHovered()) {
        painter->setBrush(QBrush(QColor(50, 112, 144)));
    } else {
		painter->setBrush(QBrush(QColor(0, 0, 0)));
    }
    painter->drawRoundRect(br, 50, 50);

    auto innerRect = br;
    innerRect.setX(innerRect.x() + 2);
    innerRect.setY(innerRect.y() + 2);
    innerRect.setWidth(innerRect.width() - 2);
    innerRect.setHeight(innerRect.height() - 2);
	
	painter->setBrush(QBrush(QColor(57, 57, 57)));
    painter->drawRoundRect(innerRect, 50, 50);
}

void ConnectorItem::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    _hovered = true;
    update();
}

void ConnectorItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    _hovered = false;
    update();
}

bool ConnectorItem::isHovered() const {
    return _hovered;
}
