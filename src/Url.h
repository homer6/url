#pragma once

#include <string>
using std::string;

#include <map>
using std::multimap;


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
            and adheres to https://rosettacode.org/wiki/URL_parser examples.

        Url and UrlView will use default ports for known schemes, if the port is not explicitly provided.

    */



    class Url{

        public:

            Url();
            Url( const std::string& s );

            string getScheme() const;
            string getUsername() const;
            string getPassword() const;
            string getHost() const;
            unsigned short getPort() const;
            string getPath() const;
            string getQuery() const;
            const multimap<string,string>& getQueryParameters() const;
            string getFragment() const;


            enum components_type{
                scheme_component = 1,
                username_component = 2,
                password_component = 4,
                host_component = 8,
                port_component = 16,
                path_component = 32,
                query_component = 64,
                fragment_component = 128,
                all_components = 
                    scheme_component | 
                    username_component | 
                    password_component | 
                    host_component | 
                    port_component | 
                    path_component | 
                    query_component | 
                    fragment_component
            };


            string toString( int components = all_components ) const;

            static Url fromString( const std::string& s );

            friend bool operator==(const Url& a, const Url& b);
            friend bool operator!=(const Url& a, const Url& b);
            friend bool operator<(const Url& a, const Url& b);


        protected:

            static bool unescape_path(const std::string& in, std::string& out);

            string scheme;
            string username;
            string password;
            string host;
            string port;
            string path;
            string query;
            multimap<string,string> query_parameters;
            string fragment;

            bool ipv6_host = false;

    };



}