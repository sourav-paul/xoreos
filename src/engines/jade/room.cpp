/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file engines/jade/room.cpp
 *  A room within a Jade Empire area.
 */

#include "common/error.h"

#include "graphics/aurora/model.h"

#include "engines/aurora/resources.h"
#include "engines/aurora/model.h"

#include "engines/jade/room.h"

namespace Engines {

namespace Jade {

Room::Room(const Common::UString &resRef, uint32 id, float x, float y, float z) :
	_model(0) {

	load(resRef, id, x, y, z);
}

Room::~Room() {
	unload();
}

void Room::load(const Common::UString &resRef, uint32 id, float x, float y, float z) {
	if (resRef == "****")
		return;

	indexOptionalArchive(Aurora::kArchiveRIM, resRef + "-a.rim", 500 + id, &_resources);

	_model = loadModelObject(resRef);
	if (!_model)
		throw Common::Exception("Can't load room model \"%s\"", resRef.c_str());

	_model->setPosition(x, y, z);
}

void Room::unload() {
	delete _model;
	_model = 0;

	ResMan.undo(_resources);
}

void Room::show() {
	if (_model)
		_model->show();
}

void Room::hide() {
	if (_model)
		_model->hide();
}

} // End of namespace Jade

} // End of namespace Engines