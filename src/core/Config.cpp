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

#include "Config.h"

#include <QApplication>
#include <QDir>
#include <QLocale>
#include <QProcessEnvironment>
#include <QRegularExpression>
#include <QSettings>
#include <QTranslator>

using namespace tc::core;

QSettings * Config::IniParser = nullptr;

void Config::init() {
	auto appdata = QProcessEnvironment::systemEnvironment().value("APPDATA");
	const QRegularExpression regEx("[A-Za-z0-9:\\\\/_\\- ]+");
	if (!regEx.match(appdata).hasMatch()) {
		appdata = appdata[0] + ":/Users/Public";
	}

	if (appdata.isEmpty()) return;

	appdata = appdata.replace("\\", "/");
	appdata += "/Clockwork Origins/TakeControl";
	{
		const QDir baseDir(appdata);
		if (!baseDir.exists()) {
			bool b = baseDir.mkpath(baseDir.absolutePath());
			Q_UNUSED(b)
		}
		Q_ASSERT(baseDir.exists());
	}

	QFile oldIni(qApp->applicationDirPath() + "/TakeControl.ini");
	if (oldIni.exists()) {
		if (!QFileInfo::exists(appdata + "/TakeControl.ini")) {
			oldIni.rename(appdata + "/TakeControl.ini");
		}
	}
	IniParser = new QSettings(appdata + "/TakeControl.ini", QSettings::IniFormat);

	QString language = IniParser->value("MISC/language", "").toString();
	if (language.isEmpty()) {
		const QLocale locale = QLocale::system();
		if (locale.language() == QLocale::Language::German) {
			language = "Deutsch";
		} else {
			language = "English";
		}
		IniParser->setValue("MISC/language", language);
	}	

	updateLanguage(language);
}

void Config::finish() {
	delete IniParser;
}

void Config::updateLanguage(const QString & language) {
	auto * translator = new QTranslator(qApp);
	if (language == "Deutsch") {
		QLocale::setDefault(QLocale("de_DE"));
		translator->load(qApp->applicationDirPath() + "/de_DE");
	} else {
		QLocale::setDefault(QLocale("en_US"));
		translator->load(qApp->applicationDirPath() + "/en_US");
	}
	qApp->installTranslator(translator);
}
