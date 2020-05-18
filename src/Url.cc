#include "Url.h"

#include <cstring>
#include <cctype>
#include <cstdlib>


namespace homer6{



    Url::Url(){

    }


    Url::Url( const string& s ){
        *this = this->fromString(s);
    }



    string Url::getScheme() const{
        return this->scheme;
    }



    string Url::getUsername() const{
        return this->username;
    }



    string Url::getPassword() const{
        return this->password;
    }



    string Url::getHost() const{
        return this->host;
    }



    unsigned short Url::getPort() const{

        if( this->port.size() > 0 ){
            return std::atoi( this->port.c_str() );
        }

        if( this->scheme == "https" ) return 443;
        if( this->scheme == "http" ) return 80;     
        if( this->scheme == "ssh" ) return 22;
        if( this->scheme == "ftp" ) return 21;

        return 0;

    }



    string Url::getPath() const{

        std::string tmp_path;
        unescape_path( this->path, tmp_path );
        return tmp_path;

    }



    string Url::getQuery() const{
        return this->query;
    }



    const multimap<string,string>& Url::getQueryParameters() const{
        return this->query_parameters;
    }



    string Url::getFragment() const{
        return this->fragment;
    }



    string Url::toString( int components ) const{

        std::string current_string;

        if( (components & this->scheme_component) != 0 && !this->scheme.empty() ){
            current_string = this->scheme;
            current_string += "://";
        }

        if( (components & username_component) != 0 && !this->username.empty() ){
            current_string += this->username;

            if( (components & password_component) != 0 && !this->password.empty() ){
                current_string += ":";
                current_string += this->password;
            }

            current_string += "@";
        }

        if( (components & host_component) != 0 ){
            if( this->ipv6_host ) current_string += "[";
            current_string += host;
            if( this->ipv6_host ) current_string += "]";
        }

        if( (components & port_component) != 0 && !this->port.empty() ){
            current_string += ":";
            current_string += this->port;
        }

        if( (components & path_component) != 0 && !this->path.empty() ){
            current_string += this->path;
        }

        if( (components & query_component) != 0 && !this->query.empty() ){
            current_string += "?";
            current_string += this->query;
        }

        if( (components & fragment_component) != 0 && !this->fragment.empty() ){
            current_string += "#";
            current_string += this->fragment;
        }

        return current_string;

    }



    Url Url::fromString( const std::string& source_string ){

        //string::const_iterator it = source_string.begin();
        const char *s = const_cast<const char*>( source_string.c_str() );

        Url new_url;

        // scheme
            std::size_t length = std::strcspn( s, ":" );
            new_url.scheme.assign(s, s + length);
            for( std::size_t i = 0; i < new_url.scheme.length(); ++i ){
                new_url.scheme[i] = std::tolower(new_url.scheme[i]);
            }
            s += length;


        // "://".
            if (*s++ != ':') throw std::runtime_error( "Expected : in url" );
            if (*s++ != '/') throw std::runtime_error( "Expected / in url" );
            if (*s++ != '/') throw std::runtime_error( "Expected / in url" );


        // username & password
            length = std::strcspn( s, "@:[/?#" );
            if( s[length] == '@' ){

                new_url.username.assign( s, s + length );
                s += length + 1;

            }else if( s[length] == ':' ){

                std::size_t length2 = std::strcspn( s + length, "@/?#" );
                if (s[length + length2] == '@'){
                    new_url.password.assign(s, s + length2 );
                    s += length2 + 1;
                }

            }


        // host
            if( *s == '[' ){

                length = std::strcspn( ++s, "]" );
                if( s[length] != ']' ) throw std::runtime_error( "Expected closing ] in ipv6 host" );

                new_url.host.assign( s, s + length );
                new_url.ipv6_host = true;
                s += length + 1;

                if( std::strcspn(s, ":/?#") != 0 ) throw std::runtime_error( "Expected host delimeter" );

            }else{

                length = std::strcspn( s, ":/?#" );
                new_url.host.assign( s, s + length );
                s += length;

            }


        // port
            if( *s == ':' ){
                
                length = std::strcspn( ++s, "/?#" );
                
                if( length == 0 ) throw std::runtime_error( "Expected port delimeter" );

                new_url.port.assign( s, s + length );

                for( std::size_t i = 0; i < new_url.port.length(); ++i ){

                    if( !std::isdigit(new_url.port[i]) ) throw std::runtime_error( "Expected port to be a numeric" );
                }

                s += length;

            }


        // path
            if( *s == '/' ){

                length = std::strcspn( s, "?#" );
                new_url.path.assign(s, s + length);
                std::string tmp_path;
                if( !unescape_path(new_url.path, tmp_path) ) throw std::runtime_error( "Failed to unescape path" );
                s += length;

            }else{
                
                new_url.path = "/";

            }
        

        // query
            if( *s == '?' ){
                length = std::strcspn( ++s, "#" );
                new_url.query.assign( s, s + length );
                s += length;
            }


        // fragment
            if( *s == '#' ) new_url.fragment.assign( ++s );

        return new_url;

    }



    bool Url::unescape_path( const std::string& in, std::string& out ){

        out.clear();
        out.reserve( in.size() );

        for( std::size_t i = 0; i < in.size(); ++i ){

            switch( in[i] ){

                case '%':

                    if( i + 3 <= in.size() ){

                        unsigned int value = 0;
                
                        for( std::size_t j = i + 1; j < i + 3; ++j ){
                
                            switch( in[j] ){

                                case '0': case '1': case '2': case '3': case '4':
                                case '5': case '6': case '7': case '8': case '9':
                                    value += in[j] - '0';
                                    break;

                                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                                    value += in[j] - 'a' + 10;
                                    break;

                                case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
                                    value += in[j] - 'A' + 10;
                                    break;
                                
                                default:
                                    return false;
                            }
                        
                            if( j == i + 1 ) value <<= 4;

                        }


                        out += static_cast<char>(value);
                        i += 2;

                    }else{

                        return false;

                    }
                    
                    break;



                case '-': case '_': case '.': case '!': case '~': case '*':
                case '\'': case '(': case ')': case ':': case '@': case '&':
                case '=': case '+': case '$': case ',': case '/': case ';':
                    out += in[i];
                    break;


                default:
                    if( !std::isalnum(in[i]) ) return false;
                    out += in[i];
                    break;

            }

        }

        return true;

    }



    bool operator==( const Url& a, const Url& b ){

        return a.scheme == b.scheme
            && a.username == b.username
            && a.password == b.password
            && a.host == b.host
            && a.port == b.port
            && a.path == b.path
            && a.query == b.query
            && a.fragment == b.fragment;

    }



    bool operator!=( const Url& a, const Url& b ){

        return !(a == b);

    }



    bool operator<( const Url& a, const Url& b ){

        if( a.scheme < b.scheme ) return true;
        if( b.scheme < a.scheme ) return false;

        if( a.username < b.username ) return true;
        if( b.username < a.username ) return false;

        if( a.password < b.password ) return true;
        if( b.password < a.password ) return false;

        if( a.host < b.host ) return true;
        if( b.host < a.host ) return false;

        if( a.port < b.port ) return true;
        if( b.port < a.port ) return false;

        if( a.path < b.path ) return true;
        if( b.path < a.path ) return false;

        if( a.query < b.query ) return true;
        if( b.query < a.query ) return false;

        return a.fragment < b.fragment;

    }



}








