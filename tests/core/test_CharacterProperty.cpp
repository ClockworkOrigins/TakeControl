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

#include "properties/CharacterProperty.h"

#include "TakeControlConfig.h"

#include "CoreTypes.h"
#include "IProperty.h"

#include "utils/UndoStack.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;
using namespace tc::utils;

class CharacterPropertyTest : public ::testing::Test {
protected:
	void SetUp() override {
		UndoStack::instance()->clear();

		characterProperty = std::make_shared<CharacterProperty>();
		prop = characterProperty;
	}
	
	CharacterPropertyPtr characterProperty;
	IPropertyPtr prop;
};

TEST_F(CharacterPropertyTest, ctor) {
	ASSERT_EQ("Character", prop->getType());
	ASSERT_EQ("", characterProperty->getValue());
}

TEST_F(CharacterPropertyTest, valueChange) {
	const QString testText = QStringLiteral("Character 1");

	int count = 0;
	QObject::connect(characterProperty.get(), &IProperty::valueChanged, [&count]() { count++; });
	
	ASSERT_EQ("", characterProperty->getValue());

	characterProperty->setValue(testText);

	ASSERT_EQ(testText, characterProperty->getValue());
	ASSERT_EQ(1, count);

	UndoStack::instance()->undo();

	ASSERT_EQ("", characterProperty->getValue());
	ASSERT_EQ(2, count);

	UndoStack::instance()->redo();

	ASSERT_EQ(testText, characterProperty->getValue());
	ASSERT_EQ(3, count);
}

TEST_F(CharacterPropertyTest, save) {
	QJsonObject json;
	prop->write(json);
	
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/CharacterProperty/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	ASSERT_EQ(referenceData, jsonData);
}

TEST_F(CharacterPropertyTest, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/CharacterProperty/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	prop->read(json);

	ASSERT_EQ("Character 1", characterProperty->getValue());
}
