/// \file

#ifdef _WIN32
#include "stdint.h"
#endif

#include "zia_api/filter/INewConnection.h"
#include "zia_api/filter/IBodyDecoder.h"
#include "zia_api/filter/IBodyEncoder.h"
#include "zia_api/filter/IBodyProcessing.h"
#include "zia_api/filter/IClosedConnection.h"
#include "zia_api/filter/IInputDecoder.h"
#include "zia_api/filter/IOutputEncoder.h"

#include "Session.h"
#include "RequestHeaderGrammar.hpp"
#include "ConnectionHttp.h"
#include "HookType.h"

using namespace BOOST_SPIRIT_CLASSIC_NS;

Session::FctExecHook	Session::_tabFctExecHook[] =
  {
    &Session::execNewConnection,
    &Session::execInputDecoder,
    &Session::execBodyDecoder,
    &Session::execBodyProcessing,
    &Session::execBodyEncoder,
    &Session::execOutputEncoder,
    &Session::execClosedConnection
  };


/*********************************************************************/
Session::Session( ConnectionHttp & con) : _connection(con)
{
  this->clear();
}

Session::~Session()
{
  if (this->_response != 0)
    delete this->_response; // peut faire une erreur si deja free ds ConnectionHttp
  if (this->_hookFilter.size() > 0)
    {
      HookManager * man = HookManager::getInstance();
      man->clearHook(this->_hookFilter, static_cast<HookType>(this->_curHook));
    }
}

/*********************************************************************/

//Traitement du buffer, parsing ou envoi dans les hooks
int	Session::treatBuffer(boost::array<char, 4096>& buffer, size_t length)
{
  std::cout << "..........................................................................."<<std::endl;
  for (unsigned int i = 0; i < length; ++i)
    {
      std::cout << buffer[i];
      this->_buffer << buffer[i];
    }
  std::cout << std::endl;
  if (!this->_inTreatment)
    {
      if (std::string::npos == this->_buffer.str().find("\r\n\r\n"))
	return (1);
      request_header_grammar	myGrammar;
      parse_info<> info = parse(this->_buffer.str().c_str(), myGrammar[var(this->_request) = arg1]);
      if (info.full)
	{
	  std::cout << "-------------------------\nParsing succeeded\n-------------------------\n";
	  this->_inTreatment = true;
	  int ind = this->_buffer.str().find("\r\n\r\n");
	  std::cout << "la fin du header se termine a " << ind + 4 << "voici le buffer " << this->_buffer.str() << std::endl;
 	  char c;
	  for (int i = 0; i < (ind + 4); ++i)
	    {
	      this->_buffer >> c;
	      std::cout << i << ":" << c << "<---";
	    }
	  std::cerr << "<--- fin de la consomation\n";
	}
      else
	{
	  std::cout << "-------------------------\nParsing failed\nStopped at: \": " << info.stop << "\"\n-------------------------\n";
	  return (1);
	}
    }
  if (this->_inTreatment)
    {
      int ind;
      while ((ind = this->exec()) != 0)
	{
	  if (ind == 2)
	    return (1);
	}
      if (this->_response->getHeader().sent())
	{
	  std::cout << "---------> I send a response (" << this->_buffer.str().size() << ")<--------" << std::endl;
	  this->_response->getBody().str(this->_buffer.str());
	  static_cast<ConnectionHttp &>(this->_connection).sendResponse(this->_response);
	  this->_response = 0;
	}
      this->clear();
    }
  return (1);
}

void	Session::clear()
{
  this->_request.clear();
  this->_response = new HttpResponse;
  this->_curHook = static_cast<int>(INPUT_DECODER);
  this->_inTreatment = false;
  HookManager * man = HookManager::getInstance();
  man->getHook(this->_hookFilter, static_cast<HookType>(this->_curHook));
  this->_curFilter = this->_hookFilter.begin();
  this->_buffer.str("");
  this->_buffer1.str("");
}

