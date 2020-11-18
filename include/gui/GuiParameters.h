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

#include <QObject>

// Dynamic library import/export macro
#ifndef TC_GUI_API
	#if defined Q_OS_WIN
		#ifdef TCGui_EXPORTS
			#define TC_GUI_API __declspec(dllexport)
		#else
			#define TC_GUI_API __declspec(dllimport)
		#endif
	#elif defined Q_OS_UNIX
		#define TC_GUI_API
	#else
		#define TC_GUI_API
	#endif
#endif
