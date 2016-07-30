/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

#include <string>
#include "IDictionnary.h"

namespace zia {

	/**
	 * \brief IConfiguration is an interface allowing the configuration of the plugins.
	 */
	class IConfiguration
	{
		public:

			/**
			 * \brief Virtual destructor for the interface.
			 */
			virtual ~IConfiguration() {}

			/**
			 * \brief Get the hive.
			 *
			 * \return an implementation of IDictionnary representing the plugin configuration.
			 */
			virtual const IDictionnary& getHive(const std::string&) = 0;

			/**
			 * \brief Checks whether the hive exists or not.
			 *
			 * \return true if the hive exists, false if not.
			 */
			virtual bool                hiveExists(const std::string&) const = 0;
	};

} // zia

#endif /* ICONFIGURATION_H */
