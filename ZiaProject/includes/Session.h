/// \file

#ifndef SESSION_H_
#define SESSION_H_

#include <sstream>
#include <list>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <boost/array.hpp>

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HookManager.h"

class ConnectionHttp;

/*! \class Session
 * \brief Gestion de requetes
 *
 * Gere l'ensemble des requetes d'un client, c'est a dire parsing plus execution de la requete.
 */

class	Session
{
 public:
  Session(ConnectionHttp &);
  ~Session();

  int				treatBuffer(boost::array<char, 4096>&, size_t);

  typedef zia::filter::Status (Session::*FctExecHook)();

 private:
  Session();
  Session(Session const &);
  Session &			operator=(Session const &);

  //zia::filter::IFilter *	getFilter() const;
  //HttpResponse *		getResponse() const;
  //HttpRequest &			getRequest() const;
  /*   void				freeFilter(zia::filter::IFilter *); // inutilise */
  /*   bool				nextFilter(); // inutilise */
  void				clear();
  bool				nextHook();
  void				freeHook();

  bool				manageStatus(zia::filter::Status &);
  int				exec();
  int				exec_NewConnection();
  zia::filter::Status		execNewConnection();
  zia::filter::Status		execInputDecoder();
  zia::filter::Status		execBodyDecoder();
  zia::filter::Status		execBodyProcessing();
  zia::filter::Status		execBodyEncoder();
  zia::filter::Status		execOutputEncoder();
  zia::filter::Status		execClosedConnection();
  void				switchBuffer();

 private:
  std::stringstream								_buffer;
  std::stringstream								_buffer1;
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	_curFilter;
  HttpRequest									_request;
  HttpResponse *								_response;
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >		_hookFilter;
  int										_curHook;
  ConnectionHttp &								_connection;
  bool										_inTreatment;
  static FctExecHook   							_tabFctExecHook[];
};

#endif /* SESSION_H_ */
