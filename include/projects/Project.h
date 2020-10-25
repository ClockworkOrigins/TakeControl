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

#include <memory>

#include <QString>

namespace tc {
namespace utils {
	class Character;
	class Dialog;
}
namespace projects {

	class Project {
	public:
		Project() = default;
		Project(const QString & path, const QString & name, const QString & type);

		static bool supports(const QString & path);
		
		void save(const QList<std::shared_ptr<utils::Character>> & characters, const QList<std::shared_ptr<utils::Dialog>> & dialogs) const;
		void load(const QString & path, QList<std::shared_ptr<utils::Character>> & characters, QList<std::shared_ptr<utils::Dialog>> & dialogs);

		QString getName() const;

	private:
		QString _path;
		QString _name;
		QString _type;
	};
	typedef std::shared_ptr<Project> ProjectPtr;

} /* namespace projects */
} /* namespace tc */
