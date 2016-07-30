/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef ILOGGER_H
#define ILOGGER_H

#include <ostream>
#include <sstream>

namespace zia {

	/**
	 * \brief Log namespace
	 */
	namespace log
	{
		/**
		 * \brief Enumeration for the log messages priorities
		 */
		enum Priority
		{
			ZIA_DEBUG,
			ZIA_INFO,
			ZIA_WARN,
			ZIA_ERROR
		};

	}

	/**
	 * \brief ILogger is a helper interface to simplify the commit of streamed message. 
	 */
	class ILogger
	{
		public:

			/**
			 * \brief Message is RAII helper object for user friendly logging.
			 */
			class Message
			{
				public:
					/**
					 * \brief Destructor. Logs the Message at destruction.
					 */
					~Message() { if (_active) _iLogger.log(_priority, _ss.str()); }

					/**
					 * \brief Operator overload for streaming purpose.
					 */
					template <typename T>
						std::ostream& operator<<(T& d) { _ss << d; return _ss; }

					/**
					 * \brief Constructor.
					 */
					Message(ILogger& il, log::Priority p):
						_iLogger(il),
						_priority(p),
						_active(true)	
				{}

					Message(const Message& from):
						_iLogger(from._iLogger),
						_priority(from._priority),
						_ss(from._ss.str()),
						_active(true)
				{ from._active = false; }

				private:

					Message& operator=(const Message& from);

					/**
					 * \brief 
					 */
					ILogger&          _iLogger;
					/**
					 * \brief
					 */
					log::Priority     _priority;
					/**
					 * \brief 
					 */
					std::stringstream _ss;
					mutable bool      _active;
			};

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~ILogger() {}

			/**
			 * \brief Logs the string with the given priority. MUST BE THREAD-SAFE.
			 */
			virtual void    log(log::Priority p, const std::string& msg) = 0;
			/**
			 * \brief Logs a stream with the given priority.
			 *
			 * \return a Message for streaming purpose.
			 */
			virtual Message log(log::Priority p) = 0;
	};

} // zia
#endif /* ILOGGER_H */
