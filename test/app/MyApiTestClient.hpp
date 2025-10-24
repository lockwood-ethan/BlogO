#ifndef MyApiTestClient_hpp
#define MyApiTestClient_hpp

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class MyApiTestClient : public oatpp::web::client::ApiClient {
	API_CLIENT_INIT(MyApiTestClient)
	API_CALL("GET", "/hello", getHello)
};

#include OATPP_CODEGEN_END(ApiClient)

#endif
