#include <iostream>
#include <sstream>
#include <list>
#include <iostream>

#include <ctime>
#include <boost/asio.hpp>

#include "filterDirectoryBrowsing.h"
#include "TypeToString.hpp"
#include "StringToType.hpp"
#include "Utils.h"

filterDirectoryBrowsing::filterDirectoryBrowsing(zia::IConfiguration* conf) : _configuration(conf)
{
}

filterDirectoryBrowsing::~filterDirectoryBrowsing(void)
{
}

/*********************************************************************/

std::size_t	filterDirectoryBrowsing::getObjectSize() const
{
  return (sizeof(*this));
}

void	filterDirectoryBrowsing::constructObject(void* storage) const
{
  new (storage) filterDirectoryBrowsing(this->_configuration);
}

int	filterDirectoryBrowsing::getPriority() const
{
  return (1);
}

/*********************************************************************/

void	filterDirectoryBrowsing::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

/*********************************************************************/

std::string	filterDirectoryBrowsing::getDayTimeToString() const
{
  char          buffer[26];
  time_t        now = time(0);
  ctime_r(&now, buffer);
  std::string	temp(buffer);
  temp.erase(temp.find("\n"));
  return (temp);
}

void	filterDirectoryBrowsing::uriCat(std::string& result, const std::string& rootDir, std::string uri) const
{
  if ('/' == uri[0])
    uri.erase(0, 1);
  boost::filesystem::path rootPath(boost::filesystem::system_complete(boost::filesystem::path(rootDir)));
  if (uri != "")
    {
      boost::filesystem::path URIPath(uri);
      result = boost::filesystem::complete(boost::filesystem::system_complete(boost::filesystem::complete(URIPath, rootPath))).string();
    }
  else
    result = rootPath.string();
}

/*********************************************************************/

size_t	filterDirectoryBrowsing::fillListFiles(boost::filesystem::path const & path,
					       std::string const & rootDirectory,
					       std::ostream& osResponseBody,
					       bool isHead) const

{
  boost::filesystem::directory_iterator		dir_itr_end;
  std::list<std::string>			files;
  for (boost::filesystem::directory_iterator dir_itr((path)); dir_itr != dir_itr_end; ++dir_itr)
    files.push_front(dir_itr->path().filename());
  files.sort();

  std::string	temp(path.string());
  std::string	tmp;
  if ('/' == temp[temp.size() - 1])
    tmp = "";
  else
    {

      temp.erase(0, ((path.parent_path().string().size() < rootDirectory.size()) ? rootDirectory.size() : path.parent_path().string().size()));
      if (temp[0] == '/')
	temp.erase(0, 1);
      tmp = temp + "/";
    }

  std::list<std::string>::const_iterator	it = files.begin();
  std::list<std::string>::const_iterator	itEnd = files.end();
  std::string	tempBody;
  for (; it != itEnd; ++it)
    tempBody += "<li><a href=\"" + tmp + *it + "\">" + *it + "</a></li>";
  if (false == isHead)
    osResponseBody << tempBody;
  return (tempBody.size());
}

