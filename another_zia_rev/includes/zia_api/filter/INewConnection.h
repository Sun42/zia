/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef INEWCONNECTION_H
#define INEWCONNECTION_H

#include "IFilter.h"
#include "network/IConnection.h"

namespace zia {
	namespace filter {

		/**
		 * \brief INewConnection is an interface to handle the new connection hook.
		 */
		class INewConnection: public IFilter
		{
			public:

				/**
				 * \brief Main processing method.
				 *
				 * \return the status fo the process to the server.
				 */
				virtual Status newConnection(network::IConnection& con) = 0;
		};

	} // zia
} // filter

#endif /* INEWCONNECTION_H */
