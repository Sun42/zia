/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef IOUTPUTENCODER_H
#define IOUTPUTENCODER_H

#include "IFilter.h"
#include "network/IConnection.h"

namespace zia {
  namespace filter {

	/**
	 * \brief IOutputEncoder is an interface to handle the output encoding hook.
	 */
	class IOutputEncoder: virtual public IFilter
	{
	  public:

		/**
		 * \brief Main processing method.
		 *
		 * \return the status of the process to the server.
		 */
		virtual Status outputEncode(
			const network::IConnection& con,
			std::istream& isPlain,
			std::ostream& osEncoded) = 0;

		/**
		 * \brief Alternative processing method, called when 
		 * the input stream is empty but the output stream still 
		 * requires processing.
		 *
		 * \return the status of the process to the server.
		 */
		virtual Status outputEncodeEnding(
			const network::IConnection& con,
			std::ostream& osEncoded) = 0;
	};

  } // zia
} // filter

#endif /* IOUTPUTENCODER_H */
