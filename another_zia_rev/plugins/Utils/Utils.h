/// \file
#ifdef _WIN32
# include <Windows.h>
#endif

#ifndef UTILS_H_

#define UTILS_H_
#define BOOST_HAS_THREADS

#include <sstream>
#include <time.h>
#include <string>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/fstream.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_month.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "zia_api/http/IRequestHeader.h"
#include "zia_api/network/IConnection.h"

namespace Utils
{
  bool		existPath(const std::string& path);
  bool		isDirectory(const std::string& realPath);
  bool		hasVariable(const std::string& path);
  std::string	URLDecode(const std::string& path);
  std::string	URLEncode(const std::string& path);
  std::string	getRealPath(const std::string& rootdir, const std::string& path);
  std::string	getDate(void);

  void		uriCat(std::string& result, const std::string& rootDir, const std::string& uri);
  void		setCgiEnv(const zia::network::IConnection& con,
			  zia::http::IRequestHeader &rh,
			  std::istream& is,
			  const zia::IDictionnary& ziaConf);
  bool		setEnv(const std::string& name,const std::string& value, int i = 0);
}


#endif // UTILS_H_
