#ifndef PLUGINGZIP_H_
#define PLUGINGZIP_H_

#include "zia_api/IPlugin.h"
#include "zia_api/IConfiguration.h"

class filterGzip;

class	pluginGzip : public zia::IPlugin
{
 public:
  pluginGzip(void);
  ~pluginGzip(void);

  virtual unsigned int						getVersion() const;
  virtual const std::string&					getName() const;
  virtual const std::vector<const zia::filter::IFilter*>&	getFilters() const;
  virtual void							setLogger(zia::ILogger* logger);
  virtual void							setConfigurator(zia::IConfiguration*);

 private:
  filterGzip*					_encode;
  std::vector<const zia::filter::IFilter*>	_filters;
  zia::ILogger*					_logger;
};

#endif // PLUGINGZIP_H_
