#include "UrlList.h"
#include <sstream>
#include <algorithm>


namespace homer6{

    static vector<string> split_string( const string& source, char delimiter ){

        vector<string> output;
        std::istringstream buffer( source );
        string token;

        while( std::getline(buffer, token, delimiter) ) {
            output.push_back( token );
        }

        return output;

    }

    static string to_lower( const string& source ){
        string destination = source;
        std::transform(
            source.begin(),
            source.end(),
            destination.begin(),
            [](unsigned char c){ return std::tolower(c); }
        );
        return destination;
    }



    UrlList::UrlList( const std::string& url_set_source ){

        vector<string> url_sources = split_string( url_set_source, ',' );
        for( const string& url_source : url_sources ){
            this->urls.push_back( { url_source } );
        }

    }


    string UrlList::getScheme() const{

        string current_scheme;
        int x = 0;
        for( const Url& url : this->urls ){
            const string new_scheme = to_lower( url.getScheme() );
            if( x == 0 ){
                //first url
                current_scheme = new_scheme;
            }else{
                if( current_scheme != new_scheme ){
                    throw std::runtime_error( "Url schemes do not match in UrlList" );
                }
            }
            x++;
        }
        return current_scheme;

    }

}
