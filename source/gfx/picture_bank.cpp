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
// You should have received a createCopy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com

#include "picture_bank.hpp"

#include <cstdlib>
#include <string>
#include <memory>
#include <sys/stat.h>
#include <map>
#include <SDL.h>

#include "core/position.hpp"
#include "core/exception.hpp"
#include "game/resourcegroup.hpp"
#include "gfx/animation.hpp"
#include "game/settings.hpp"
#include "core/stringhelper.hpp"
#include "core/logger.hpp"
#include "picture_info_bank.hpp"
#include "core/foreach.hpp"
#include "loader.hpp"
#include "vfs/file.hpp"
#include "core/color.hpp"

class PictureBank::Impl
{
public:
  typedef std::map< unsigned int, Picture> Pictures;
  typedef Pictures::iterator ItPicture;
  StringArray availableExentions;

  Pictures resources;  // key=image name, value=picture
  Picture tryLoadPicture( const std::string& name );

  void setPicture( const std::string &name, SDL_Texture* texture);
  Picture makePicture(const std::string& name, SDL_Texture* texture );
};

PictureBank& PictureBank::instance()
{
  static PictureBank inst; 
  return inst;
}

void PictureBank::Impl::setPicture( const std::string &name, SDL_Texture* texture )
{
  // first: we deallocate the current picture, if any
  unsigned int picId = StringHelper::hash( name );
  Impl::ItPicture it = resources.find( picId );
  if( it != resources.end() )
  {
    SDL_DestroyTexture( it->second.texture() );
    it->second = makePicture( name, texture );
  }
  else
  {
    resources[ picId ] = makePicture( name, texture );
  }
}

void PictureBank::setPicture( const std::string &name, const Picture& pic )
{
  _d->setPicture( name, pic.texture() );
}

Picture& PictureBank::getPicture(const std::string &name)
{
  const unsigned int hash = StringHelper::hash( name );

  Impl::ItPicture it = _d->resources.find( hash );
  if( it == _d->resources.end() )
  {
    //can't find image in valid resources, try load from hdd
    const Picture& pic = _d->tryLoadPicture( name );

    if( pic.isValid() )     {      setPicture( name, pic );    }
    else    {      _d->resources[ hash ] = pic;    }

    return _d->resources[ hash ];
  }
  return it->second;
}

Picture& PictureBank::getPicture(const std::string& prefix, const int idx)
{
  std::string resource_name = StringHelper::format( 0xff, "%s_%05d", prefix.c_str(), idx );

  return getPicture(resource_name);
}

Picture PictureBank::Impl::makePicture(const std::string& name, SDL_Texture* texture)
{
   Point offset( 0, 0 );

   int dot_pos = name.find('.');
   std::string filename = name.substr(0, dot_pos);
   int w, h;
   SDL_QueryTexture( texture, 0, 0, &w, &h );

   if( texture )
   {
     // decode the picture name => to set the offset manually
     Point pic_info = PictureInfoBank::instance().getOffset( filename );

     if( pic_info == Point( -1, -1 ) )
     {
       // this is a tiled picture=> automatic offset correction
       offset.setY( h-15*( (w+2)/60 ) );   // (w+2)/60 is the size of the tile: (1x1, 2x2, 3x3, ...)
     }
     else if( pic_info == Point( -2, -2 ) )
     {
        // this is a walker picture=> automatic offset correction
        offset = Point( -w/2, int(h*3./4.) );
     }
     else
     {
        offset = pic_info;
     }
   }

   Picture pic;
   pic.init( texture, offset );
   pic.setName( filename );
   //pic.textureID() = id;

   return pic;
}

PictureBank::PictureBank() : _d( new Impl )
{
  _d->availableExentions << ".png";
  _d->availableExentions << ".bmp";
}

PictureBank::~PictureBank(){}


Picture PictureBank::Impl::tryLoadPicture(const std::string& name)
{
  vfs::Path realPath( name );  

  bool fileExist = false;
  if( realPath.extension().empty() )
  {
    foreach( itExt, availableExentions )
    {
     realPath = name + *itExt;

      if( realPath.exist() )
      {
        fileExist = true;
        break;
      }
    }
  }

  if( fileExist )
  {    
    vfs::NFile file = vfs::NFile::open( realPath );
    if( file.isOpen() )
    {
      Picture ret = PictureLoader::instance().load( file );
      return ret;
    }
  }

  Logger::warning( "PictureBank: Unknown resource %s", name.c_str() );
  return Picture::getInvalid();
}
