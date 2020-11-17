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

#include "nodes/NodeFactory.h"

#include <QJsonArray>

using namespace tc::nodes;
using namespace tc::utils;

Dialog::Dialog(const QString & name) : _name(name) {}

QString Dialog::getName() const {
	return _name;
}

QJsonObject Dialog::save() const {
	QJsonObject json;
	json["Name"] = _name;

	QJsonArray nodes;

	for (const auto & node : _nodes) {
		QJsonObject jsonNode;
		node->write(jsonNode);
		nodes << jsonNode;
	}

	json["Nodes"] = nodes;

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
