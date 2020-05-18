#include "Url.h"

using homer6::Url;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

template<class T>
bool equal( const T& left, const T& right ){

    if( left != right ){
        cout << "    FAIL: " << left << " != " << right << endl;
        return false;
    }else{
        cout << "    PASS: " << left << " == " << right << endl;
        return true;
    }

};



bool test_url( const string& url_source, const string& scheme, const string& host, unsigned short port, const string& path, const string& query, const string& fragment ){
    
    bool success = true;

    Url url{ url_source };

    cout << endl << url_source << endl;

    if( !equal(url.getScheme(), scheme) ) success = false;
    if( !equal(url.getHost(), host) ) success = false;
    if( !equal(url.getPort(), port) ) success = false;
    if( !equal(url.getPath(), path) ) success = false;
    if( !equal(url.getQuery(), query) ) success = false;
    if( !equal(url.getFragment(), fragment) ) success = false;


    if( success ){
        cout << "PASSED" << endl;
    }else{
        cout << "FAILED" << endl;
    }

    return success;

}




int main(){

    int fail_count = 0;
    int test_count = 0;
    

    if( !test_url(
        "https://www.wikipedia.org/what-me-worry?hello=there#wonder",
        "https",
        "www.wikipedia.org",
        443,
        "/what-me-worry",
        "hello=there",
        "wonder"
    )) fail_count++;
    test_count++;


    if( !test_url(
        "jdbc:mysql://test_user:ouupppssss@localhost:3306/sakila?profileSQL=true",
        "jdbc:mysql",
        "localhost",
        3306,
        "/sakila",
        "profileSQL=true",
        ""
    )) fail_count++; 
    test_count++;


    if( !test_url(
        "ftp://ftp.is.co.za/rfc/rfc1808.txt",
        "ftp",
        "ftp.is.co.za",
        21,
        "/rfc/rfc1808.txt",
        "",
        ""
    )) fail_count++;
    test_count++;



    cout << endl << "Total Tests: " << test_count << endl;
    cout << "Total Failed: " << fail_count << endl;

  
  /*
  http://www.ietf.org/rfc/rfc2396.txt#header1
  ldap://[2001:db8::7]/c=GB?objectClass=one&objectClass=two
  mailto:John.Doe@example.com
  news:comp.infosystems.www.servers.unix
  tel:+1-816-555-1212
  telnet://192.0.2.16:80/
  urn:oasis:names:specification:docbook:dtd:xml:4.1.2

    */





    return 0;

}


