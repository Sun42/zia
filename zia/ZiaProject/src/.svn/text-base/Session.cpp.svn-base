/// \file

#include "Session.h"
#include "stdint.h"
#include "RequestHeaderGrammar.hpp"
#include "zia_api/filter/INewConnection.h"
#include "zia_api/filter/IBodyDecoder.h"
#include "zia_api/filter/IBodyEncoder.h"
#include "zia_api/filter/IBodyProcessing.h"
#include "zia_api/filter/IClosedConnection.h"
#include "zia_api/filter/IInputDecoder.h"
#include "zia_api/filter/IOutputEncoder.h"
#include "ConnectionHttp.h"

using namespace BOOST_SPIRIT_CLASSIC_NS;

Session::Session( zia::network::IConnection & con) : _connection(con)
{
  this->clear();
}

Session::~Session()
{
}

int	Session::treatBuffer(boost::array<unsigned char, 4096>& buffer, size_t length)
{
  request_header_grammar	myGrammar;
  static FctExecHook	tab[] =
    {
      &Session::execNewConnection,
      &Session::execInputDecoder,
      &Session::execBodyDecoder,
      &Session::execBodyProcessing,
      &Session::execBodyEncoder,
      &Session::execOutputEncoder,
      &Session::execClosedConnection
    };
  for (unsigned int i = 0; i < length; i++)
    this->_buffer << buffer[i];
  parse_info<> info = parse(this->_buffer.str().c_str(), myGrammar[var(this->_request) = arg1]);
  if (info.full)
    {
      std::cout << "-------------------------\n";
      std::cout << "Parsing succeeded\n";
      std::cout << "-------------------------\n";

      while ((this->*tab[this->_curHook])() != 0) ;
      if (this->_response->getHeader().sent())
	{
	  std::cout << "---------> I send a response <--------" << std::endl;
	  dynamic_cast<ConnectionHttp *>(&this->_connection)->sendResponse(this->_response);
	}
      this->clear();
    }
  else
	{
      std::cout << "-------------------------\n";
      std::cout << "Parsing failed\n";
      std::cout << "Stopped at: \": " << info.stop << "\"\n";
      std::cout << "-------------------------\n";
      return (2);
    }
  return (0);
}

void				Session::flushList()
{
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	itBegin = this->_hookFilter.begin();
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	itEnd = this->_hookFilter.end();
  for (;itBegin != itEnd;)
    itBegin = this->_hookFilter.erase(itBegin);
}


void				Session::clear()
{
  this->_request.clear();
  this->_response = new HttpResponse();
  this->_curHook = 0;
  HookManager * man = HookManager::getInstance();
  man->getHook(this->_hookFilter, static_cast<HookManager::hookType>(this->_curHook));
  this->_curFilter = this->_hookFilter.begin();
  this->_buffer.clear();
}

bool				Session::nextHook()
{
  HookManager * man = HookManager::getInstance();
  man->clearHook(this->_hookFilter, static_cast<HookManager::hookType>(this->_curHook));
  this->flushList();
  this->_curHook++;
  if (!man->getHook(this->_hookFilter, static_cast<HookManager::hookType>(this->_curHook)))
    return false;
  this->_curFilter = this->_hookFilter.begin();
  return true;
}

void				Session::freeHook()
{
  HookManager * man = HookManager::getInstance();
  man->clearHook(this->_hookFilter, static_cast<HookManager::hookType>(this->_curHook));
  this->flushList();
}

void				Session::freeFilter(zia::filter::IFilter * rm)
{
  HookManager * man = HookManager::getInstance();
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	it = this->_hookFilter.begin();
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	ite = this->_hookFilter.end();
  for (;it != ite; ++it)
    if ((*it).second == rm)
      {
	man->clearFilter(*it, static_cast<HookManager::hookType>(this->_curHook));
	this->_hookFilter.erase(it);
	return ;
      }
}

zia::filter::IFilter *			Session::getFilter()
{
  return ((*this->_curFilter).second);
}

bool				Session::nextFilter()
{
  ++this->_curFilter;
  if (this->_curFilter == this->_hookFilter.end())
    return (false);
  return (true);
}

HttpResponse *			Session::getResponse()
{
  return (this->_response);
}

