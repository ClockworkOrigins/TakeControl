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

#include "Dialog.h"

#include "Connection.h"
#include "INode.h"
#include "NodeFactory.h"

#include <QJsonArray>

using namespace tc::core;

Dialog::Dialog(const QString & name) : _name(name) {}

QString Dialog::getName() const {
	return _name;
}

QJsonObject Dialog::save() const {
	QJsonObject json;
	json["Name"] = _name;

	QJsonArray nodes;

	int counter = 0;

	for (const auto & node : _nodes) {
		QJsonObject jsonNode;
		node->setID(counter++);
		node->write(jsonNode);
		nodes << jsonNode;
	}

	json["Nodes"] = nodes;

	QJsonArray connections;
	
	for (const auto & connection : _connections) {
		QJsonObject jsonConnection;
		connection->write(jsonConnection);
		connections << jsonConnection;
	}

	json["Connections"] = connections;

	return json;
}

DialogPtr Dialog::load(const QJsonObject & json) {
	if (!json.contains("Name")) return nullptr;
	
	QString name = json["Name"].toString();
	
	auto c = std::make_shared<Dialog>(name);

	if (json.contains("Nodes")) {
		auto nodes = json["Nodes"].toArray();

		for (auto node : nodes) {
			const auto jsonNode = node.toObject();

			auto nodePtr = NodeFactory::instance()->create(jsonNode);

			if (!nodePtr) continue;

			c->_nodes << nodePtr;
		}
	}

	if (json.contains("Connections")) {
		auto connections = json["Connections"].toArray();

		for (auto connection : connections) {
			const auto jsonConnection = connection.toObject();

			auto connectionPtr = std::make_shared<Connection>(nullptr, 0, nullptr);
			connectionPtr->read(jsonConnection, c->_nodes);

			c->_connections << connectionPtr;
		}
	}

	return c;
}

void Dialog::addNode(const INodePtr & node) {
	Q_ASSERT(!_nodes.contains(node));

	if (_nodes.contains(node)) return;

	_nodes << node;
}

void Dialog::removeNode(const INodePtr & node) {
	_nodes.removeAll(node);
}

QList<INodePtr> Dialog::getNodes() const {
	return _nodes;
}

void Dialog::addConnection(const ConnectionPtr & connection) {
	Q_ASSERT(!_connections.contains(connection));

	if (_connections.contains(connection)) return;

	_connections << connection;
}

void Dialog::removeConnection(const ConnectionPtr & connection) {
	_connections.removeAll(connection);
}

QList<ConnectionPtr> Dialog::getConnections() const {
	return _connections;
}
