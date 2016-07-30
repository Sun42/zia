/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 *
 * IBodyEncoder filter interface.
 */

#ifndef IBODYENCODER_H
#define IBODYENCODER_H

#include "IFilter.h"
#include "network/IConnection.h"
#include "http/IRequestHeader.h"
#include "http/IResponseHeader.h"

namespace zia {
  namespace filter {

	/**
	 * \brief IBodyEncoder is an interface to handle the body encoding hook.
	 */
	class IBodyEncoder: virtual public IFilter
	{
	  public:
		/**
		 * \brief Main processing method.
		 *
		 * \return the status of the process to the server.
		 */
		virtual Status bodyEncode(
			const network::IConnection& con,
			const http::IRequestHeader& rh,
			const http::IResponseHeader& rr,
			std::istream& isPlainBody,
			std::ostream& osEncodedBody) = 0;

		/**
		 * \brief Alternative processing method, called when the input stream is empty but the output stream still requires processing.
		 *
		 * \return the status of the process to the server.
		 */
		virtual Status bodyEncodeEnding(
			const network::IConnection& con,
			const http::IRequestHeader& rh,
			const http::IResponseHeader& rr,
			std::ostream& osEncodedBody) = 0;
	};

  } // zia
} // filter

#endif /* IBODYENCODER_H */
