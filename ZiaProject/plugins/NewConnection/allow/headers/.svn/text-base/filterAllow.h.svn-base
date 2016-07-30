#ifndef FILTERALLOW_H_
# define FILTERALLOW_H_

#include "zia_api/IConfiguration.h"
#include "zia_api/filter/INewConnection.h"

class	filterAllow : public zia::filter::INewConnection
{
 public:
  filterAllow(zia::IConfiguration* conf = 0);
  ~filterAllow();

  void				setConfigurator(zia::IConfiguration* conf);

  virtual std::size_t		getObjectSize() const;
  virtual void			constructObject(void* storage) const;
  virtual int			getPriority() const;

  virtual zia::filter::Status	newConnection(zia::network::IConnection& con);

 private:
  bool			isEqual(const unsigned char ip[4], const unsigned char ip2[4]) const;
  void			fillByteIP(unsigned char& byte, std::string& banIP) const;
  void			fillIP(unsigned char byte[4], std::string& banIP) const;

 private:
  zia::IConfiguration*		_configuration;
};

#endif // FILTERALLOW_H_
