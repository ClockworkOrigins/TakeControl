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

#pragma once

#include "core/CoreTypes.h"

#include "GuiParameters.h"

#include <QGraphicsScene>

namespace tc {
namespace gui {

    class ConnectorItem;
    class GraphicsView;

	class TC_GUI_API GraphicsScene : public QGraphicsScene {
		Q_OBJECT
		
	public:
        explicit GraphicsScene(QObject * par);
		
        QPointF getMousePosition() const;

        void setView(GraphicsView * graphicsView);

	signals:
        void addConnection(const core::INodePtr & startNode, int startNodeOutput, const core::INodePtr & endNode);
		
    private:
        QPointF _mousePosition;
        ConnectorItem * _connectorItem = nullptr;
        GraphicsView * _graphicsView = nullptr;

		void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
		void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;
	};

} /* namespace gui */
} /* namespace tc */
