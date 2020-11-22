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

#include "gui/PropertyItem.h"

class QGraphicsProxyWidget;
class QLineEdit;

namespace tc {
namespace gui {

	class TC_GUI_API TextPropertyItem : public QObject, public PropertyItem {
	public:
        TextPropertyItem();
		
        void configure(const core::IPropertyPtr & prop) override;

    protected:
        QRectF boundingRect() const override;
		void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;

    private:
        core::TextPropertyPtr _property;
        QGraphicsProxyWidget * _graphicsProxyWidget = nullptr;
        QLineEdit * _lineEdit = nullptr;

        QRectF _boundingRect;
	};

} /* namespace gui */
} /* namespace tc */
