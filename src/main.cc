#include "Url.h"
using homer6::Url;
using homer6::UrlView;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

int main(){
	
	Url url{ "https://www.wikipedia.org" };

	cout << url.getScheme() << endl;
	
	return 0;

}


