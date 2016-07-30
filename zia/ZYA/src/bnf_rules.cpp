#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_push_back_actor.hpp>
#include <boost/spirit/include/classic_loops.hpp>
#include <iostream>
#include "ZiaException.h"
using namespace BOOST_SPIRIT_CLASSIC_NS;


int main()
{
  /*
    BNF BASIC RULES
   */
  rule<> OCTET          = anychar_p;/*(any 8-bit sequence of data)*/
  rule<> CHAR           = range_p(0, 127); /*(any US-ASCII character (octets 0 - 127))*/
  rule<> UPALPHA        = upper_p;/*(any US-ASCII uppercase letter "A".."Z")*/
  rule<> LOALPHA        = lower_p;/*(any US-ASCII lowercase letter "a".."z")*/
  rule<> ALPHA          = (UPALPHA | LOALPHA);
  rule<> DIGIT          = digit_p;/*(any US-ASCII digit "0".."9")*/
  rule<> CTL            = cntrl_p;/*(any US-ASCII control character (octets 0 - 31) and DEL (127))*/
  rule<> CTLS		= +(cntrl_p);
  rule<> CTL_N		= ~range_p(0, 31) & ~ch_p(127); /*non control char*/
  rule<> CTLS_N		= +(CTL_N);/*non control chars*/
  rule<> HT             = ch_p('\t');/*(US-ASCII HT, horizontal-tab (9))*/
  rule<> HT_N           = ~ch_p('\t');/* non HT*/
  rule<> SP		=  ch_p(' ');/* <US-ASCII SP, space (32)>*/
  rule<> SP_N		= ~ch_p(' ');
  rule<> CR		= ch_p('\r');
  rule<> LF		= ch_p('\n');
  rule<> CRLF           = CR >> LF;
  rule<> LWS            = !(CRLF) && +( SP | HT );

  rule<> TEXT           = (CTLS_N | LWS) | (OCTET & CTLS_N);/*<any OCTET except CTLs, but including LWS>*/  
  rule<> HEX            = xdigit_p;
  rule<> separators     = (ch_p('(') | ch_p(')') | ch_p('<') | ch_p('>') |
			   ch_p('@') | ch_p(',') | ch_p(';') | ch_p(':') |
			   ch_p('\\') | ch_p('\"') | ch_p('/') | ch_p('[') |
			   ch_p(']') | ch_p('?') | ch_p('=') | ch_p('{') |
			   ch_p('}') | SP | HT);
  rule<>separators_n	= (~ch_p('(') & ~ch_p(')') & ~ch_p('<') & ~ch_p('>') &
			   ~ch_p('@') & ~ch_p(',') & ~ch_p(';') & ~ch_p(':') &
			   ~ch_p('\\') & ~ch_p('\"') & ~ch_p('/') & ~ch_p('[') &
			   ~ch_p(']') & ~ch_p('?') & ~ch_p('=') & ~ch_p('{') &
			   ~ch_p('}') & SP_N & HT_N);
  rule<> token          = +(CTLS_N  & separators_n & CHAR); /* 1*<any CHAR except CTLs or separators>*/
  rule<> ctext          = (~(ch_p('(')) & ~(ch_p(')')) & TEXT); /*<any TEXT excluding "(" and ")">;*/
  rule<> quoted_pair    = ch_p('\\') >> CHAR; /* ch_p(\" >> CHAR */
  rule<> qdtext         = (~(ch_p('\"')) & TEXT );/*<any TEXT except <">>*/
  rule<> quoted_string  =  (ch_p('\"') >>*(qdtext | quoted_pair)  >> ch_p('\"'));/*( <"> *(qdtext | quoted-pair ) <"> )*/
  rule<> comment        =  ch_p('(') >> *(ctext | quoted_pair | comment) >> ch_p(')'); /*"(" *( ctext | quoted-pair | comment ) ")"*/


  /*
    OTHERS
   */
  /*  rule <> DIGIT2 = repeat_p(2) [DIGIT];*/
  uint_parser<unsigned, 10 , 4, 4> DIGIT4;  /*repeat_p(4) [DIGIT];*/
  uint_parser<unsigned, 10, 2, 2> DIGIT2;
  /*
    BNF DATE RULES
   */
  
  rule <> month =	str_p("Jan") | str_p("Feb") | str_p("Mar") | str_p("Apr") |
			str_p("May") | str_p("Jun") | str_p("Jul") | str_p("Aug") |
			str_p("Sep") | str_p("Oct") | str_p("Nov") | str_p("Dec");
  
  
  rule <> date1 =	limit_d(0u, 31u)[DIGIT2] >> SP >> month >> SP >> DIGIT4; //02 Jun 1987 
  rule <> date2 =	limit_d(0u, 31u)[DIGIT2] >> ch_p('-') >> month >> ch_p('-') >> repeat_p(2)[DIGIT]; //02-Jun-09
  rule <> date3 =	month >> SP >> (limit_d(0u, 31u)[DIGIT2] | (SP && DIGIT));// month day
  rule <> time =	limit_d(0u, 23u)[DIGIT2] >> ch_p(':') >> limit_d(0u, 59u)[DIGIT2] >>
			':' >> limit_d(0u, 59u)[DIGIT2];//; 00:00:00 - 23:59:59
  
  rule <> wkday =	str_p("Mon") | "Tue" | "Wed" | "Thu" | "Fri" | "Sat" | "Sun";
  
  rule <> weekday =	str_p("Monday") | "Tuesday" | "Wednesday" | "Thursday" | 
			"Friday" | "Saturday" | "Sunday";
  
  rule <> asctime_date = wkday >> SP >> date3 >> SP >> time >> SP >> repeat_p(4)[DIGIT];
  rule <> rfc850_date = weekday >> ch_p(',') >> SP >> date2 >> SP >> time >> SP >> str_p("GMT");
  rule <> rfc1123_date = wkday >> ch_p(',') >> SP >> date1 >> SP >> time >> SP >> str_p("GMT");
  rule <> HTTP_date = rfc1123_date | rfc850_date | asctime_date;  
  /*tests unitaires*/
  try
    {
      std::cout<< "Parsing tests rules" << std::endl;
      /* month*/
//       std::cout << "rule<> month :" << std::endl;
//       str = "";
//       if (parse(str.c_str(), comment).full)
// 	throw ZiaException("comment rule failed");
//       str = "(this is a comment)";
//       if (!parse(str.c_str(), comment).full)
// 	throw ZiaException("comment rule failed");
  

//       std::cout<< "rule<> ALPHA :";
//       std::string str = "L";
//       std::cout<< "parsing :" << str << std::endl;

//       if (!parse(str.c_str(), ALPHA).full)
// 	throw ZiaException("Alpha rule failed");
  
//       str[0] = '-';
//       std::cout<< "parsing :" << str << std::endl;
//       if (parse(str.c_str(), ALPHA).full)
// 	throw ZiaException("Alpha rule failed");
  
//       /* rule CHAR*/
//       std::cout<< "rule<> CHAR :";
//       str = "-";
//       std::cout<< "parsing :" << str << std::endl;
//       if (!parse(str.c_str(), CHAR).full)
// 	throw ZiaException("CHAR rule failed");

//       str = "\b";
//       std::cout<< "parsing :" << str << std::endl;
//       if (!parse(str.c_str(), CHAR).full)
// 	throw ZiaException("CHAR rule failed");


//       /*chqr depqssqnt 127 doit fqil*/
//       str[0] = 255;
//       std::cout<< "parsing : " << str << std::endl;
//       if (parse(str.c_str(), CHAR).full)
// 	throw ZiaException("CHAR rule failed");
    
//       /*rule OCTET*/
//       std::cout << "rule<> OCTET :";
//       str[0] = 255;
//       std::cout<< "parsing : " << str << std::endl;
//       if (!parse(str.c_str(), OCTET).full)
// 	throw ZiaException("OCTET rule failed");
  
//       /*DIGIT*/
//       std::cout << "rule<> DIGIT :" << std::endl;
//       str = "0";
//       if (!parse(str.c_str(), DIGIT).full)
// 	throw ZiaException("DIGIT rule failed");
//       str = "99";
//       if (parse(str.c_str(), DIGIT).full)
// 	throw ZiaException("DIGIT rule failed");

//       /*CTL*/
//       std::cout << "rule<> CTL :" << std::endl;
//       str = "\b";
//       if (!parse(str.c_str(), CTL).full)
// 	throw ZiaException("CTL rule failed");
  
//       str = "o";
//       if (parse(str.c_str(), CTL).full)
// 	throw ZiaException("CTL rule failed");
//       /*CTL_N*/
  
//       std::cout << "rule<> CTL_N :" << std::endl;
//       str = "0";
//       if (!parse(str.c_str(),CTL_N).full)
// 	throw ZiaException("CTL_N rule failed");
  
//       str = "\b";
//       if (parse(str.c_str(), CTL_N).full)
// 	throw ZiaException("CTL_N rule failed");
  
//       /*CTLS*/
//       std::cout << "rule<> CTLS :" << std::endl;
//       str = "\b\b\t\n";
//       if (!parse(str.c_str(), CTLS).full)
// 	throw ZiaException("CTLS rule failed");
  
//       str = "\b lol \t\n";
//       if (parse(str.c_str(), CTLS).full)
// 	throw ZiaException("CTLS rule failed");
  
//       /*CTLS_N*/
//       std::cout << "rule<> CTLS_N :" << std::endl;
//       str = "\b\b\t\n";
//       if (parse(str.c_str(), CTLS_N).full)
// 	throw ZiaException("CTLS_N 1 rule failed");
  
//       str = " lol ";
//       if (!parse(str.c_str(), CTLS_N).full)
// 	throw ZiaException("CTLS_N  2 rule failed");
//       /*HT*/
//       std::cout << "rule<> HT :" << std::endl;
//       str = "\t";
//       if (!parse(str.c_str(), HT).full)
// 	throw ZiaException("HT rule failed");
  
//       str = "\n";
//       if (parse(str.c_str(), HT).full)
// 	throw ZiaException("HT rule failed");
  
//       /*HT_N*/
//       std::cout << "rule<> HT_N :" << std::endl;
//       str = "\t";
//       if (parse(str.c_str(), HT_N).full)
// 	throw ZiaException("HT_N rule failed");
  
//       str = "\n";
//       if (!parse(str.c_str(), HT_N).full)
// 	throw ZiaException("HT_N rule failed");

//       /*SP*/
//       std::cout << "rule<> SP :" << std::endl;
//       str = "\t";
//       if (parse(str.c_str(), SP).full)
// 	throw ZiaException(" rule failed");
  
//       str = " ";
//       if (!parse(str.c_str(), SP).full)
// 	throw ZiaException(" rule failed");

//       /*SP_N*/
//       std::cout << "rule<> SP_N :" << std::endl;
//       str = " ";
//       if (parse(str.c_str(), SP_N).full)
// 	throw ZiaException("SP_N rule failed");
  
//       str = "\t";
//       if (!parse(str.c_str(), SP_N).full)
// 	throw ZiaException("SP_N rule failed");

//       /*CR*/
//       std::cout << "rule<> CR :" << std::endl;
//       str = "o";
//       if (parse(str.c_str(), CR).full)
// 	throw ZiaException("CR rule failed");
  
//       str = "\r";
//       if (!parse(str.c_str(), CR).full)
// 	throw ZiaException("CR rule failed");

//       /*LF*/
//       std::cout << "rule<> LF :" << std::endl;
//       str = "y";
//       if (parse(str.c_str(), LF).full)
// 	throw ZiaException("LF rule failed");
  
//       str = "\n";
//       if (!parse(str.c_str(), LF).full)
// 	throw ZiaException("LF rule failed");

//       /*CRLF*/
//       std::cout << "rule<> CRLF :" << std::endl;
//       str = "\n\r";
//       if (parse(str.c_str(), CRLF).full)
// 	throw ZiaException("CRLF rule failed");
  
//       str = "\r\n";
//       if (!parse(str.c_str(), CRLF).full)
// 	throw ZiaException("CRLF rule failed");

//       /*LWS*/  
//       std::cout << "rule<> LWS :" << std::endl;
//       str = "\r\n";
//       if (parse(str.c_str(), LWS ).full)
// 	throw ZiaException("LWS 1 rule failed");
  
//       str = "\r\n ";
//       if (!parse(str.c_str(), LWS ).full)
// 	throw ZiaException("LWS 2 rule failed");
//       str = "\r\n\t";
//       if (!parse(str.c_str(), LWS ).full)
// 	throw ZiaException("LWS 3 rule failed");
      
     
//       /*TEXT  <any OCTET except CTLs,but including LWS>*/  
//       std::cout << "rule<> TEXT :" << std::endl;
//       str = "\b";
//       if (parse(str.c_str(), TEXT).full)
// 	throw ZiaException("TEXT 1 rule failed");
  
//       str = "\r\n\t";
//       if (!parse(str.c_str(), TEXT).full)
// 	throw ZiaException("TEXT 2 rule failed");

  
//       str = "Q";
//       if (!parse(str.c_str(), TEXT).full)
// 	throw ZiaException("TEXT 2 rule failed");

//       /*HEX*/
//       std::cout << "rule<> HEX :" << std::endl;
//       str = "T";
//       if (parse(str.c_str(), HEX).full)
// 	throw ZiaException("HEX rule failed");
  
//        str = "9";
//        if (!parse(str.c_str(), HEX).full)
//  	throw ZiaException("HEX rule failed");

//        str = "A";
//        if (!parse(str.c_str(), HEX).full)
//  	throw ZiaException("HEX rule failed");

//       /*separators*/
//        std::cout << "rule<> separators :" << std::endl;
//       str = "-";
//       if (parse(str.c_str(), separators).full)
// 	throw ZiaException("separators rule failed");
  
//        str = "(";
//        if (!parse(str.c_str(), separators).full)
//  	throw ZiaException("separators rule failed");

//        /*spearators_n*/
//        std::cout << "rule<> separators_n :" << std::endl;
//        str = ")";
//        if (parse(str.c_str(), separators_n).full)
//  	throw ZiaException("separators_n rule failed");
  
//        str = "-";
//        if (!parse(str.c_str(), separators_n).full)
//  	throw ZiaException("separators_n  rule failed");

//       /*token*/
//       std::cout << "rule<> token :" << std::endl;
//       str = "(";
//       if (parse(str.c_str(), token).full)
// 	throw ZiaException("token rule failed");
  
//       str = "c";
//       if (!parse(str.c_str(), token).full)
// 	throw ZiaException("token rule failed");

//        /*ctext*/
//        std::cout << "rule<> ctext :" << std::endl;
//        str = "(";
//        if (parse(str.c_str(), ctext).full)
//  	throw ZiaException("ctext rule failed");
  
//        str = "f";
//        if (!parse(str.c_str(), ctext).full)
//  	throw ZiaException("ctext rule failed");

//       /*quoted pair*/
//       std::cout << "rule<> quoted_pair :" << std::endl;
//       str = "p";
//       if (parse(str.c_str(), quoted_pair).full)
// 	throw ZiaException("quoted_pair 1 rule failed");
  
//       str = "\\ ";
//       if (!parse(str.c_str(), quoted_pair).full)
// 	throw ZiaException("quoted_pair rule failed");


//        /*qd text*/
//        std::cout << "rule<> qdtext:" << std::endl;
//        str = "\"";
//        if (parse(str.c_str(), qdtext).full)
//  	throw ZiaException("qdtext rule failed");
  
//        str = "<";
//        if (!parse(str.c_str(), qdtext).full)
// 	 throw ZiaException("qdtext rule failed");

//       /*quoted string*/
//       std::cout << "rule<> quoted_string :" << std::endl;
//       str = "\"fgfgfgfg";
//       if (parse(str.c_str(), quoted_string).full)
// 	throw ZiaException("quoted_string rule failed");
  
//       str = "\"rtrt\"";
//       if (!parse(str.c_str(), quoted_string).full)
// 	throw ZiaException("quoted_string rule failed");
    }
  catch(std::exception& e)
    {
      std::cout<< e.what() <<std::endl;
    }
  return (0);
}
