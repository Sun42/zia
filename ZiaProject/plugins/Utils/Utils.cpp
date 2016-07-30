/// \file

#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "Utils.h"
#include "Dictionnary.h"

namespace Utils
{
  bool	existPath(const std::string& path)
  {
    return (boost::filesystem::exists(path));
  }

  bool	isDirectory(const std::string& realPath)
  {
    return (boost::filesystem::is_directory(realPath));
  }

  bool	hasVariable(const std::string& path)
  {
    if (path.find('?'))
      return true;
    return false;
  }

  std::string	URLDecode(const std::string& path)
  {
    std::string decoded;
    int len = path.length();

    for (int i = 0; i < len; i++)
      if (path[i] == '%')
	{
	  std::string tmp("0x0");
	  int chnum;
	  tmp.append(path.substr((i + 1), 2));
	  std::istringstream	iss(tmp.c_str());
	  iss >> std::hex >> chnum;
	  decoded += chnum;
	  i += 2;
	}
      else
	decoded += path[i];
    return (decoded);
  }

  std::string	URLEncode(const std::string& path)
  {
    std::string encoded;
    int max = path.length();
    for(int i=0; i<max; i++)
      {
        if ( (48 <= path[i] && path[i] <= 57) ||//0-9
             (65 <= path[i] && path[i] <= 90) ||//abc...xyz
             (97 <= path[i] && path[i] <= 122) || //ABC...XYZ
             (path[i]=='~' || path[i]=='!' || path[i]=='*' ||
	      path[i]=='(' || path[i]==')' || path[i]=='\''))
	  {
            encoded.append( &path[i], 1);
	  }
        else
	  {
            encoded.append("%");
	    int	tmpchar = static_cast<unsigned char>(path[i]);
	    std::ostringstream os;
	    os << std::hex << tmpchar;
	    std::istringstream is(os.str());
	    std::string tmpstr;
	    is >> tmpstr;
	    encoded.append(tmpstr);
	  }
      }
    return (encoded);
  }

  // urlDecode si besoin, delete les variables si besoin, map si besoin?
  // /ans%020wer?var=1&var=2
  //return /ziapath/ans wer
  std::string	getRealPath(const std::string& rootDir, const std::string& path)
  {
    std::string realpath;

    realpath = URLDecode(path);
    std::cerr << "DECODED STRING=> " << realpath << std::endl;
    Utils::uriCat(realpath, rootDir, realpath);
    std::cerr << "REAL PATH: " << realpath << std::endl;
    if (Utils::hasVariable(realpath))
      realpath = realpath.substr(0, realpath.find('?'));
    return (realpath);
  }

  std::string	getDate(void)
  {
#ifdef _WIN32
    std::ostringstream	ios;
    boost::gregorian::date	d1 = boost::gregorian::day_clock::local_day();
    boost::gregorian::date_facet* us_facet = new boost::gregorian::date_facet();
    ios.imbue(std::locale(std::locale::classic(), us_facet));
    boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    boost::posix_time::time_iterator titr(now, boost::posix_time::hours(1));
    boost::posix_time::ptime t = boost::posix_time::time_from_string(to_simple_string(*titr));
    us_facet->format("%a %b %d ");
    ios << d1 << t.time_of_day();
    us_facet->format(" %Y");
    ios << d1;
    delete us_facet;
    return (ios.str());
#else
    #include <ctime>
    char	buffer[26];

    time_t	now = time(0);
    std::string	timeString = ctime_r(&now, buffer);
    if (timeString.length() > 0)
      timeString.erase(timeString.find('\n'));
    return (timeString);
#endif
  }

  // Example:
  // rootDirectory = www/
  // uri = /myDir/index.php
  // result = www/myDir/index.php
  void	uriCat(std::string& result, const std::string& rootDir,
	       const std::string& uri)
  {
    //std::cerr << "URI CAT PERL" << std::endl;
    //std::cerr << "URI = " << uri << std::endl;
    //std::cerr << "ROOTDIR = " << rootDir << std::endl;

    boost::filesystem::path	absRootPath(boost::filesystem::system_complete(rootDir));

    if (uri != "/")
      {
	absRootPath /= uri;
	absRootPath.normalize();
      }
    result = absRootPath.string();

    //std::cerr << "RESULT = " << result << std::endl;
  }

  void		setCgiEnv(const zia::network::IConnection& con,
			  zia::http::IRequestHeader &rh,
			  std::istream& /*is*/,
			  const zia::IDictionnary& ziaConf)
  {
    const zia::IDictionnary& rhDico = rh.entities();
    /*const zia::network::IEndPoint& client = con.getClient();*/
    const zia::network::IEndPoint& server = con.getServer();
    //setenv("DOCUMENT_ROOT", ziaConf.get("RootDirectory").c_str(), 0);

    /*fail si set */setenv("SERVER_SOFTWARE", /*ziaConf.get("ServerName").c_str()*/"Zia", 0);
    setenv("SERVER_ADMIN", ziaConf.get("ServerAdmin").c_str(), 0);

    std::string ip = rhDico.get("Host");
    size_t pos = ip.find(':');
    ip = ip.substr(0, pos);
    setenv("HTTP_HOST", ip.c_str(), 0);

    //    faire fonction ip to string
    //     std::ostringstream servaddr;
    //     if (server.getAddress().isV4())
    //       servaddr << server.getAddress().getV4();
    //     else
    //       servaddr << server.getAddress().getV6();
    setenv("HTTP_ADDR", ip.c_str() , 0);

    std::ostringstream servport;
    servport << server.getPort();
    setenv("SERVER_PORT", servport.str().c_str(), 0);

    // recuperer port deconfig ssl et faire une comparaison => faire passer ZiaConf en IConfiguration et faire des getHive
    setenv("HTTPS", "OFF", 0);
    setenv("HTTP_USER_AGENT", rhDico.get("User-Agent").c_str(), 0);
    //fail si sette :o    setenv("REQUEST_METHOD", rh.getMethod().c_str(), 0);
  }

  bool		setEnv(const std::string& name,const  std::string& value, int i)
  {
#ifndef _WIN32
# include <stdlib.h>
    return (setenv(name.c_str(), value.c_str(), i));
#else
# include "Windows.h"
    return (SetEnvironmentVariable(name.c_str(), value.c_str()));
# endif
  }
}
