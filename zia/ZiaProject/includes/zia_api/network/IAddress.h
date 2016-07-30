/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef IADDRESS_H
#define IADDRESS_H

/** \file IAddress.h
 * stdint.h is a C99 standard. We know it is not shipped with Microsoft
 * Visual Studio or some older C++ compilers, but we will let you make the
 * code compile with Microsoft Visual Studio. It is not up to us to patch
 * Microsoft Visual Studio, hell no !!! ;)
 *
 * http://en.wikipedia.org/wiki/Stdint.h#Downloads for more information.
 */
#include <stdint.h>

namespace zia {

  /**
   * \brief Network namespace in the Zia API.
   */  
  namespace network {

	/**
	 * \brief IPv4Address is a structure representing IPv4.
	 */
	struct IPv4Address
	{
	  union
	  {
		struct
		{
		  unsigned char a;
		  unsigned char b;
		  unsigned char c;
		  unsigned char d;
		};
		unsigned char bytes[4];
		uint32_t      host;
	  };
	};

	/**
	 * \brief IPv6Address is a structure representing IPv6.
	 */
	struct IPv6Address
	{
	  union
	  {
		struct
		{
		  union
		  {
			unsigned char networkBytes[8];
			uint64_t      network;
		  };
		  union
		  {
			unsigned char hostBytes[8];
			uint64_t      host;
		  };
		};
		unsigned char bytes[16];
	  };
	};

	/**
	 * \brief IAddress is a class representing any kind of IP address.
	 */
	class IAddress
	{
	  public:

		/**
		 * \brief Virtual destructor.
		 */
		virtual ~IAddress() {}

		/**
		 * \brief Checks whether an address is an IPv4 address. 
		 *
		 * \return true if the address is an IPv4 address, false if not.
		 */
		virtual bool isV4() const = 0;

		/**
		 * \brief Checks whether an address is an IPv6 address.
		 *
		 * \return true if the address is an IPv6 address, false if not.
		 */
		virtual bool isV6() const = 0;

		/**
		 * \brief Checks whether the address is an IPv4-compatible address.
		 *
		 * \return true if the address is an IPv4-compatible address, false if not.
		 */
		virtual bool isV4Compatible() const = 0;

		/**
		 * \brief Get the IPv4 address.
		 *
		 * \return the IPv4 address.
		 */
		virtual const IPv4Address& getV4() const = 0;

		/**
		 * \brief Get the IPv6 address.
		 *
		 * \return the IPv6 address.
		 */
		virtual const IPv6Address& getV6() const = 0;
	};

  } // network 
} // zia

#endif /* IADDRESS_H */
