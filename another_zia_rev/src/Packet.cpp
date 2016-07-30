/// \file

#include "Packet.h"

/*********************************************************************/

Packet::Packet() :
  _isHead(false)
{
}

Packet::~Packet()
{
}

Packet::Packet(Packet const & obj) :
  _buf(obj._buf), _ptDef(obj._ptDef), _isHead(obj._isHead)
{
}

/*********************************************************************/

Packet &	Packet::operator=(Packet const & obj)
{
  if (this != &obj)
    {
      this->_buf = obj._buf;
      this->_ptDef = obj._ptDef;
      this->_isHead = obj._isHead;
    }
  return (*this);
}

bool	Packet::operator==(Packet const & obj) const
{
  return (obj._buf == this->_buf);
}

Packet &	Packet::operator+=(Packet & obj)
{
  std::vector<unsigned char>::iterator	it = obj._buf.begin();
  std::vector<unsigned char>::iterator	itEnd = obj._buf.end();
  for (; it != itEnd; ++it)
    {
      this->_buf.push_back(*it);
    }
  return *this;
}

Packet&	Packet::operator<<(unsigned int val)
{
  for(unsigned int dec = 0, filtr = 0x000000FF;
      dec <= 24;
      dec += 8,	filtr <<= 8)
    {
      this->_buf.push_back((val & filtr) >> dec);
    }
  return (*this);
}

Packet&	Packet::operator<<(unsigned char val)
{
  this->_buf.push_back(val);
  return (*this);
}

Packet&	Packet::operator<<(std::string const & val)
{
  unsigned int	i = 0;
  while (i < val.size())
    {
      this->_buf.push_back(val.at(i));
      ++i;
    }
  this->_buf.push_back('\0');
  return (*this);
}

void	Packet::operator>>(unsigned char & val)
{
  val = *this->_ptDef;
  ++this->_ptDef;
}

void	Packet::operator>>(unsigned int & val)
{
  val = 0;
  for (int dec = 0; dec <= 24; dec += 8)
    {
      val += (*this->_ptDef) << dec;
      ++this->_ptDef;
    }
}

void	Packet::operator>>(std::string & val)
{
  while(*this->_ptDef != '\0')
    {
      val.push_back(*this->_ptDef);
      ++this->_ptDef;
    }
  ++this->_ptDef;
}

/*********************************************************************/

char	Packet::getCmd() const
{
  if (this->_buf.size() < DET_SIZE || !this->checkLen() || !this->checkParity())
    return 0;
  return (this->_buf.at(INDEX_CMD));
}

std::vector<unsigned char>*	Packet::getData() const
{
  return (new std::vector<unsigned char>(this->_buf));
}

bool	Packet::getParity() const
{
  bool tmpParity = 0;
  for(unsigned int i = 0; i < this->_buf.size(); ++i)
    {
      for (unsigned int j = 0; j < 8; ++j)
	tmpParity ^= ((this->_buf.at(i) & (0x80 >> j)) >> (7 - j));
    }
  return tmpParity;
}

int	Packet::getRealSize() const
{
  return (this->_buf.size());
}

int	Packet::getSize() const
{
  return (this->_buf.size() - DET_SIZE);
}

/*********************************************************************/

bool	Packet::checkLen() const
{
  if (this->_buf.size() < DET_SIZE)
    return false;

  unsigned int	tmpLen = 0;
  tmpLen += (this->_buf.at(3) & 0x7F) << 24;
  tmpLen += this->_buf.at(2) << 16;
  tmpLen += this->_buf.at(1) << 8;
  tmpLen += this->_buf.at(0) << 0;

  return (this->_buf.size() == tmpLen);
}

bool	Packet::checkParity() const
{
  if (!this->checkLen())
    return false;

  bool saveParity = (this->_buf.at(3) & 0x80) >> 7;

  return ((saveParity ^ getParity()) == saveParity);
}

bool	Packet::isEnd()
{
  return (this->_ptDef == this->_buf.end());
}

/*********************************************************************/

void	Packet::add(boost::array<unsigned char, 4096> & buf, unsigned int len)
{
  this->_buf.insert(this->_buf.end(), buf.begin(), buf.begin() + len);
  if(this->_buf.size() > DET_SIZE)
    this->_ptDef = this->_buf.begin() + DET_SIZE + 1;
  this->_isHead = true;
}

void	Packet::addHead()
{
  if (!this->_isHead)
    {
      unsigned char	tmpDet[DET_SIZE];
      unsigned int * tmpSize = (unsigned int *)tmpDet;

      *tmpSize = this->_buf.size() + DET_SIZE;
      this->_buf.insert(this->_buf.begin(), tmpDet, tmpDet + 4);
      this->_buf.at(3) |= getParity() << 7;
      this->_isHead = true;
    }
}

void	Packet::reset()
{
  this->_isHead = false;
  this->_buf.clear();
}

/*********************************************************************/

std::ostream&	operator<<(std::ostream& os, Packet const & packet)
{
  return (os << "Taille : " << packet.getSize() <<
	  "\nCommand : " << packet.getCmd() <<
	  "Checklen :" << std::boolalpha << packet.checkLen() << std::endl);
}
