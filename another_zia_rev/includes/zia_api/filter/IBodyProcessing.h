/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 *
 * IBodyProcessing filter interface.
 */

#ifndef IBODYPROCESSING_H
#define IBODYPROCESSING_H

#include "IFilter.h"
#include "network/IConnection.h"
#include "http/IRequestHeader.h"
#include "http/IResponseHeader.h"

namespace zia {
	namespace filter {

		/**
		 * \brief IBodyProcessing is an interface to handle the body processing hook.
		 */
		class IBodyProcessing: public IFilter
		{
			public:
				/**
				 * \brief Main processing method.
				 *
				 * \return the status of the process to the server.
				 */
				virtual Status processBody(
						const network::IConnection& con,
						http::IRequestHeader& rh,
						http::IResponseHeader& rr,
						std::istream& isRequestBody,
						std::ostream& osResponseBody
						) = 0;

				/**
				 * \brief Alternative processing method, called when the input stream
				 * is empty but the output stream still requires processing.
				 *
				 * \return the status of the process to the server.
				 */
				virtual Status processBodyEnding(
						const network::IConnection& con,
						http::IRequestHeader& rh,
						http::IResponseHeader& rr,
						std::ostream& osResponseBody
						) = 0;
		};

	} // zia
} // filter

#endif /* IBODYPROCESSING_H */
