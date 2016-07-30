/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 *
 * HTTP Response Header interface.
 */

#ifndef IRESPONSEHEADER_H
#define IRESPONSEHEADER_H

#include <string>
#include "IDictionnary.h"

namespace zia {
	namespace http {

		/**
		 * \brief IResponseHeader is an interface representing an HTTP response header
		 */
		class IResponseHeader
		{
			public:

				/**
				 * \brief Virtual destructor.
				 */
				virtual ~IResponseHeader() {}

				/**
				 * \brief Get the major version number of HTTP protocol.
				 *
				 * \return the major version number of http protocol.
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
				 * \brief Sets the status code of the response.
				 */
				virtual void                setCode(unsigned int code) = 0;

				/**
				 * \brief Get the status code of the response.
				 *
				 * \return the status code of the response.
				 */
				virtual unsigned int        getCode() const = 0;

				/**
				 * \brief Sets the reason-phrase corresponding to the status code of the response.
				 */
				virtual void                setMsg(const std::string& msg) = 0;

				/**
				 * \brief Get the reason-phrase corresponding to the status code of the response.
				 *
				 * \return the reason-phrase corresponding to the status code of the response.
				 */
				virtual const std::string&  getMsg() const = 0;

				/**
				 * \brief When the workflow needs to send the HTTP response header
				 * the process calls this method.
				 */
				virtual void                readyToSend() = 0;

				/**
				 * \brief Checks whether the response has been sent.
				 *
				 * \return true if the response has been sent, false if not.
				 */
				virtual bool                sent() const = 0;

				/**
				 * \brief Get the response header fields as an IDictionnary.
				 *
				 * \return the response header fields.
				 */
				virtual const IDictionnary& entities() const = 0;

				/**
				 * \brief Get the response header fields as an IDictionnary.
				 *
				 * \return the response header fields.
				 */
				virtual IDictionnary&       entities() = 0;
		};

	} // http
} // zia

#endif /* IRESPONSEHEADER_H */