void		Session::manageStatus(zia::filter::Status & st)
{
  if (st.persistence == zia::filter::Status::REMOVEME)
    this->_curFilter = this->_hookFilter.erase(this->_curFilter);
  else if (st.persistence == zia::filter::Status::ALIVE)
    ++this->_curFilter;
  if (st.translation == zia::filter::Status::TAKEOVER)
    {
      ++this->_curFilter;
      for (;this->_curFilter != this->_hookFilter.end();)
	this->_curFilter = this->_hookFilter.erase(this->_curFilter);
    }
  else if (st.translation == zia::filter::Status::DECLINE)
    ++this->_curFilter;
}

int		Session::execNewConnection()
{
  std::cout << "Exec NewConnection"<< std::endl;
  zia::filter::Status res;
  for (;this->_curFilter != this->_hookFilter.end();)
    {
      res = dynamic_cast<zia::filter::INewConnection *>((*this->_curFilter).second)->newConnection(this->_connection);
      manageStatus(res);
    }
  if (!this->nextHook())
    return (0);
  return (1);
}

int		Session::execInputDecoder()
{
  std::cout << "Exec InputDecoder"<< std::endl;
  zia::filter::Status res;
  for (;this->_curFilter != this->_hookFilter.end();)
    {
      dynamic_cast<zia::filter::IInputDecoder *>((*this->_curFilter).second)->inputDecode(this->_connection, this->_buffer, this->_buffer1, this->_response->getBody());
      manageStatus(res);
    }
  if (!this->nextHook())
    return (0);
  return (1);
}

int		Session::execBodyDecoder()
{
  std::cout << "Exec BodyDecoder"<< std::endl;
  zia::filter::Status res;
  for (;this->_curFilter != this->_hookFilter.end();)
    {
      dynamic_cast<zia::filter::IBodyDecoder *>((*this->_curFilter).second)->bodyDecode(
											this->_connection,
											this->_request.getHeader(),
											this->_response->getHeader(),
											this->_buffer,
											this->_buffer1,
											this->_response->getBody()
											);
      manageStatus(res);
    }
  if (!this->nextHook())
    return (0);
  return (1);
}


int		Session::execBodyProcessing()
{
  std::cout << "Exec BodyProcessing"<< std::endl;
  zia::filter::Status res;
  for (;this->_curFilter != this->_hookFilter.end();)
    {
      std::cout << "--------------" << std::endl;
      dynamic_cast<zia::filter::IBodyProcessing *>((*this->_curFilter).second)->processBody(this->_connection, this->_request.getHeader(), this->_response->getHeader(), this->_buffer, this->_response->getBody());
      manageStatus(res);
    }
  if (!this->nextHook())
    return (0);
  return (1);
}

int		Session::execBodyEncoder()
{
  std::cout << "Exec BodyEncoder"<< std::endl;
  zia::filter::Status res;
  for (;this->_curFilter != this->_hookFilter.end();)
    {
      dynamic_cast<zia::filter::IBodyEncoder *>((*this->_curFilter).second)->bodyEncode(this->_connection, this->_request.getHeader(), this->_response->getHeader(), this->_buffer, this->_response->getBody());
      manageStatus(res);
    }
  if (!this->nextHook())
    return (0);
  return (1);
}

int		Session::execOutputEncoder()
{
  std::cout << "Exec OutputEncoder"<< std::endl;
  zia::filter::Status res;
  for (;this->_curFilter != this->_hookFilter.end();)
    {
      dynamic_cast<zia::filter::IOutputEncoder *>((*this->_curFilter).second)->outputEncode(this->_connection,this->_buffer, this->_response->getBody());
      manageStatus(res);
    }
  if (!this->nextHook())
    return (0);
  return (1);
}

int		Session::execClosedConnection()
{
  std::cout << "Exec ClosedConnection"<< std::endl;
  zia::filter::Status res;
  for (;this->_curFilter != this->_hookFilter.end();)
    {
      dynamic_cast<zia::filter::IClosedConnection *>((*this->_curFilter).second)->closedConnection(this->_connection);
      manageStatus(res);
    }
  if (!this->nextHook())
    return (0);
  return (1);
}
