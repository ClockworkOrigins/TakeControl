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

#include "Connection.h"

#include "TakeControlConfig.h"

#include "NodeFactory.h"

#include "gtest/gtest.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace tc::core;

TEST(Connection, save) {
	auto startNode = NodeFactory::instance()->create("And");
	auto endNode = NodeFactory::instance()->create("And");
	
	const Connection c(startNode, 0, endNode);

	startNode->setID(0);
	endNode->setID(1);
	
	QJsonObject json;
	c.write(json);
	
	const QJsonDocument jsonDoc(json);
	const auto jsonData = jsonDoc.toJson();

	QFile referenceFile(TESTFOLDER + "/core/resources/Connection/save.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	ASSERT_EQ(referenceData, jsonData);
}

TEST(Connection, load) {
	auto startNode = NodeFactory::instance()->create("And");
	auto endNode = NodeFactory::instance()->create("And");

	startNode->setID(5);
	endNode->setID(2);

	const QList<INodePtr> nodes = { startNode, endNode };
	
	QFile referenceFile(TESTFOLDER + "/core/resources/Connection/load.json");
	ASSERT_TRUE(referenceFile.open(QIODevice::ReadOnly));

	const auto referenceData = referenceFile.readAll();

	const auto jsonDoc = QJsonDocument::fromJson(referenceData);
	const auto json = jsonDoc.object();

	auto c = std::make_shared<Connection>(nullptr, 0, nullptr);
	c->read(json, nodes);

	ASSERT_EQ(startNode, c->getStartNode());
	ASSERT_EQ(endNode, c->getEndNode());
	ASSERT_EQ(1, c->getStartNodeOutput());
}
