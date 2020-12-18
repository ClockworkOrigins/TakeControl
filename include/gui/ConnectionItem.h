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

#include <QFont>
#include <QGraphicsItem>

namespace tc {
namespace gui {

    class ConnectorItem;
    class NodeItem;

	class TC_GUI_API ConnectionItem : public QObject, public QGraphicsItem {
		Q_OBJECT
		Q_INTERFACES(QGraphicsItem)
		
	public:
        ConnectionItem(NodeItem * startNodeItem, int startNodeOutput, NodeItem * endNodeItem);

	signals:
        void deleteClicked();

    protected:
        ConnectorItem * _startConnectorItem;
        ConnectorItem * _endConnectorItem;
        QPainterPath _painterPath;

        bool _hovered = false;
		
		QRectF boundingRect() const override;
		void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
		void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

        bool isHovered() const;

		QPainterPath shape() const override;

		void contextMenuEvent(QGraphicsSceneContextMenuEvent * event) override;
	};

} /* namespace gui */
} /* namespace tc */
