#ifndef MyController_hpp
#define MyController_hpp

#include "../dto/UserDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class MyController : public oatpp::web::server::api::ApiController {
public:
	MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) {}
public:
	ENDPOINT("GET", "/hello", root) {
		auto dto = UserDto::createShared();
		return createDtoResponse(Status::CODE_200, dto);
	}
};

#include OATPP_CODEGEN_END(ApiController)

#endif 
