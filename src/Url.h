#pragma once

#include <string>
using std::string;

#include <string_view>
using std::string_view;

#include <tuple>
using std::tuple;

#include <vector>
using std::vector;


// This class takes inspiration and some source code from 
// https://github.com/chriskohlhoff/urdl/blob/master/include/urdl/url.hpp


namespace homer6{

	/* 
		Url only makes one string copy and its storage is self-contained.
	
		UrlView is identical to Url, except UrlView does not make any string copies and thus depends on the 
			storage lifetime of the string passed to it.

		Url and UrlView are compliant with
			https://tools.ietf.org/html/rfc3986
			https://tools.ietf.org/html/rfc6874
			https://tools.ietf.org/html/rfc7320

			and adhere to https://rosettacode.org/wiki/URL_parser examples.

	*/

	class UrlView;


	class Url : public UrlView {

		protected:
			string url;

	};


	class UrlView{

		public:

			Url(){}
			Url( const char* s );
			Url( const std::string& s );

			string_view getScheme() const;
			string_view getUsername() const;
			string_view getPassword() const;
			string_view getHost() const;
			unsigned short getPort() const;
			string_view getPath() const;
			vector<tuple<string_view,string_view>> getQueryParameters() const;
			string_view getFragment() const;


			enum components_type{
				protocol_component = 1,
				user_info_component = 2,
				host_component = 4,
				port_component = 8,
				path_component = 16,
				query_component = 32,
				fragment_component = 64,
				all_components = 
					protocol_component | 
					user_info_component | 
					host_component | 
					port_component | 
					path_component | 
					query_component | 
					fragment_component
			};


			string to_string( int components = all_components ) const;

			static Url from_string( const std::string& s );

			friend bool operator==(const Url& a, const Url& b);
			friend bool operator!=(const Url& a, const Url& b);
			friend bool operator<(const Url& a, const Url& b);


		protected:

			static bool unescape_path(const std::string& in, std::string& out);

			string_view scheme;
			string_view username;
			string_view password;
			string_view host;
			string_view port;
			string_view path;
			vector<tuple<string_view,string_view>> query_parameters;
			string_view fragment;

			bool ipv6_host = false;

	};



}