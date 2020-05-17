#pragma once

#include "Url.h"

namespace homer6{


	Url::Url(){


	}



	Url::Url( const char* s ){

		*this = from_string(s);

	}



	Url::Url( const string& s ){

		*this = from_string(s);

	}



	string_view Url::getScheme() const{
		return scheme;
	}

	string_view Url::getUsername() const{
		return username;
	}

	string_view Url::getPassword() const{
		return password;
	}

	string_view Url::host() const{
		return host;
	}

	unsigned short Url::port() const{

	}

	string_view Url::path() const{

	}

	string_view Url::query() const{
		return query;
	}

	string_view Url::fragment() const{
		return fragment;
	}

	/// Components of the URL, used with @c from_string.
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


	string Url::to_string( int components = all_components ) const{



	}


	static Url Url::from_string( const std::string& s ){



	}

	bool Url::operator==(const Url& a, const Url& b){


	}



	bool Url::operator!=(const Url& a, const Url& b){



	}


	bool Url::operator<(const Url& a, const Url& b){



	}




}