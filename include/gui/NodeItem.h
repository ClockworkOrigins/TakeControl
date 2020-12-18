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

#include <memory>

#include "core/CoreTypes.h"

#include "GuiParameters.h"

#include <QFont>
#include <QGraphicsItem>

namespace tc {
namespace gui {

    class ConnectorItem;

	class TC_GUI_API NodeItem : public QGraphicsItem {
        Q_INTERFACES(QGraphicsItem)
		
	public:
        NodeItem();
		
        virtual void configure(const core::INodePtr & node);

        ConnectorItem * getInputConnector() const;
        ConnectorItem * getOutputConnector(int output) const;

    protected:
        QFont _textFont;
        QString _name;
        qreal _labelHeight;
        core::INodePtr _node;

        bool _hovered = false;

        ConnectorItem * _inputConnectorItem = nullptr;
        QList<ConnectorItem *> _outputConnectorItems;
		
		QRectF boundingRect() const override;
		void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;
		void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

        bool isHovered() const;
	};

} /* namespace gui */
} /* namespace tc */
