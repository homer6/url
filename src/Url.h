// homer::Url v0.2.0
// MIT License
// https://github.com/homer6/url

// This class takes inspiration and some source code from 
// https://github.com/chriskohlhoff/urdl/blob/master/include/urdl/url.hpp

#pragma once

#include <string>
using std::string;

#include <string_view>
using std::string_view;

#include <map>
using std::multimap;


namespace homer6{

    /* 
        WARNING: Url does not make any string copies and thus depends on the storage lifetime of the string passed to it.

        Url is compliant with
            https://tools.ietf.org/html/rfc3986
            https://tools.ietf.org/html/rfc6874
            https://tools.ietf.org/html/rfc7320
            and adheres to https://rosettacode.org/wiki/URL_parser examples.

        Url will use default ports for known schemes, if the port is not explicitly provided.

    */


    class Url{

        public:

            Url();
            Url( const std::string& s );

            string_view getScheme() const;
            string_view getUsername() const;
            string_view getPassword() const;
            string_view getHost() const;
            unsigned short getPort() const;
            string_view getPath() const;
            string_view getQuery() const;
            //const multimap<string_view,string_view>& getQueryParameters() const;
            string_view getFragment() const;


            void fromString( const std::string& s );

            friend bool operator==(const Url& a, const Url& b);
            friend bool operator!=(const Url& a, const Url& b);
            friend bool operator<(const Url& a, const Url& b);

            void setSecure( bool secure );

            bool isIpv6() const;
            bool isSecure() const;

            //string toString() const;
            //explicit operator string() const;


        protected:

            static bool unescape_path(const std::string& in, std::string& out);

            string_view captureUpTo( const string_view right_delimiter, const string& error_message = "" );            
            bool moveBefore( const string_view right_delimiter );
            bool existsForward( const string_view right_delimiter );       

            string_view scheme;
            string_view authority;
            string_view user_info;
            string_view username;
            string_view password;
            string_view host;
            string_view port;
            string_view path;
            string_view query;
            //multimap<string_view,string_view> query_parameters;
            string_view fragment;

            bool secure = false;
            bool ipv6_host = false;
            bool authority_present = false;

            size_t left_position = 0;
            size_t right_position = 0;
            string_view parse_target;

    };



}