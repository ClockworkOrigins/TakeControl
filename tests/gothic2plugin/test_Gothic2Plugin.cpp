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

#include "plugins/PluginLoader.h"

#include "TakeControlConfig.h"

#include "core/Project.h"

#include "gothic2plugin/Gothic2Plugin.h"

#include "gtest/gtest.h"

#include <QFile>

using namespace tc::core;
using namespace tc::plugins;
using namespace tc::plugins::gothic2plugin;

class Gothic2PluginTest : public ::testing::Test {
protected:
	void SetUp() override {
		const auto * plugin = _loader.getGamePlugin("Gothic 2");

		ASSERT_TRUE(plugin);

		_plugin = dynamic_cast<const Gothic2Plugin *>(plugin);

		ASSERT_TRUE(_plugin);
	}
	
	QString convert(const DialogPtr & dialog) const {
		return _plugin->convert(dialog, _project->getCharacters(), _project->getTexts());
	}

	void init(const QString & testName) {
		_project = std::make_shared<Project>();
		_project->load(QString("%1/gothic2plugin/resources/%2/G2.json").arg(TESTFOLDER).arg(testName), [this](const QString &) { return _plugin; });

		QFile f(QString("%1/gothic2plugin/resources/%2/Dialog.d").arg(TESTFOLDER).arg(testName));

		const auto b = f.open(QIODevice::ReadOnly);

		ASSERT_TRUE(b);

		const auto data = f.readAll();
		_referenceDialogString = QString::fromLatin1(data);
	}

	ProjectPtr _project;
	PluginLoader _loader;
	const Gothic2Plugin * _plugin = nullptr;
	QString _referenceDialogString;
};

TEST_F(Gothic2PluginTest, importantDialog) {
	const PluginLoader loader;
		
	init("ImportantDialog");

	const auto dialogs = _project->getDialogs();
	ASSERT_FALSE(dialogs.isEmpty());

	const auto convertedDialog = convert(dialogs[0]);

	ASSERT_EQ(_referenceDialogString, convertedDialog);
}

TEST_F(Gothic2PluginTest, endDialog) {
	const PluginLoader loader;

	init("EndDialog");

	const auto dialogs = _project->getDialogs();
	ASSERT_FALSE(dialogs.isEmpty());

	const auto convertedDialog = convert(dialogs[0]);

	ASSERT_EQ(_referenceDialogString, convertedDialog);
}
