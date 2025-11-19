#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include "http.h"
#include "datastore.h"
#include "handlers.h"

using namespace std;

//   router for HTTP requests to appropriate handlers
string routeRequest(DataStore& store, HttpRequest req);

#endif
