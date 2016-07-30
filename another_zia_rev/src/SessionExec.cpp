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
#include "ConnectionHttp.h"

zia::filter::Status		Session::execNewConnection()
{
  return static_cast<zia::filter::INewConnection *>((*this->_curFilter).second)->newConnection(this->_connection);
}

zia::filter::Status		Session::execInputDecoder()
{
  if (false == this->_isFull)
    return  static_cast<zia::filter::IInputDecoder *>((*this->_curFilter).second)->inputDecode(this->_connection, this->_bufferIn, this->_bufferOut, this->_response->getBody());
  return  static_cast<zia::filter::IInputDecoder *>((*this->_curFilter).second)->inputDecodeEnding(this->_connection, this->_bufferOut, this->_response->getBody());
}

zia::filter::Status		Session::execBodyDecoder()
{
  if (false == this->_isFull)
    return  static_cast<zia::filter::IBodyDecoder *>((*this->_curFilter).second)->bodyDecode(
											     this->_connection,
											     this->_request.getHeader(),
											     this->_response->getHeader(),
											     this->_bufferIn,
											     this->_bufferOut,
											     this->_response->getBody()
											     );
  return  static_cast<zia::filter::IBodyDecoder *>((*this->_curFilter).second)->bodyDecodeEnding(
												 this->_connection,
												 this->_request.getHeader(),
												 this->_response->getHeader(),
												 this->_bufferOut,
												 this->_response->getBody()
												 );
}


zia::filter::Status		Session::execBodyProcessing()
{
	std::cout << "Session::execBodyProcessing()" << std::endl;
  if (false == this->_isFull)
    return  static_cast<zia::filter::IBodyProcessing *>((*this->_curFilter).second)->processBody(
												 this->_connection,
												 this->_request.getHeader(),
												 this->_response->getHeader(),
												 this->_bufferIn,
												 this->_bufferOut
												 );
      return  static_cast<zia::filter::IBodyProcessing *>((*this->_curFilter).second)->processBodyEnding(
													 this->_connection,
													 this->_request.getHeader(),
													 this->_response->getHeader(),
													 this->_bufferOut
													 );

}

zia::filter::Status		Session::execBodyEncoder()
{
  zia::filter::Status res =   static_cast<zia::filter::IBodyEncoder *>((*this->_curFilter).second)->bodyEncode(
											     this->_connection,
											     this->_request.getHeader(),
											     this->_response->getHeader(),
											     this->_bufferOut,
											     this->_response->getBody());

  this->_bufferOut << this->_response->getBody().rdbuf();
  return (res);

//   return  static_cast<zia::filter::IBodyEncoder *>((*this->_curFilter).second)->bodyEncodeEnding(
// 												 this->_connection,
// 												 this->_request.getHeader(),
// 												 this->_response->getHeader(),
// 												 this->_response->getBody());
}

zia::filter::Status		Session::execOutputEncoder()
{
  //std::cerr << "Exec OutputEncoder\tNb Filtres : "<< this->_hookFilter.size() << std::endl;
  if (false == this->_isFull)
    return  static_cast<zia::filter::IOutputEncoder *>((*this->_curFilter).second)->outputEncode(
												 this->_connection,
												 this->_bufferIn,
												 this->_response->getBody());
  return  static_cast<zia::filter::IOutputEncoder *>((*this->_curFilter).second)->outputEncodeEnding(
												     this->_connection,
												       this->_response->getBody());
}

zia::filter::Status		Session::execClosedConnection()
{
  //std::cerr << "Exec ClosedConnection\tNb Filtres : "<< this->_hookFilter.size() << std::endl;
  return  static_cast<zia::filter::IClosedConnection *>((*this->_curFilter).second)->closedConnection(this->_connection);
}

bool		Session::exec_NewConnection()
{
  zia::filter::Status	res;
  bool			rep = true;

  for (this->_curFilter = this->_hookFilter.begin(); this->_curFilter != this->_hookFilter.end();)
    {
      res = (this->*(this->_tabFctExecHook)[this->_curHook])();
      manageStatus(res);
      if (res.authorization == zia::filter::Status::DENY)
	rep = false;
    }
  this->nextHook();
  return (rep);
}