bool	Session::nextHook()
{

  HookManager * man = HookManager::getInstance();
  man->clearHook(this->_hookFilter, static_cast<HookType>(this->_curHook));
  ++(this->_curHook);
  if (!man->getHook(this->_hookFilter, static_cast<HookType>(this->_curHook)))
    return (false);
  this->_curFilter = this->_hookFilter.begin();
  return (true);
}

void	Session::freeHook()
{
  //  std::cerr<< "Session::freeHook()" << std::endl;
  HookManager * man = HookManager::getInstance();
  man->clearHook(this->_hookFilter, static_cast<HookType>(this->_curHook));
}

/**********************just for debug***********************************************/
std::ostream&	operator<<(std::ostream& os, zia::filter::Status& st)
{
  return (os << "\nstatus::error : " << ((st.error == zia::filter::Status::SUCCESS) ? "SUCCESS" : "FATAL_ERROR" ) <<
	  "\nstatus::authorization : " << ((st.authorization == zia::filter::Status::DENY) ? "DENY" : "ACCEPT") <<
	  "\nstatus::translation : " << ((st.translation == zia::filter::Status::TAKEOVER) ? "TAKEOVER" : "DECLINE") <<
	  "\nstatus::persistence : " << ((st.persistence == zia::filter::Status::ALIVE) ? "ALIVE" : "REMOVEME") << std::endl);
}
/*********************************************************************/

bool		Session::manageStatus(zia::filter::Status & st)
{
  std::cerr<< "Session::manageStatus()" << std::endl << st;
  HookManager * man = HookManager::getInstance();
  if (st.translation == zia::filter::Status::TAKEOVER)
    {
      std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator tmp = this->_hookFilter.begin();
      for (;tmp != this->_hookFilter.end(); ++tmp)
	{
	  if (tmp != this->_curFilter)
	    {
	      man->clearFilter(*tmp, static_cast<HookType>(this->_curHook));
	      tmp = this->_hookFilter.erase(tmp);
	    }
	}
    }
  if (st.persistence == zia::filter::Status::REMOVEME)
    {
      man->clearFilter(*(this->_curFilter), static_cast<HookType>(this->_curHook));
      this->_curFilter = this->_hookFilter.erase(this->_curFilter);
    }
  else  if (st.translation == zia::filter::Status::DECLINE)
    ++this->_curFilter;
  if (st.persistence == zia::filter::Status::ALIVE)
    {
      std::cout <<"Alive" << std::endl;
      return false;
    }
  return true;
}

int		Session::exec()
{
  std::cout << "Exec du Hook (" << this->_curHook << ") whith size == " << this->_hookFilter.size()<< std::endl;
  zia::filter::Status	res;
  bool		alive;
  while (this->_hookFilter.size() != 0)
    {
      std::cout << "-----------------" << std::endl;
      this->_curFilter = this->_hookFilter.begin();
      alive = true;
      for (;this->_curFilter != this->_hookFilter.end();)
	{
	  std::cout << "Voila le istream == " << this->_buffer.str() << "<---\n";
	  std::cout << "++ Before: BufferSize == " << this->_buffer.str().size()<< std::endl;
	  res = (this->*(this->_tabFctExecHook)[this->_curHook])();
	  this->switchBuffer();
	  std::cout << "++ After: BufferSize == " << this->_buffer.str().size()<< std::endl;
	  alive = manageStatus(res);
	}
      if (!alive)
	return (2);
    }
  return (!this->nextHook() ? 0 : 1);
}

zia::filter::Status		Session::execNewConnection()
{
  return static_cast<zia::filter::INewConnection *>((*this->_curFilter).second)->newConnection(this->_connection);
}

zia::filter::Status		Session::execInputDecoder()
{
  std::cout << "Exec InputDecoder"<< std::endl;
  return  static_cast<zia::filter::IInputDecoder *>((*this->_curFilter).second)->inputDecode(this->_connection, this->_buffer, this->_buffer1, this->_response->getBody());
}

