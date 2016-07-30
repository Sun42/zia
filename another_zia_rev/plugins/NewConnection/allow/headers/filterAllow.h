#ifndef FILTERALLOW_H_
# define FILTERALLOW_H_

#define WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <iostream>

#include "zia_api/IConfiguration.h"
#include "zia_api/ILogger.h"
#include "zia_api/filter/INewConnection.h"

class	filterAllow : public zia::filter::INewConnection
{
 public:
  filterAllow(zia::IConfiguration* conf = 0, zia::ILogger* logger = 0);
  ~filterAllow();

  void				setConfigurator(zia::IConfiguration*);
  void				setLogger(zia::ILogger*);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

  virtual zia::filter::Status	newConnection(zia::network::IConnection& con);

 private:
  template<class T, long unsigned int N>
    void			fillArray(boost::array<T, N>& temp, unsigned char const * bytes);

  std::string&			trim(std::string& str) const;
  bool				checkBannedList(boost::asio::ip::address const &, std::string &, std::string&);

 private:
  zia::IConfiguration*		_configuration;
  zia::ILogger*			_logger;
};

#endif // FILTERALLOW_H_
