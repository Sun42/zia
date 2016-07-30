/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef IDICTIONNARY_H
#define IDICTIONNARY_H

#include <string>
#include <map>

namespace zia {

	/**
	 * \brief IDictionnary is a collection interface for accessing key/value pairs,
	 * like HTTP header entities, configuration hives...
	 */
	class IDictionnary
	{
		public:

			/**
			 * \brief Virtual destructor for the interface.
			 */
			virtual                    ~IDictionnary() {}

			/**
			 * \brief Set a pair for the associated key and value.
			 */
			virtual void               set(const std::string& key, const std::string& value) = 0;

			/**
			 * \brief Get the value of the pair for the given key.
			 *
			 * \return a string with the mentionned value.
			 */
			virtual std::string        get(const std::string& key) const = 0;

			/**
			 * \brief Unset the pair for the given key.
			 */
			virtual void               unset(const std::string& key) = 0;

			/**
			 * \brief Checks whether the key exists or not.
			 *
			 * \return true if the key exists, false if not.
			 */
			virtual bool               exists(const std::string& key) const = 0;

			/**
			 * \brief Get the size.
			 *
			 * \return the size of the dictionnary.
			 */
			virtual size_t             getSize() const = 0;

			/**
			 * \brief Checks whether the dictionnary is empty or not.
			 *
			 * \return true if the dictionnary is empty, false is not.
			 */
			virtual bool               isEmpty() const = 0;

			/**
			 * \brief Dumps the dictionnary.
			 *
			 * \return a map representing each key/value pair.
			 */
			virtual std::map< std::string, std::string > getContent() const = 0;
	};

} // zia

#endif /* IDICTIONNARY_H */
