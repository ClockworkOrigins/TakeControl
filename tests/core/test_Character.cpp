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

#include "Character.h"

#include "TakeControlConfig.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>

using namespace tc::core;

TEST(Character, ctor) {
	const Character c("Test");
	ASSERT_EQ("Test", c.getName());
}

TEST(Character, save) {
	const Character c("SaveTest");
	
	const QJsonObject json = c.save();
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/Character/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadWrite));

	const auto referenceData = referenceFile.readAll();

	ASSERT_EQ(referenceData, jsonData);
}

TEST(Character, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/Character/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadWrite));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	const auto c = Character::load(json);
	ASSERT_TRUE(c);

	ASSERT_EQ("LoadTest", c->getName());
}
