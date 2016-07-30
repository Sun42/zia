/// \file

#ifdef _WIN32
#include "stdint.h"
#endif

#include "Session.h"
#include "RequestHeaderGrammar.hpp"
#include "ConnectionHttp.h"
#include "HookType.h"
#include "StringToType.hpp"
#include "TypeToString.hpp"

using namespace BOOST_SPIRIT_CLASSIC_NS;

//#warning "un des deux buffers est peut etre en trop devrait etre ds le httpResponse !!!"

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
  for (unsigned int i = 0; i < length; ++i)
    this->_bufferIn << buffer[i];
  if (!this->_inTreatment)
    {
      std ::string tmp = this->_bufferIn.str();
      size_t end = tmp.find("\r\n\r\n");
      if (std::string::npos == end)
	return (1);
      request_header_grammar	myGrammar;
      parse_info<> info = parse(tmp.c_str(), myGrammar[var(this->_request) = arg1]);
      if (info.full)
	{
	  this->_inTreatment = true;
	  for (size_t i = 0; i < (end + 4); ++i)
	    this->_bufferIn.get();
	  length = (this->_bufferIn.rdbuf())->in_avail();
	}
      else
	{
	  return (1);
	}
    }
  if (this->_inTreatment)
    return this->treat(length);
  return (1);
}

int		Session::treat(size_t length)
{
  int ind;
  this->_bodylengthRead += length;
  while ((ind = this->exec()) != 0)
    {
      if (ind == 2)
	return (1);
    }
  //std::errcerr << "---------> I send a response<--------" << std::endl;
  this->checkConnection();
  if (this->_response->getHeader().sent())
    {
      this->_response->getBody() << this->_bufferOut.rdbuf();
      //      std::cout << "Display \n---------\n" << this->_response->getBody() << "\n-----------" <<std::endl;
      return 3;
    }
  else
    {
      this->fillNotFound();
      return 4;
    }
}


void	Session::clear()
{
  this->_request.clear();
  this->_response = new HttpResponse;
  this->_curHook = static_cast<int>(NEW_CONNECTION);
  this->_inTreatment = false;
  HookManager * man = HookManager::getInstance();
  man->getHook(this->_hookFilter, static_cast<HookType>(this->_curHook));
  this->_curFilter = this->_hookFilter.begin();
  this->_bodylengthRead = 0;
  this->_isFull = false;
  this->_bufferIn.str("");
  this->_bufferOut.str("");
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
  std::cerr<< "Session::manageStatus()" << std::endl ;//<< st;
  HookManager * man = HookManager::getInstance();
  if (st.translation == zia::filter::Status::TAKEOVER)
    {
      std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator tmp = this->_hookFilter.begin();
      for (;tmp != this->_hookFilter.end();)
	{
	  if (tmp != this->_curFilter)
	    {
	      std::cerr << "Appel a clearfilter" << std::endl;
	      man->clearFilter(*tmp, static_cast<HookType>(this->_curHook));
	      std::cerr << "FinAppel a clearfilter" << std::endl;
	      tmp = this->_hookFilter.erase(tmp);
	      std::cerr << "FinHookFilter" << std::endl;
	    }
	  else
	    ++tmp;
	}
    }
  std::cerr << "AVANT IFF REMOVEME" << std::endl;
  if (st.persistence == zia::filter::Status::REMOVEME)
    {
      std::cerr << "1Appel a clearfilter" << std::endl;
      man->clearFilter(*(this->_curFilter), static_cast<HookType>(this->_curHook));
      std::cerr << "1FinAppel a clearfilter" << std::endl;
      this->_curFilter = this->_hookFilter.erase(this->_curFilter);
      std::cerr << "1FinHookFilter" << std::endl;
    }
  else  if (st.translation == zia::filter::Status::DECLINE)
    {
      std::cerr <<"DECLINE" << std::endl;
      ++this->_curFilter;
      std::cerr <<"FINDECLINE" << std::endl;
    }
  std::cerr << "APRES IFF ET ELSEIF REMOVEME" << std::endl;
  if (st.persistence == zia::filter::Status::ALIVE)
    {
      std::cerr <<"Alive" << std::endl;
      return false;
    }
  std::cerr <<"FinTotal" << std::endl;
  return true;
}

void		Session::isFull()
{
  std::string cl = this->_request.getHeader().entities().get("Content-Length");
  if (cl == "")
    {
      //std::errcerr << "Content-Length == \"\"" << std::endl;
      this->_isFull = true;
    }
  else
    {
      if (stringToType<int>(cl) == this->_bodylengthRead && this->_bufferIn.rdbuf()->in_avail() == 0)
	{
	  this->_isFull = true;
	}
      else
	this->_isFull = false;
    }
}

int		Session::exec()
{
  zia::filter::Status	res;
  bool		alive;
  while (this->_hookFilter.size() != 0)
    {
      this->_curFilter = this->_hookFilter.begin();
      alive = true;
      this->isFull();
       for (;this->_curFilter != this->_hookFilter.end();)
	{
	  //std::errcerr << "++ Before: BufferSize == " << this->_bufferIn.rdbuf()->in_avail()<< std::endl;
	  res = (this->*(this->_tabFctExecHook)[this->_curHook])();
	  //std::errcerr << "++ After: BufferSize == " << this->_bufferOut.rdbuf()->in_avail()<< std::endl;
	  alive = manageStatus(res);
	}
      if (!alive && !this->_isFull)
	return (2);
    }
  return (!this->nextHook() ? 0 : 1);
}

bool			Session::checkConnection()
{
  const zia::IDictionnary& dic = this->_request.getHeader().entities();
  if (dic.get("Connection").find("close") != std::string::npos)
    {
      this->_connection.shutDown();
      return false;
    }
  return true;
}

HttpResponse *		Session::getResponse()
{
  return (this->_response);
}

void			Session::fillNotFound()
{
  RequestHeader&        rh = this->_request.getHeader();
  ResponseHeader&	rr = this->_response->getHeader();
  rr.setVMajor(rh.getVMajor());
  rr.setVMinor(rh.getVMinor());
  rr.setCode(404);
  rr.setMsg("Not Found");
  zia::IDictionnary& headerResponse = rr.entities();
  headerResponse.set("Content-Type", "text/html");

  const std::string	error404 = "<?xml version=\"1.0\" encoding=\"utf-8\"?><!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\"><head><title>Erreur 404</title><meta http-equiv=\"Content-Language\" content=\"fr\" /><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" /></head><body><h1>404: Page Not Found</h1><hr>The requested URL was not found on this server.</body></html>";
  headerResponse.set("Content-Length", typeToString<std::size_t>(error404.length()));
}
