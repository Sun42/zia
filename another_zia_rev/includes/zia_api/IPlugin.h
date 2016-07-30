/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <string>
#include <vector>
#include "filter/IFilter.h"
#include "ILogger.h"
#include "IConfiguration.h"

/**
 * \brief Global namespace for the Zia API
 */
namespace zia {

	/**
	 * \brief IPlugin is an interface for all plugin for the Zia server. 
	 */
	class IPlugin
	{
		public:

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~IPlugin() {}

			/**
			 * \brief Get plugin version.
			 *
			 * \return plugin version.
			 */
			virtual unsigned int getVersion() const = 0;

			/**
			 * \brief Get plugin name.
			 *
			 * \return plugin name.
			 */
			virtual const std::string& getName() const = 0;

			/**
			 * \brief Get a vector of filters representing the hooks where the plugin attaches itself.
			 *
			 * \return a vector.
			 */
			virtual const std::vector<const filter::IFilter*>& getFilters() const = 0;

			/**
			 * \brief Allows the plugin to access a logging interface presented by the server.
			 */
			virtual void setLogger(ILogger* logger) = 0;

			/**
			 * \brief Allows the plugin to access a configuration interface presented by the server.
			 *
			 * This allows the server to present different configuration interface, depending on the 
			 * plugin.
			 */
			virtual void setConfigurator(IConfiguration* configurator) = 0;
	};

	/**
	 * \brief All modules (.so, .dll) must have extern "C" { Plugin& getInstance(); }
	 * typedef getPlugin_t represents this function prototype.
	 */
	typedef IPlugin& (*getPlugin_t)();

} // zia

#endif /* IPLUGIN_H */
