// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __CAESARIA_ROME_DINIVITY_H_INCLUDED__
#define __CAESARIA_ROME_DINIVITY_H_INCLUDED__

#include "core/referencecounted.hpp"
#include "core/scopedptr.hpp"
#include "game/predefinitions.hpp"
#include "game/service.hpp"
#include "core/variant.hpp"
#include "objects/constants.hpp"
#include "config.hpp"

namespace religion
{

#define BIG_TEMPLE_TYPE(a) object::big_##a##_temple
#define SML_TEMPLE_TYPE(a) object::small_##a##_temple

class Divinity : public ReferenceCounted
{
public:
  typedef enum { bigTemple, smallTemple } TempleSize;
  virtual std::string name() const = 0;
  virtual float relation() const = 0;
  virtual Service::Type serviceType() const = 0;
  virtual const gfx::Picture& picture() const = 0;
  virtual void updateRelation( float income, PlayerCityPtr city ) = 0;
  virtual DateTime lastFestivalDate() const = 0;
  virtual void load( const VariantMap& vm ) = 0;
  virtual VariantMap save() const = 0;
  virtual void setEffectPoint( int value ) = 0;
  virtual void setRelation(float value) = 0;
  virtual void setPicture(gfx::Picture picture) = 0;
  virtual void setService(const std::string& service) = 0;
  virtual void setName(const std::string& name) = 0;
  virtual object::Type templeType( TempleSize size ) const = 0;
  virtual void setInternalName(const std::string &newName) = 0;
  virtual int wrathPoints() const = 0;
  virtual void checkAction( PlayerCityPtr city ) = 0;
  virtual std::string internalName() const = 0;
};

PREDEFINE_CLASS_SMARTLIST(Divinity,List)

}//end namespace religion

#endif //__CAESARIA_DINIVITY_H_INCLUDED__
