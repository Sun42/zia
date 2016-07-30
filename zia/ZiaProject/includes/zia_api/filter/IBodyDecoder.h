/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 *
 * IBodyDecoder filter interface.
 */

#ifndef IBODYDECODER_H
#define IBODYDECODER_H

#include "IFilter.h"
#include "network/IConnection.h"
#include "http/IRequestHeader.h"
#include "http/IResponseHeader.h"

namespace zia {
  namespace filter {

	/**
	 * \brief IBodyDecoder is an interface to handle the body decoding hook.
	 */
	class IBodyDecoder: virtual public IFilter
	{
	  public:

		/**
		 * \brief Main processing method.
		 *
		 * \return the status of the process to the server.
		 */
		virtual Status bodyDecode(
			const network::IConnection& con,
			const http::IRequestHeader& rh,
			http::IResponseHeader& rr,
			std::istream& isEncodedBody,   // encoded request body input stream 
			std::ostream& osDecodedBody,   // decoded request body output stream
			std::ostream& osResponseBody   // raw response body output stream
			) = 0;

		/**
		 * \brief Alternative processing method, called when 
		 * the input stream is empty but the output stream still 
		 * requires processing.
		 *
		 * \return the status of the process to the server.
		 */
		virtual Status bodyDecodeEnding(
			const network::IConnection& con,
			const http::IRequestHeader& rh,
			http::IResponseHeader& rr,
			std::ostream& osDecodedBody,
			std::ostream& osResponseBody) = 0;
	};

  } // zia
} // filter

#endif /* IBODYDECODER_H */
