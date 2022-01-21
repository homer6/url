#pragma once

#include <string>
#include <vector>

#include "Url.h"

namespace homer6{

    using std::string;
    using std::vector;

    class UrlList {

        public:
            UrlList(){};
            UrlList( const std::string& url_set_source );

            /**
             * Returns a lowercase version of the scheme.
             *
             * @throws if the schemes do not all match
             * @return string (eg. http)
             */
            string getScheme() const;

            std::vector<Url> urls;

    };

}

