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

#include "nodes/OrNode.h"

#include "TakeControlConfig.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;

TEST(OrNode, ctor) {
	const INodePtr orNode = std::make_shared<OrNode>();

	const auto properties = orNode->getProperties();
	
	ASSERT_EQ(0, properties.count());

	const auto type = orNode->getType();

	ASSERT_EQ("Or", type);
	ASSERT_EQ(0, orNode->getID());
}

TEST(OrNode, save) {
	const INodePtr orNode = std::make_shared<OrNode>();
	
	orNode->setID(2);
	
	QJsonObject json;
	orNode->write(json);
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/OrNode/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	QString text = QString::fromLatin1(jsonData);

	ASSERT_EQ(referenceData, jsonData);
}

TEST(OrNode, load) {
	QFile referenceFile(TESTFOLDER + "/core/resources/OrNode/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	const INodePtr orNode = std::make_shared<OrNode>();
	orNode->read(json);

	const auto properties = orNode->getProperties();

	ASSERT_EQ(0, properties.count());
	ASSERT_EQ(1, orNode->getID());
}
