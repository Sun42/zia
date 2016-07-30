/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 *
 * IClosedConnection filter interface.
 */

#ifndef ICLOSEDCONNECTION_H
#define ICLOSEDCONNECTION_H

#include "IFilter.h"
#include "network/IConnection.h"

namespace zia {
  namespace filter {

	/**
	 * \brief IClosedConnection is an interface to handle the closed connection hook.
	 */
	class IClosedConnection: virtual public IFilter
	{
	  public:

		/**
		 * \brief Main processing method.
		 *
		 * \return the status of the process to the server.
		 */
		virtual Status closedConnection(const network::IConnection& con) = 0;
	};

  } // zia
} // filter

#endif /* ICLOSEDCONNECTION_H */