size_t	filterDirectoryBrowsing::fillBodyResponse(const zia::network::IConnection& con,
						  boost::filesystem::path const & path,
						  std::string const & rootDirectory,
						  std::ostream& osResponseBody,
						  std::string const & uri,
						  bool isHead) const
{
  std::string tempBody("<?xml version=\"1.0\" encoding=\"utf-8\"?><!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\"><html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\"><head><title>Index Of : " + uri + "</title><meta http-equiv=\"Content-Language\" content=\"fr\" /><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" /></head><body><h1>Index of " + uri + "</h1><ul>");;
  if (rootDirectory != path)
    {
      std::string tmp = path.string();
      if (tmp[tmp.size() - 1] == '/')
	tmp.erase(tmp.size() - 1);
      boost::filesystem::path temp(tmp);
      boost::filesystem::path ppd = temp.parent_path();
      boost::filesystem::path rt(rootDirectory);
      std::string pd;
      if (ppd == rt)
	pd = "";
      else
	pd = ppd.string();

      pd.erase(0, rootDirectory.size());
      if (pd == "")
	pd.push_back('/');
      if (pd[0] == '/')
	tempBody+=  "<li><a href=\"" + pd + "\"> Parent Directory</a></li>";
      else
	tempBody+=  "<li><a href=\"/" + pd + "\"> Parent Directory</a></li>";
    }
  size_t	sizeBody = tempBody.size();
  if (false == isHead)
    osResponseBody << tempBody;
  sizeBody += this->fillListFiles(path, rootDirectory, osResponseBody, isHead);
  tempBody = "</ul><address>Zia Server (Tech3's Corporation) at " + con.getServer().getHostName() + " - Port " + typeToString(con.getServer().getPort()) + "</address> <p><a href=\"http://validator.w3.org/check?uri=referer\"><img src=\"http://www.w3.org/Icons/valid-xhtml10\" alt=\"Valid XHTML 1.0 Strict\" height=\"31\" width=\"88\" /></a></p></body></html>";
  if (false == isHead)
    osResponseBody << tempBody;
  return (sizeBody + tempBody.size());
}

void	filterDirectoryBrowsing::fillHeaderResponse(const zia::http::IRequestHeader& rh,
						    zia::http::IResponseHeader& rr,
						    size_t sizeBody) const
{
  rr.setVMajor(rh.getVMajor());
  rr.setVMinor(rh.getVMinor());
  rr.setCode(200);
  rr.setMsg("OK");
  zia::IDictionnary& headerResponse = rr.entities();
  headerResponse.set("Date", this->getDayTimeToString());
  headerResponse.set("Content-Type", "text/html");
  headerResponse.set("Content-Length", typeToString(sizeBody));
}

void	filterDirectoryBrowsing::fillResponse(const zia::network::IConnection& con,
					      const zia::http::IRequestHeader& rh,
					      zia::http::IResponseHeader& rr,
					      std::ostream& osResponseBody) const
{
  const zia::IDictionnary&	dictionnary = this->_configuration->getHive("Main");
  std::string			rootDirectory = dictionnary.get("RootDirectory");
  std::string realpath = Utils::getRealPath(rootDirectory , rh.getPath());
  boost::filesystem::path	path(realpath);

  // make cofee
  if ((path.normalize()).string().find(rootDirectory) != 0)
    path = rootDirectory;
  std::string tmp = path.string();
  if ('.' == tmp[(tmp).size() - 1])
    (tmp).erase((tmp).size() - 1);
  path = tmp;
  realpath.erase(0, rootDirectory.size());
  if (realpath == "")
    realpath.push_back('/');
  if (boost::filesystem::is_directory(path))
    {
      std::size_t	sizeBody = this->fillBodyResponse(con, path, rootDirectory, osResponseBody, realpath, rh.getMethod() == "HEAD");
      this->fillHeaderResponse(rh, rr, sizeBody);
      rr.readyToSend();
    }
}

/*********************************************************************/

zia::filter::Status	filterDirectoryBrowsing::processBody(const zia::network::IConnection& con,
							     zia::http::IRequestHeader& rh,
							     zia::http::IResponseHeader& rr,
							     std::istream&,
							     std::ostream& osResponseBody)
{
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;
  if ((rh.getMethod() == "GET" || rh.getMethod() == "HEAD") && this->_configuration != 0)
    {
      this->fillResponse(con, rh, rr, osResponseBody);
      status.translation = zia::filter::Status::TAKEOVER;
    }
  else
    status.translation = zia::filter::Status::DECLINE;
  return (status);
}

zia::filter::Status	filterDirectoryBrowsing::processBodyEnding(const zia::network::IConnection& con,
								   zia::http::IRequestHeader& rh,
								   zia::http::IResponseHeader& rr,
								   std::ostream& osResponseBody)
{
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;

  if (rh.getMethod() == "GET" || rh.getMethod() == "HEAD")
    {
      this->fillResponse(con, rh, rr, osResponseBody);
      status.translation = zia::filter::Status::TAKEOVER;
    }
  else
    status.translation = zia::filter::Status::DECLINE;
  return (status);
}
