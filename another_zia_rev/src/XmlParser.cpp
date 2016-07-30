/// \file

#include <QString>

#include <iostream>

#include "XmlParser.h"

XmlParser::XmlParser(void)
  : _file(0)
{
}

XmlParser::~XmlParser(void)
{
}

bool	XmlParser::read(const std::string& filename, Configuration& conf)
{
  this->_file = new QFile(QString(filename.c_str()));
  if (!this->_file->open(QFile::ReadOnly | QFile::Text))
    {
      delete this->_file;
      this->_file = 0;
      return (false);
    }

  setDevice(this->_file);

  while (!atEnd())
    {
      readNext();

      if (isStartElement())
	{
	  if (name() == "hives")
	    {
	      readHives(conf);
	    }
	  else
	    {
	      std::cerr << "This file is not a zia configuration file." << std::endl;
	      break;
	    }
	}
    }
  this->_file->close();
  delete this->_file;
  this->_file = 0;
  return (!error());
}

void	XmlParser::readHives(Configuration& conf)
{
  while (!atEnd())
    {
      readNext();

      if (isEndElement())
	break;

      if (isStartElement())
	{
	  if ("hive" == name())
	    {
	      readHive(conf, attributes().value("name").toString().toStdString());
	    }
	  else
	    {
	      readUnknownElement();
	    }
	}
    }
}

void	XmlParser::readHive(Configuration& conf, const std::string& hiveName)
{
  while (!atEnd())
    {
      readNext();

      if (isEndElement())
	break;

      if (isStartElement())
	{
	  if ("entry" == name())
	    {
	      const QString	key = attributes().value("key").toString();
	      conf.addData(hiveName, key.toStdString(), readElementText().toStdString());
	    }
	  else
	    {
	      std::cerr << "Not an entry token.. " << name().toString().toStdString() << std::endl;
	    }
	}
    }
}

void	XmlParser::readUnknownElement(void)
{
  std::cerr << "readUnknownElement" << std::endl;
  while (!atEnd())
    {
      readNext();

      if (isEndElement())
	break;

      if (isStartElement())
	readUnknownElement();
    }
}