zia::filter::Status		Session::execBodyDecoder()
{
  std::cout << "Exec BodyDecoder\tNb Filtres : "<< this->_hookFilter.size() << std::endl;
  return  static_cast<zia::filter::IBodyDecoder *>((*this->_curFilter).second)->bodyDecode(
											     this->_connection,
											     this->_request.getHeader(),
											     this->_response->getHeader(),
											     this->_buffer,
											     this->_buffer1,
											     this->_response->getBody()
											     );
}


zia::filter::Status		Session::execBodyProcessing()
{
  std::cout << "Exec BodyProcessing\tNb Filtres : "<< this->_hookFilter.size() << std::endl;
  return  static_cast<zia::filter::IBodyProcessing *>((*this->_curFilter).second)->processBody(
											       this->_connection,
											       this->_request.getHeader(),
											       this->_response->getHeader(),
											       this->_buffer,
											       this->_buffer1
											       );
}

zia::filter::Status		Session::execBodyEncoder()
{
  std::cout << "Exec BodyEncoder\tNb Filtres : "<< this->_hookFilter.size() << std::endl;
  return  static_cast<zia::filter::IBodyEncoder *>((*this->_curFilter).second)->bodyEncode(
											     this->_connection,
											     this->_request.getHeader(),
											     this->_response->getHeader(),
											     this->_buffer,
											     this->_response->getBody());
}

zia::filter::Status		Session::execOutputEncoder()
{
  std::cout << "Exec OutputEncoder\tNb Filtres : "<< this->_hookFilter.size() << std::endl;
  return  static_cast<zia::filter::IOutputEncoder *>((*this->_curFilter).second)->outputEncode(
												 this->_connection,
												 this->_buffer,
												 this->_response->getBody());
}

zia::filter::Status		Session::execClosedConnection()
{
  std::cout << "Exec ClosedConnection\tNb Filtres : "<< this->_hookFilter.size() << std::endl;
  return  static_cast<zia::filter::IClosedConnection *>((*this->_curFilter).second)->closedConnection(this->_connection);
}

void		Session::switchBuffer()
{
  std::cout << "-- Alter Buffer"<< std::endl;
  std::string tmp = this->_buffer1.str();
  this->_buffer.str("");
  this->_buffer1.str("");
  this->_buffer <<  tmp;
}

int		Session::exec_NewConnection()
{
  zia::filter::Status	res;
  bool		alive;
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator it;
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >           hook;
  HookManager * man = HookManager::getInstance();
  man->getHook(hook, NEW_CONNECTION);
  while (hook.size() != 0)
    {
      std::cout << "-----------------" << std::endl;
      alive = true;
      for (it = hook.begin(); it != hook.end();)
	{
	  res = (this->*(this->_tabFctExecHook)[this->_curHook])();
	  alive = manageStatus(res);
	}
      if (!alive)
	return (2);
    }
  return (1);
}


/*********************************************************************/

// zia::filter::IFilter *			Session::getFilter() const
// {
//   return ((*this->_curFilter).second);
// }


// HttpResponse *			Session::getResponse() const
// {
//   return (this->_response);
// }


// void				Session::freeFilter(zia::filter::IFilter * rm)
// {
//   //std::cerr<< "Session::freeFilter()" << std::endl;
//   HookManager * man = HookManager::getInstance();
//   std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	it = this->_hookFilter.begin();
//   std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	ite = this->_hookFilter.end();
//   for (;it != ite; ++it)
//     if ((*it).second == rm)
//       {
// 	man->clearFilter(*it, static_cast<HookType>(this->_curHook));
// 	this->_hookFilter.erase(it);
// 	return ;
//       }
// }

// bool				Session::nextFilter()
// {
//   ++this->_curFilter;
//   return  (!((this->_curFilter == this->_hookFilter.end())));
// }

