/// \file

#ifndef DATE_RULES_H_
#define DATE_RULES_H_

#define WIN32_LEAN_AND_MEAN
#define BOOST_SPIRIT_THREADSAFE // Always before including spirit headers
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_dynamic.hpp>

#include "BasicRules.h"

using namespace BOOST_SPIRIT_CLASSIC_NS;

static BasicRules basicRules;

/*! \struct DateRules
 * \brief Regles de BNF/Boost Spirit concernant le format des dates.
 *
 * Structure contenant les regles concernant le format des dates dans la RFC 2616.
 */

struct	DateRules
{
  DateRules(void)
  {
    uint_parser<unsigned, 10, 1, 1> DIGIT;
    uint_parser<unsigned, 10, 2, 2> DIGIT2;
    uint_parser<unsigned, 10 , 4, 4> DIGIT4;
    month =	str_p("Jan") | str_p("Feb") | str_p("Mar") | str_p("Apr") |
      str_p("May") | str_p("Jun") | str_p("Jul") | str_p("Aug") |
      str_p("Sep") | str_p("Oct") | str_p("Nov") | str_p("Dec");

    //02 Jun 1987
    date1 =	limit_d(0u, 31u)[DIGIT2] >> basicRules.SP >> month >> basicRules.SP >> DIGIT4;

    //02-Jun-09
    date2 =	limit_d(0u, 31u)[DIGIT2] >> ch_p('-') >> month >> ch_p('-') >> DIGIT2;

    // month day
    date3 =	month >> basicRules.SP >> (limit_d(0u, 31u)[DIGIT2] | (basicRules.SP && DIGIT));

    //; 00:00:00 - 23:59:59
    time =	limit_d(0u, 23u)[DIGIT2] >> ch_p(':') >> limit_d(0u, 59u)[DIGIT2] >>
      ':' >> limit_d(0u, 59u)[DIGIT2];

    wkday =	str_p("Mon") | "Tue" | "Wed" | "Thu" | "Fri" | "Sat" | "Sun";

    weekday =	str_p("Monday") | "Tuesday" | "Wednesday" | "Thursday" |
      "Friday" | "Saturday" | "Sunday";

    asctime_date = wkday >> basicRules.SP >> date3 >> basicRules.SP >>
      time >> basicRules.SP >> DIGIT4;

    rfc850_date = weekday >> ch_p(',') >> basicRules.SP >> date2 >> basicRules.SP
			  >> time >> basicRules.SP >> str_p("GMT");

    rfc1123_date = wkday >> ch_p(',') >> basicRules.SP >> date1 >> basicRules.SP >>
      time >> basicRules.SP >> str_p("GMT");

    HTTP_date = rfc1123_date | rfc850_date | asctime_date;
  }

  stored_rule <> DIGIT, DIGIT2 , DIGIT4;
  stored_rule <> month, date1, date2, date3, time, wkday, weekday;
  stored_rule <> asctime_date, rfc850_date, rfc1123_date, HTTP_date;
};

#endif
