#ifndef SwaggerComponent_hpp
#define SwaggerComponent_hpp

#include "dto/ConfigDto.hpp"

#include "oatpp-1.3.0/oatpp-swagger/Model.hpp"
#include "oatpp-1.3.0/oatpp-swagger/Resources.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include "oatpp/core/macro/component.hpp"

class SwaggerComponent {
public:
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo) ([] {
		OATPP_COMPONENT(oatpp::Object<ConfigDto>, config);
		oatpp::swagger::DocumentInfo::Builder builder;
	    	builder
		.setTitle("user-service")
		.setDescription("Service which stores and reads user info to/from postgresql database")
		.setVersion("1.0")
	      	.setContactName("Ethan Lockwood")
		.setContactUrl("https://linkedin.com/in/ethan-lockwood-dev")

		.addServer("http://localhost:" + oatpp::utils::conversion::int32ToStr(config->port), "server on localhost");
		return builder.build();
	}());
	
	OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources) ([] {
		return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
	}());
};

#endif
