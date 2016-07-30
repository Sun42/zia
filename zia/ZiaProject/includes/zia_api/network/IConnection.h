/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <string>
#include "IEndPoint.h"

namespace zia {
  namespace network {

	/**
	 * \brief IConnection is an interface for handling connections.
	 */
	class IConnection
	{
	  public:

		/**
		 * \brief Virtual destructor.
		 */
		virtual ~IConnection() {}

		/**
		 * \brief Get the client endpoint
		 *
		 * \return the endpoint representing the client.
		 */
		virtual const IEndPoint& getClient() const = 0;

		/**
		 * \brief Get the server endpoint.
		 *
		 * \return the endpoint representing the server.
		 */
		virtual const IEndPoint& getServer() const = 0;
	};

  } // network
} // zia

#endif /* ICONNECTION_H */
