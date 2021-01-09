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

#include "GraphicsView.h"

#include "GraphicsScene.h"

#include <QPaintEvent>

using namespace tc::gui;

GraphicsView::GraphicsView(QGraphicsScene * graphicsScene) : QGraphicsView(graphicsScene) {}

void GraphicsView::startDrawConnection(QPointF startPoint) {
    _startPoint = mapFromScene(startPoint);
    _drawConnection = true;

    scene()->update();
}

void GraphicsView::stopDrawConnection() {
    _drawConnection = false;
}

void GraphicsView::paintEvent(QPaintEvent * event) {
    QGraphicsView::paintEvent(event);

    if (!_drawConnection) return;

    QPainter painter(viewport());
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setPen(QPen(QBrush(QColor(Qt::white)), 2));

    auto * graphicsScene = dynamic_cast<GraphicsScene *>(scene());

    auto mousePos = graphicsScene->getMousePosition();
    mousePos = mapFromScene(mousePos);
	
    QPainterPath painterPath;
    painterPath.moveTo(_startPoint);
    painterPath.cubicTo(_startPoint, _startPoint + (mousePos - _startPoint) / 2, mousePos);
    painter.drawPath(painterPath);

    scene()->update();
}

void GraphicsView::wheelEvent(QWheelEvent * event) {
    QGraphicsView::wheelEvent(event);

    const double angle = event->angleDelta().y();
    const double factor = std::pow(1.0015, angle);

    auto * graphicsScene = dynamic_cast<GraphicsScene *>(scene());
    const auto mousePos = graphicsScene->getMousePosition();

    scale(factor, factor);
    centerOn(mousePos);

    const QPointF deltaViewportPos = mapFromScene(mousePos) - QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
    const QPointF viewportCenter = mapFromScene(mousePos) - deltaViewportPos;

    centerOn(mapToScene(viewportCenter.toPoint()));
}
