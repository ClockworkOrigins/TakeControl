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

#include "ConnectionItem.h"

#include "ConnectorItem.h"
#include "NodeItem.h"

#include <QPainter>

using namespace tc::core;
using namespace tc::gui;

constexpr qreal BEZIER_OFFSET = 40.0;

ConnectionItem::ConnectionItem(NodeItem * startNodeItem, int startNodeOutput, NodeItem * endNodeItem) : QGraphicsItem() {
    setFlags(ItemIsSelectable);
    setAcceptHoverEvents(true);
	
    _startConnectorItem = startNodeItem->getOutputConnector(startNodeOutput);
    _endConnectorItem = endNodeItem->getInputConnector();
}

QRectF ConnectionItem::boundingRect() const {
    const auto startBr = _startConnectorItem->mapToScene(_startConnectorItem->boundingRect().center());
    const auto endBr = _endConnectorItem->mapToScene(_endConnectorItem->boundingRect().center());

    const auto left = std::min(startBr.x(), endBr.x());
    const auto top = std::min(startBr.y(), endBr.y());
    const auto right = std::max(startBr.x(), endBr.x());
    const auto bottom = std::max(startBr.y(), endBr.y());
	
    return QRectF(left, top, right - left, bottom - top);
}

void ConnectionItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *) {
    const auto br = boundingRect();

    QColor color = Qt::white;
    if (isSelected()) {
        color = QColor(68, 192, 255);
    } else if (isHovered()) {
        color = QColor(50, 112, 144);
    }
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
    painter->setPen(QPen(QBrush(color), 2));

    const auto startPoint = mapFromScene(_startConnectorItem->scenePos()) + _startConnectorItem->boundingRect().center();
    const auto endPoint = mapFromScene(_endConnectorItem->scenePos()) + _endConnectorItem->boundingRect().center();
	
    QPainterPath painterPath;
    painterPath.moveTo(startPoint);
    painterPath.cubicTo(startPoint, startPoint + QPointF(BEZIER_OFFSET, 0), startPoint + (endPoint - startPoint) / 2);
    painterPath.cubicTo(startPoint + (endPoint - startPoint) / 2, endPoint - QPointF(BEZIER_OFFSET, 0), endPoint);
    painter->drawPath(painterPath);
}

void ConnectionItem::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    _hovered = true;
    update();
}

void ConnectionItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    _hovered = false;
    update();
}

bool ConnectionItem::isHovered() const {
    return _hovered;
}
