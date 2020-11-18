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

#include "nodesGui/PropertyItem.h"

class QComboBox;
class QCompleter;
class QGraphicsProxyWidget;

namespace tc {
namespace nodes {
    class CharacterProperty;
    typedef std::shared_ptr<CharacterProperty> CharacterPropertyPtr;
} /* namespace nodes */
namespace nodesGui {

	class TC_NODESGUI_API CharacterPropertyItem : public QObject, public PropertyItem {
	public:
        CharacterPropertyItem();
		
        void configure(const nodes::IPropertyPtr & prop) override;

    protected:
        QRectF boundingRect() const override;
		void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;

    private:
        nodes::CharacterPropertyPtr _property;
        QGraphicsProxyWidget * _graphicsProxyWidget = nullptr;
        QComboBox * _comboBox = nullptr;

        QRectF _boundingRect;

        void updateCharacters();
        void updateCompleter(const QStringList & options);
	};

} /* namespace nodesGui */
} /* namespace tc */
