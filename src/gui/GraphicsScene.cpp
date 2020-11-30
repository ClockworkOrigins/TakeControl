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

#include "GraphicsScene.h"

#include "ConnectorItem.h"
#include "GraphicsView.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

using namespace tc::gui;

GraphicsScene::GraphicsScene(QObject * par) : QGraphicsScene(par) {}

QPointF GraphicsScene::getMousePosition() const {
    return _mousePosition;
}

void GraphicsScene::setView(GraphicsView * graphicsView) {
    _graphicsView = graphicsView;
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    _mousePosition = event->scenePos();

    const auto itemList = items();

    for (auto * i : itemList) {
        const auto br = i->boundingRect();
    	
        auto pos = i->scenePos();
    	
        pos.setX(pos.x() + br.left());
        pos.setY(pos.y() + br.top());
    	
        if (pos.x() > _mousePosition.x()) continue;
        if (pos.x() + br.width() < _mousePosition.x()) continue;

        if (pos.y() > _mousePosition.y()) continue;
        if (pos.y() + br.height() < _mousePosition.y()) continue;

        auto * ci = dynamic_cast<ConnectorItem *>(i);

        if (!ci) continue;

        if (ci->getType() == ConnectorItem::Type::Input) continue;

        pos.setX(pos.x() + br.width() / 2);
        pos.setY(pos.y() + br.height() / 2);

        _graphicsView->startDrawConnection(pos);

        _connectorItem = ci;

        break;
    }
	
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * event) {
    _mousePosition = event->scenePos();

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {
    _mousePosition = event->scenePos();

    _graphicsView->stopDrawConnection();

    const auto itemList = items();

    if (_connectorItem) {
        for (auto * i : itemList) {
            const auto br = i->boundingRect();

            auto pos = i->scenePos();

            pos.setX(pos.x() + br.left());
            pos.setY(pos.y() + br.top());

            if (pos.x() > _mousePosition.x()) continue;
            if (pos.x() + br.width() < _mousePosition.x()) continue;

            if (pos.y() > _mousePosition.y()) continue;
            if (pos.y() + br.height() < _mousePosition.y()) continue;

            auto * ci = dynamic_cast<ConnectorItem *>(i);

            if (!ci) continue;

            if (ci->getType() == ConnectorItem::Type::Output) continue;

            emit addConnection(_connectorItem->getNode(), _connectorItem->getOutput(), ci->getNode());

            break;
        }
        _connectorItem = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}
