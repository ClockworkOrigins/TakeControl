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

#include <QGraphicsView>

class QGraphicsScene;

namespace tc {
namespace gui {

    class ConnectorItem;

	class TC_GUI_API GraphicsView : public QGraphicsView {
	public:
        explicit GraphicsView(QGraphicsScene * graphicsScene);

        void startDrawConnection(QPointF startPoint);
        void stopDrawConnection();
		
    private:
        QPointF _startPoint;
        bool _drawConnection = false;
		
		void paintEvent(QPaintEvent * event) override;
	};

} /* namespace gui */
} /* namespace tc */
