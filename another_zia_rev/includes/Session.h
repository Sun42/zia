/// \file

#ifndef SESSION_H_
# define SESSION_H_

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
  typedef zia::filter::Status (Session::*FctExecHook)();

 public:
  Session(ConnectionHttp &);
  ~Session();

  int				treatBuffer(boost::array<char, 4096>&, size_t);
  bool				exec_NewConnection();
  HttpResponse *		getResponse();
  void				clear();

 private:
  Session();
  Session(Session const &);
  Session &			operator=(Session const &);

  bool				nextHook();
  void				freeHook();
  bool				manageStatus(zia::filter::Status &);
  int				exec();
  void				isFull();
  int				treat(size_t);
  void				fillNotFound();

  zia::filter::Status		execNewConnection();
  zia::filter::Status		execInputDecoder();
  zia::filter::Status		execBodyDecoder();
  zia::filter::Status		execBodyProcessing();
  zia::filter::Status		execBodyEncoder();
  zia::filter::Status		execOutputEncoder();
  zia::filter::Status		execClosedConnection();
  void				switchBuffer();
  bool				checkConnection();

 private:
  std::stringstream								_bufferIn;
  std::stringstream								_bufferOut;
  HttpRequest									_request;
  HttpResponse *								_response;
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >::iterator	_curFilter;
  std::list<std::pair< PoolFilter * const, zia::filter::IFilter *> >		_hookFilter;
  int										_curHook;
  ConnectionHttp &								_connection;
  bool										_inTreatment;
  int										_bodylengthRead;
  bool										_isFull;
  static FctExecHook								_tabFctExecHook[];

};

#endif /* SESSION_H_ */
