/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 *
 * HTTP Request Header interface.
 */

#ifndef IREQUESTHEADER_H
#define IREQUESTHEADER_H

#include <string>
#include "IDictionnary.h"

namespace zia {

	/**
	 * \brief HTTP namespace in the Zia API
	 */
	namespace http {

		/**
		 * \brief IRequestHeader is an interface representing an HTTP request header.
		 */
		class IRequestHeader
		{
			public:

				/**
				 * \brief Virtual destructor.
				 */
				virtual ~IRequestHeader() {}

				/**
				 * \brief Get the method name of the request.
				 *
				 * \return the method name of the request.
				 */
				virtual const std::string&  getMethod() const = 0;

				/**
				 * \brief Set the method name of the request.
				 */
				virtual void                setMethod(const std::string&) = 0;

				/**
				 * \brief Get the path of the request.
				 *
				 * \return the path of the request.
				 */
				virtual const std::string&  getPath() const = 0;

				/**
				 * \brief Set the path of the request.
				 */
				virtual void                setPath(const std::string&) = 0;

				/**
				 * \brief Get the major version number of the HTTP protocol.
				 *
				 * \return the major version number of HTTP protocol.
				 */
				virtual unsigned int        getVMajor() const = 0;

				/**
				 * \brief Set the major version number of HTTP protocol.
				 */
				virtual void                setVMajor(unsigned) = 0;

				/**
				 * \brief Get the minor version number of HTTP protocol.
				 *
				 * \return the minor version number of HTTP protocol.
				 */
				virtual unsigned int        getVMinor() const = 0;

				/**
				 * \brief Set the minor version number of HTTP protocol.
				 */
				virtual void                setVMinor( unsigned) = 0;

				/**
				 * \brief Get the request header fields as an IDictionnary.
				 *
				 * \return the request header fields.
				 */
				virtual const IDictionnary& entities() const = 0;

				/**
				 * \brief Get the request header fields as an IDictionnary.
				 *
				 * \return the request header fields.
				 */
				virtual IDictionnary&       entities() = 0;
		};

	} // http
} // zia

#endif /* IREQUESTHEADER_H */
