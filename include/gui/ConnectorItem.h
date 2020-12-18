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

	class TC_GUI_API ConnectorItem : public QGraphicsItem {
        Q_INTERFACES(QGraphicsItem)
		
	public:
		enum class Type {
			Input,
			Output
		};
		
        ConnectorItem(Type type, const core::INodePtr & node, int output);
		
		QRectF boundingRect() const override;

        Type getType() const;
        core::INodePtr getNode() const;
        int getOutput() const;

        static qreal getHeight();

    protected:
        Type _type;
        core::INodePtr _node;
        int _output;
		
        bool _hovered = false;

		void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
		void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
		void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

        bool isHovered() const;
	};

} /* namespace gui */
} /* namespace tc */
