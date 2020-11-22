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

#include "nodes/OutputNode.h"

#include "TakeControlConfig.h"

#include "IProperty.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;

TEST(OutputNode, ctor) {
	const INodePtr outputNode = std::make_shared<OutputNode>();

	const auto properties = outputNode->getProperties();
	
	ASSERT_EQ(2, properties.count());
	ASSERT_EQ("Character", properties[0]->getType());
	ASSERT_EQ("Text", properties[1]->getType());

	const auto type = outputNode->getType();

	ASSERT_EQ("Output", type);
}

TEST(OutputNode, save) {
	const OutputNode outputNode;
	
	QJsonObject json;
	outputNode.write(json);
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/OutputNode/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	ASSERT_EQ(referenceData, jsonData);
}

TEST(OutputNode, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/OutputNode/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	OutputNode outputNode;
	outputNode.read(json);

	const auto properties = outputNode.getProperties();

	ASSERT_EQ(2, properties.count());
	ASSERT_EQ("Character", properties[0]->getType());
	ASSERT_EQ("Text", properties[1]->getType());
}
