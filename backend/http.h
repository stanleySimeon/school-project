#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <map>
#include <sstream>
using namespace std;

//   HTTP request parser section - parse incoming HTTP requests

struct HttpRequest {
    string method;
    string path;
    map<string, string> headers;
    string body;
};

//   parser for HTTP request string into structured data
HttpRequest parseHttpRequest(string requestStr);

//   builder for formatted HTTP response
string buildHttpResponse(int statusCode, string statusText, string body, string contentType = "application/json");

#endif // HTTP_H
