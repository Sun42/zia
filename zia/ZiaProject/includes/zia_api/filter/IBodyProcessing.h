/*
 * ZIA API - epitech_2011s
 * Copyright © EPITECH 2009
 *
 * IBodyProcessing filter interface.
*/

#ifndef IBODYPROCESSING_H
#define IBODYPROCESSING_H

#include "IFilter.h"
#include "network/IConnection.h"
#include "http/IRequestHeader.h"
#include "http/IResponseHeader.h"

namespace zia {
namespace filter {

  /**
   * Interface to handle the body process hook
   */
class IBodyProcessing: virtual public IFilter
{
public:
  /**
   * Called when request body data are available.
   */
   virtual Status processBody(
			      const network::IConnection& con,
			      http::IRequestHeader& rh,
			      http::IResponseHeader& rr,
			      std::istream& isRequestBody,
			      std::ostream& osResponseBody
			      ) = 0;
		
  /**
   * Called when request body is finished
   */
   virtual Status processBodyEnding(
				    const network::IConnection& con,
				    http::IRequestHeader& rh,
				    http::IResponseHeader& rr,
				    std::ostream& osResponseBody
				    ) = 0;
   };

} // zia
} // filter

#endif /* IBODYPROCESSING_H */
