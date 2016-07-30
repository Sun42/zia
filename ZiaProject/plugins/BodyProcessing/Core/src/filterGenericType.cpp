#include <iostream>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/fstream.hpp>

#include "Utils.h"
#include "TypeToString.hpp"
#include "filterGenericType.h"
#include "SizeFile.hpp"

/*
TODO :
gerer l'envoi en flux continu de gros fichiers
gerer le chunk transfert
*/

static const std::string	GENERIC_TYPE_SECTION = "GenericType";

filterGenericType::filterGenericType(zia::IConfiguration* conf) : _configuration(conf)
{
}

filterGenericType::~filterGenericType(void)
{
}

inline std::size_t	filterGenericType::getObjectSize() const
{
  return (sizeof(*this));
}

inline void		filterGenericType::constructObject(void* storage) const
{
  new (storage) filterGenericType(this->_configuration);
}

inline int		filterGenericType::getPriority() const
{
  return (7);
}

void		filterGenericType::setConfigurator(zia::IConfiguration* conf)
{
  this->_configuration = conf;
}

zia::filter::Status	filterGenericType::processBody(const zia::network::IConnection& con,
						       zia::http::IRequestHeader& rh,
						       zia::http::IResponseHeader& rr,
						       std::istream& /*isRequestBody*/,
						       std::ostream& osResponseBody)
{
  return (processBodyEnding(con, rh, rr, osResponseBody));
}


zia::filter::Status	filterGenericType::processBodyEnding(const zia::network::IConnection& /*con*/,
							     zia::http::IRequestHeader& rh,
							     zia::http::IResponseHeader& rr,
							     std::ostream& osResponseBody)
{
  struct zia::filter::Status	status;
  status.error = zia::filter::Status::SUCCESS;
  status.authorization = zia::filter::Status::ACCEPT;
  status.persistence = zia::filter::Status::REMOVEME;
  status.translation = zia::filter::Status::DECLINE;

  if (this->_configuration != 0)
    {
      const zia::IDictionnary&	dictionnary = this->_configuration->getHive("Main");
      std::string realpath  = Utils::getRealPath(dictionnary.get("RootDirectory"), rh.getPath());

      //std::cerr << "Path:"<< realpath << std::endl;
      if (!Utils::isDirectory(realpath))
	{
	  //std::cerr << "C'est un fichier je TakeOver" << std::endl;
	  if (Utils::existPath(realpath))
	    {
	      status.translation = zia::filter::Status::TAKEOVER;
	      this->fillMimeType(rr, realpath);
	      //std::cerr << "Le fichier existe" << std::endl;
	      this->completeResponse(rh, rr, osResponseBody, realpath);
	    }
	  else
	    {
	      //std::cerr << "Le fichier n'existe pas" << std::endl;
	    }
	}
    }
  return (status);
}

void	filterGenericType::completeResponse(zia::http::IRequestHeader& rh, zia::http::IResponseHeader& rr, std::ostream& osResponseBody, const std::string& realpath)
{
  rr.setCode(200);
  rr.setVMinor(1);
  rr.setVMajor(1);
  rr.setMsg("OK");
  //si c'est un get (POST?) on remplit le body
  if (rh.getMethod() == "GET")
    {
      zia::IDictionnary&		headerResponse = rr.entities();
      long int size = SizeFile(realpath);
      //std::cerr << "Size du fichier: " << size << std::endl;
      osResponseBody.flush();
      osResponseBody.clear();
      boost::filesystem::ifstream	ifs(realpath);
      osResponseBody << ifs.rdbuf();
      headerResponse.set("Content-Length", typeToString(size));
      ifs.close();
    }
  rr.readyToSend();
}

void	filterGenericType::fillMimeType(zia::http::IResponseHeader& rr, const std::string& realpath)
{
  zia::IDictionnary& headerResponse = rr.entities();

  if (0 == this->_configuration)
    {
      headerResponse.set("Content-Type", "text/plain");
      return;
    }

  //default type => text / plain
  std::string ext = boost::filesystem::extension(realpath);
  if (ext[0] == '.')
    ext = ext.substr(1, ext.size() -1);

  const zia::IDictionnary&  dictionnary = this->_configuration->getHive(GENERIC_TYPE_SECTION);
  const std::string mimetype = dictionnary.get(ext);

  if (mimetype != "")
    {
      //std::cerr << "DEBUG FILL MIME TYPE, mimeType == " << mimetype << std::endl;
      headerResponse.set("Content-Type", mimetype);
    }
  else
    {
      //std::cerr << "DEBUG FILL MIME TYPE, mimeType == text/plain" << std::endl;
      headerResponse.set("Content-Type", "text/plain");
    }
}

