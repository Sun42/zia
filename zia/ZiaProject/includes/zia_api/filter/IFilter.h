/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 */

#ifndef IFILTER_H
#define IFILTER_H

#include <cstddef>

namespace zia {

  /**
   * \brief Filter namespace in the Zia API.
   */  
  namespace filter {

	/**
	 * \brief Status structure is a bitfield
	 * that defines the return of filter methods.
	 */
	struct Status
	{
	  /**
	   * \brief Enumeration of the execution status of filter method.
	   */
	  enum
	  {
		SUCCESS,
		FATAL_ERROR
	  } error:1;

	  /**
	   * \brief Enumeration of the authorization status.
	   * If no auth is required, ACCEPT is returned.
	   */
	  enum
	  {
		DENY,
		ACCEPT
	  } authorization:1;

	  /**
	   * \brief Enumeration of the filter actions.
	   * If TAKEOVER is returned, no more filter will be executed on the current hook.
	   */
	  enum
	  {
		TAKEOVER,
		DECLINE
	  } translation:1;

	  /**
	   * \brief Filter life handling.
	   * If ALIVE is returned, the filter stays on the hook.
	   * If REMOVEME is returned, the filter is no more needed on the
	   * processing of the current request.
	   */
	  enum
	  {
		ALIVE,
		REMOVEME
	  } persistence:1;
	};

	/**
	 * \brief IFilter is a base interface for all filters.
	 * It also provides minimum requirement for integration in memory pool.
	 */
	class IFilter
	{
	  public:

		/**
		 * \brief Virtual destructor.
		 */
		virtual ~IFilter() {}

		/**
		 * \brief Required for memory pool integration.
		 * 
		 * \return the size of the filter object
		 */
		virtual std::size_t getObjectSize() const = 0;
  
		/** 
		 * \brief Constructs the object via a placement new().
		 */
		virtual void        constructObject(void* storage) const = 0;

		/**
		 * \brief Defines the filter priority in the filter stack.
		 *
		 * \return the filter priority in the filter stack.
		 */
		virtual int         getPriority() const = 0;
	};

  } // zia
} // filter

#endif /* IFILTER_H */
