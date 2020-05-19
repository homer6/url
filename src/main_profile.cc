#include "Url.h"

using homer6::Url;


int main(){

    for( int x = 0; x < 10000000; x++ ){

        Url url{ "https://www.wikipedia.org/what-me-worry?hello=there#wonder" };

    }
    
    return 0;

}


