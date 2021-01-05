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

#include "gui/PropertyItem.h"

class QComboBox;
class QCompleter;
class QLabel;
class QGraphicsProxyWidget;
class QVBoxLayout;

namespace tc {
namespace gui {

	class TC_GUI_API TranslateableTextPropertyItem : public QObject, public PropertyItem {
	public:
        TranslateableTextPropertyItem();
		
        void configure(const core::IPropertyPtr & prop) override;

    protected:
        QRectF boundingRect() const override;
		void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;

    private:
        core::TranslateableTextPropertyPtr _property;
        QGraphicsProxyWidget * _graphicsProxyWidget = nullptr;
        QComboBox * _comboBox = nullptr;
        QLabel * _label = nullptr;

        QRectF _boundingRect;

        QMetaObject::Connection _currentConnection;

        void updateTranslateableTexts();
        void updateCompleter(const QStringList & options);
        void updatePreview();
	};

} /* namespace gui */
} /* namespace tc */
