/// \file

#ifndef PACKET_H_
#define PACKET_H_

#include <vector>

#include <boost/array.hpp>
#include <boost/asio.hpp>

/*! \class Packet
 * \brief Classe encapsulant des donnees.
 *
 * Cette classe sert a la communication (a l'aide de Boost Asio)
 * entre le serveur et le client loader.
 */
class	Packet
{
 public:
  Packet();
  Packet(Packet const &);
  ~Packet();

  Packet&				operator=(Packet const &);
  bool					operator==(Packet const & obj) const;
  Packet&				operator+=(Packet & val);
  Packet&				operator<<(unsigned int val);
  Packet&				operator<<(unsigned char val);
  Packet&				operator<<(std::string const & val);
  void					operator>>(unsigned char & val);
  void					operator>>(unsigned int & val);
  void					operator>>(std::string & val);

  char					getCmd() const; /*!< recupere la commande ds le buffer */
  std::vector<unsigned char>*		getData() const ; /*!< recupere la partie DATA du packet */
  int					getRealSize() const; /*!< retourne la size totale du packet */
  int					getSize() const; /*!< retourne la taille de la partie DATA */

  bool					isEnd();
  bool					checkLen() const;
  bool					checkParity() const;

  void					add(boost::array<unsigned char, 4096> & buf, unsigned int len); /*!< ajoute les donnees a la fin du packet */
  void					addHead();  /*!< ajoute la SIZE au packet */
  void					reset();

 private:
  bool					getParity() const;
  void					copyBuff(unsigned char * buf, unsigned int len);

 private:
  static const unsigned int		DET_SIZE = 4;  /*!< Size de la partie SIZE */
  static const unsigned int		INDEX_CMD = 4;  /*!< index de la commande de l action ds le packet */
  std::vector<unsigned char>		_buf;
  std::vector<unsigned char>::iterator	_ptDef;
  bool					_isHead;
};

std::ostream&	operator<<(std::ostream&, Packet const &);

#endif /* ! PACKET_H_ */
