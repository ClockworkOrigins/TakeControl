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

#include "core/IGamePlugin.h"

namespace tc {
namespace plugins {
namespace redskiesascensiondemo {

	class RedSkiesAscensionDemoPlugin : public QObject, public core::IGamePlugin {
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "tc.game.IGamePlugin")
		Q_INTERFACES(tc::core::IGamePlugin)

	private:
		QString getName() const override;
		QStringList getSupportedNodes() const override;
		core::IConditionPtr createCondition(const QString & conditionType, const QJsonObject & json) const override;
		core::INodePtr createNode(const QString & nodeType) const override;
		gui::NodeItem * createNodeItem(const QString & nodeType) const override;
		core::IPropertyPtr createProperty(const QString & propertyType) const override;
		gui::PropertyItem * createPropertyItem(const QString & propertyType) const override;
		QStringList getSupportedLanguages() const override;
		bool exportProject(const core::ProjectPtr & project) const override;

		QStringList getCharacterProperties() const override;
	};

} /* namespace redskiesascensiondemo */
} /* namespace plugins */
} /* namespace tc */
