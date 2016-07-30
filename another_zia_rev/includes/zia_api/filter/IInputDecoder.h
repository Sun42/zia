/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef IINPUTDECODER_H
#define IINPUTDECODER_H

#include "IFilter.h"
#include "network/IConnection.h"

namespace zia {
	namespace filter {

		/**
		 * \brief IInputDecoder is an interface to handle the input decoding hook.
		 */
		class IInputDecoder: public IFilter
		{
			public:

				/**
				 * \brief Main processing method.
				 *
				 * \return the status of the process to the server.
				 */
				virtual Status inputDecode(
						const network::IConnection& con,
						std::istream& isEncoded, // encoded request input stream
						std::ostream& osDecoded, // decoded request output stream
						std::ostream& osOutput   // raw response output stream
						) = 0;

				/**
				 * \brief Alternative processing method, called when 
				 * the input stream is empty but the output stream still 
				 * requires processing.
				 *
				 * \return the status of the process to the server.
				 */
				virtual Status inputDecodeEnding(
						const network::IConnection& con,
						std::ostream& osDecoded, // decoded request output stream
						std::ostream& osOutput   // raw response output stream
						) = 0;
		};

	} // zia
} // filter

#endif /* IINPUTDECODER_H */
