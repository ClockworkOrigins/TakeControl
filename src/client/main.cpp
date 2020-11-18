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

#include "MainWindow.h"

#include "core/Config.h"

#include <QApplication>

using namespace tc::client;
using namespace tc::core;

int main(int argc, char ** argv) {
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	
	QApplication app(argc, argv);

	Config::init();

	int ret;
	{
		MainWindow wnd;

		wnd.show();

		ret = QApplication::exec();
	}
	
	return ret;
}
