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

#include "storage.hpp"
#include "core/math.hpp"
#include "core/variant_map.hpp"
#include "core/variant_list.hpp"
#include "core/utils.hpp"
#include "good/productmap.hpp"
#include "core/logger.hpp"

namespace good
{

class SmStock : public good::Stock, public ReferenceCounted
{
public:
  typedef SmartPtr<SmStock> Ptr;

  static Ptr create( good::Product type )
  {
    Ptr ret( new SmStock() );
    ret->setType( type );
    ret->drop();

    return ret;
  }
private:
  SmStock() {}
};

typedef std::vector<SmStock::Ptr> StockList;

class Storage::Impl
{
public:
  StockList stocks;
  int capacity;

  void reset()
  {
    stocks.clear();
    for( auto& goodType : good::all() )
    {
      stocks.push_back( SmStock::create( goodType ) );
    }
  }
};

Storage::Storage() : _gsd( new Impl )
{
  _gsd->capacity = 0;
  _gsd->reset();
}

void Storage::setCapacity(const int maxQty) { _gsd->capacity = maxQty;}
int Storage::capacity() const {  return _gsd->capacity; }

int Storage::qty() const
{
  int qty = 0;
  for( const auto& stock : _gsd->stocks )
    qty += stock->qty();

  return qty;
}

good::Stock& Storage::getStock(const Product& goodType){  return *(_gsd->stocks[goodType].object());}

ProductMap Storage::details() const
{
  ProductMap ret;
  for( const auto& cstock : _gsd->stocks )
    ret[ cstock->type() ] += cstock->qty();

  return ret;
}

int Storage::qty(const good::Product& goodType) const{  return _gsd->stocks[goodType]->qty();}
int Storage::capacity(const good::Product& goodType) const{  return _gsd->stocks[goodType]->capacity();}

void Storage::setCapacity(const good::Product& goodType, const int maxQty)
{
  if( goodType == good::any() )
  {
    for( auto& gtype : good::all() )
    {
      _gsd->stocks[ gtype ]->setCapacity( maxQty );
    }
  }
  else
  {
    _gsd->stocks[goodType]->setCapacity( maxQty );
  }
}

void Storage::setQty(const good::Product& goodType, const int currentQty){  _gsd->stocks[goodType]->setQty( currentQty );}

int Storage::getMaxStore(const good::Product goodType)
{
  int freeRoom = 0;
  if( !isDevastation() )
  {
    int globalFreeRoom = capacity() - qty();

    // current free capacity
    int goodFreeRoom = _gsd->stocks[ goodType ]->freeQty();

    // remove all storage reservations
    for( auto& reserved : _getStoreReservations() )
    {
      globalFreeRoom -= reserved.qty();

      if( reserved.type() == goodType )
        goodFreeRoom -= reserved.qty();
    }

    freeRoom = math::clamp( goodFreeRoom, 0, globalFreeRoom );
  }

  return freeRoom;
}

bool Storage::applyStorageReservation(good::Stock &stock, const int reservationID)
{
  good::Stock reservedStock = getStorageReservation(reservationID, true);

  if (stock.type() != reservedStock.type())
  {
    Logger::warning( "SimpleGoodStore:GoodType does not match reservation");
    return false;
  }

  if (stock.qty() < reservedStock.qty())
  {
    Logger::warning( "SimpleGoodStore:Quantity does not match reservation");
    return false;
  }

  int amount = reservedStock.qty();
  _gsd->stocks[ reservedStock.type() ]->push( amount );
  stock.pop( amount );
  return true;
}

bool Storage::applyRetrieveReservation(good::Stock& stock, const int reservationID)
{
  good::Stock reservedStock = getRetrieveReservation(reservationID, true);

  if (stock.type() != reservedStock.type())
  {
    Logger::warning( "SimpleGoodStore:GoodType does not match reservation");
    return false;
  }

  if( stock.capacity() < stock.qty() + reservedStock.qty())
  {
    Logger::warning( "SimpleGoodStore:Quantity does not match reservation");
    return false;
  }

  int amount = reservedStock.qty();
  good::Stock& currentStock = getStock(reservedStock.type());
  currentStock.pop( amount );
  stock.push( amount );
  return true;
}

void Storage::confirmDeliver(Product type, int qty, unsigned int tag, const DateTime& time)
{
  _consumers().append( type, qty, tag, time );
}

VariantMap Storage::save() const
{
  VariantMap stream = good::Store::save();

  stream[ "max" ] = _gsd->capacity;

  VariantList stockSave;
  for( auto& stockInfo : _gsd->stocks )
    stockSave.push_back( stockInfo->save() );

  stream[ "stock" ] = stockSave;

  return stream;
}

void Storage::load( const VariantMap& stream )
{
  if( stream.empty() )
  {
    Logger::warning( "!!! Storage::load from empty stream" );
    return;
  }

  good::Store::load( stream );
  _gsd->capacity = (int)stream.get( "max" );

  _gsd->reset();
  VariantList stockSave = stream.get( "stock" ).toList();
  for( auto& sotckInfo : stockSave )
  {
    SmStock::Ptr stock = SmStock::create( good::none );
    stock->load( sotckInfo.toList() );
    _gsd->stocks[ stock->type() ] = stock;
  }
}

Storage::~Storage(){}

void Storage::resize(const Store &other )
{
  setCapacity( other.capacity() );

  for( auto& goodType : good::all() )
  {
    setCapacity( goodType, other.capacity( goodType ) );
  }
}

}//end namespace good
