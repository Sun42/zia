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
	  if (name() == "zconf" && attributes().value("version") == "1.0")
	    {
	      readConfig(conf);
	    }
	  else
	    {
	      std::cerr << "This file is not a zconf file." << std::endl;
	      break;
	    }
	}
    }
  this->_file->close();
  delete this->_file;
  return (!error());
}

void	XmlParser::readConfig(Configuration& conf)
{
  while (!atEnd())
    {
      readNext();

      if (isEndElement())
	break;

      if (isStartElement())
	{
	  if ("Plugin" == name())
	    readPlugin(conf);
	  else if ("Items" == name())
	    readItems(conf);
	  else
	    readUnknownElement();
	}
    }
}

void	XmlParser::readPlugin(Configuration& conf)
{
  while (!atEnd())
    {
      readNext();

      if (isEndElement())
	break;

      if (isStartElement())
	{
	  if ("Name" == name())
	    conf.addData("Plugin", "Name", readElementText().toStdString());
	  else if ("Version" == name())
	    conf.addData("Plugin", "Version", readElementText().toStdString());
	  else
	    readUnknownElement();
	}
    }
}

void	XmlParser::readItems(Configuration& conf)
{
  while (!atEnd())
    {
      readNext();

      if (isEndElement())
	break;

      if (isStartElement())
	{
	  conf.addData("Items", name().toString().toStdString(),
		       readElementText().toStdString());
	}
    }
}

void	XmlParser::readUnknownElement(void)
{
  std::cerr << "Unknown Element." << std::endl;
  while (!atEnd())
    {
      readNext();

      if (isEndElement())
	break;

      if (isStartElement())
	readUnknownElement();
    }
}
