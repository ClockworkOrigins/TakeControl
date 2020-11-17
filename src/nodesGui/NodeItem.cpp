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

#include "nodesGui/NodeItem.h"

#include "nodes/interfaces/INode.h"

#include <QFontMetrics>
#include <QPainter>

using namespace tc;
using namespace tc::nodesGui;

NodeItem::NodeItem() : QGraphicsItem() {
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);

    _textFont.setPointSize(16);
}

void NodeItem::configure(const nodes::INodePtr & node) {
    _name = node->getType();
}

QRectF NodeItem::boundingRect() const {
    return QRectF(-100, -50, 200, 100);
}

void NodeItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    const auto br = boundingRect();
	
    if (isSelected()) {
        painter->setBrush(QBrush(QColor(68, 192, 255)));
    } else if (isHovered()) {
        painter->setBrush(QBrush(QColor(50, 112, 144)));
    } else {
		painter->setBrush(QBrush(QColor(0, 0, 0)));
    }
    painter->drawRect(br);


    auto innerRect = br;
    innerRect.setX(innerRect.x() + 2);
    innerRect.setY(innerRect.y() + 2);
    innerRect.setWidth(innerRect.width() - 2);
    innerRect.setHeight(innerRect.height() - 2);
	
    painter->fillRect(innerRect, QBrush(QColor(57, 57, 57)));
	
    const QFontMetrics fm = QFontMetrics(_textFont);
    const auto lblWidth = fm.width(_name);
    const auto lblHeight = fm.height();

    const QPen pen(QColor(193, 193, 193));
    painter->setFont(_textFont);
    painter->setPen(pen);
    painter->drawText(-lblWidth / 2, br.y() + lblHeight, _name);
}

QVariant NodeItem::itemChange(GraphicsItemChange change, const QVariant & value) {
    if (change == ItemSelectedHasChanged) {
        update();
    }
	
    return value;
}

void NodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    _hovered = true;
    update();
}

void NodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    _hovered = false;
    update();
}

bool NodeItem::isHovered() const {
    return _hovered;
}