/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef IENDPOINT_H
#define IENDPOINT_H

#include <string>
#include "IAddress.h"

namespace zia {
	namespace network {

		/**
		 * \brief IEndPoint is an interface for the network endpoints.
		 *
		 * Notice:
		 *	host name is not necessarily already resolved.
		 *	Use with caution.
		 */
		class IEndPoint
		{
			public:

				/**
				 * \brief Virtual destructor.
				 */
				virtual ~IEndPoint() {}

				/**
				 * \brief Get the hostname of the endpoint.
				 *
				 * \return the hostname of the endpoint.
				 */
				virtual const std::string& getHostName() const = 0;

				/**
				 * \brief Get the port of the hostname.
				 *
				 * \return the port of the endpoint.
				 */
				virtual unsigned short getPort() const = 0;

				/**
				 * \brief Get the address of the endpoint.
				 *
				 * \return the address of the endpoint.
				 */
				virtual const IAddress& getAddress() const = 0;

				/**
				 * \brief Set the hostname of the endpoint.
				 */
				virtual void setHostName(const std::string&) = 0;
		};

	} // network
} // zia

#endif /* IENDPOINT_H */
