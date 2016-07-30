///////////////////////////////////////////////////////////////////////////////
//
//  This sample demontrates a parser for a comma separated list of numbers
//  This is discussed in the "Quick Start" chapter in the Spirit User's Guide.
//
//  [ JDG 5/10/2002 ]
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_push_back_actor.hpp>
#include <iostream>
#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace BOOST_SPIRIT_CLASSIC_NS;
///////////////////////////////////////////////////////////////////////////////
bool	parse_numbers(char const* str, vector<char>& v)
{
  rule<>	SP = ch_p(' ');
  rule<>	CRLF = ch_p('\r') >> ch_p('\n');
  rule<>	alphanum = alnum_p;

  /* message-header */
  rule<>	field_name = token;
  rule<>	field_value = *( field-content | LWS );
  rule<>	field_content = ; // a remplir

  rule<>	message_header = field_name >> ":" >> [ field_value ];
  /* message-header */

  /* start-line */
  rule<>	Reason_Phrase =
    *<TEXT, excluding CR, LF>;

  rule<>	extension_code = 3*(digit);
  rule<>	Status_Code =
    str_p("200") | str_p("201") | str_p("202") | str_p("204") |
    str_p("301") | str_p("302") | str_p("304") | str_p("400") |
    str_p("401") | str_p("403") | str_p("404") | str_p("500") |
    str_p("501") | str_p("502") | str_p("503") | extension-code;

  rule<>	HTTP_Version =
    "HTTP/" >> +(digit) >> '.' >> +(digit) >> SP >> 3*(digit) >> SP;

  rule<>	Status_Line =
    HTTP_Version >> SP >> Status_Code >> SP >> Reason_Phrase >> CRLF;

  /////////////////////////////////////////////////////////////////
  rule<>	reg_name =
    1*( unreserved | escaped | "$" | "," | ";" | ":" | "@" | "&" | "=" | "+" )

  rule<>	port = +(digit);

  rule<>	IPv4address =
    +(digit) >> ch_p('.') >> +(digit) >> ch_p('.') >> +(digit) >>
    ch_p('.') >> +(digit);

  rule<>	toplabel =
    alpha | alpha >> *( alphanum | ch_p('-') ) >> alphanum;

  rule<>	domainlabel =
    alphanum | alphanum >> *( alphanum | ch_p('-') ) >> alphanum;

  rule<>	hostname =
    *( domainlabel >> ch_p('.') ) >> toplabel >> [ ch_p('.') ];

  rule<>	host = hostname | IPv4address;

  rule<>	hostport = host >> [ ch_p(':') >> port ];

  rule<>	escaped = '%' >> xdigit_p >> xdigit_p;

  rule<>	mark = '-' | '_' | '.' | '!' | '~' | '*' | '\'' | '(' | ')';

  rule<>	unreserved = alphanum | mark;

  rule<>	userinfo =
    *( unreserved | escaped | ';' | ':' | '&' | '=' | '+' | '$' | ',' )

  rule<>	server = [ [ userinfo >> ch_p('@') ] >> hostport ];

  rule<>	authority = server | reg_name; // reg_name a fournir

  rule<>	net_path =
    str_p("//") >> authority >> [ abs_path ];

  rule<>	hier_part =
    ( net_path | abs_path ) >> [ ch_p('?') >> query ];

  rule<>	scheme =
    alpha >> *( alpha | digit | ch_p('+') | ch_p('-') | ch_p('.') );

  rule<>	absoluteURI =
    scheme >> ch_p(':') >> ( hier_part | opaque_part );

  rule<>	Request-URI =
    ch_p('*') | absoluteURI | abs_path | authority;

  rule<>	extension_method = token;
  rule<>	Method= 
    "OPTIONS" | "GET" | "HEAD" | "POST" | "PUT" | "DELETE" |
    "TRACE" | "CONNECT" | extension_method;

  rule<>	Request_Line =
    Method >> SP >> Request_URI >> SP >> HTTP_Version >> CRLF;
  /////////////////////////////////////////////////////////////////

  rule<>	start_line = Request_Line | Status_Line;
  /* start-line */

  rule<>	generic_message =
    start_line >>
    *(message_header CRLF) >>
    CRLF >>
    [ message_body ]
    ;



  return parse(str,

	       //  Begin grammar
	       (
		generic_message
		)
	       ,
	       //  End grammar

	       space_p).full;
}

////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int
main()
{
  cout << "/////////////////////////////////////////////////////////\n\n";
  cout << "\t\tA comma separated list parser for Spirit...\n\n";
  cout << "/////////////////////////////////////////////////////////\n\n";

  cout << "Give me a comma separated list of numbers.\n";
  cout << "The numbers will be inserted in a vector of numbers\n";
  cout << "Type [q or Q] to quit\n\n";

  string str;
  while (getline(cin, str))
    {
      if (str.empty() || str[0] == 'q' || str[0] == 'Q')
	break;


      vector<char> v;
      if (parse_numbers(str.c_str(), v))
        {
	  cout << "-------------------------\n";
	  cout << "Parsing succeeded\n";
	  cout << str << " Parses OK: " << endl;

	  for (vector<char>::size_type i = 0; i < v.size(); ++i)
	    cout << i << ": " << v[i] << endl;

	  cout << "-------------------------\n";
        }
      else
        {
	  cout << "-------------------------\n";
	  cout << "Parsing failed\n";
	  cout << "-------------------------\n";
        }
    }

  cout << "Bye... :-) \n\n";
  return 0;
}
