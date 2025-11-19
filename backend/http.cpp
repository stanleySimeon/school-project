#include "http.h"

// parser for HTTP request string into structured data
HttpRequest parseHttpRequest(string requestStr) {
    HttpRequest req;
    istringstream stream(requestStr);
    string line;
    
    //   parser for request line
    getline(stream, line);
    istringstream requestLine(line);
    requestLine >> req.method >> req.path;
    
    //   parser for headers
    while (getline(stream, line) && line != "\r" && !line.empty()) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 2);
            if (value.back() == '\r') value.pop_back();
            req.headers[key] = value;
        }
    }
    
    //   parser for body
    string bodyContent;
    while (getline(stream, line)) {
        bodyContent += line;
    }
    req.body = bodyContent;
    
    return req;
}

//   builder for formatted HTTP response
string buildHttpResponse(int statusCode, string statusText, string body, string contentType) {
    ostringstream response;
    response << "HTTP/1.1 " << statusCode << " " << statusText << "\r\n";
    response << "Content-Type: " << contentType << "\r\n";
    response << "Content-Length: " << body.length() << "\r\n";
    response << "Access-Control-Allow-Origin: *\r\n";
    response << "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n";
    response << "Access-Control-Allow-Headers: Content-Type, Authorization\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    response << body;
    return response.str();
}
