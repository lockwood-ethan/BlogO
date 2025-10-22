#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "oatpp/core/macro/codegen.hpp"
#include <memory>
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/core/data/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpRequestHandler.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

class MessageDTO : public oatpp::DTO {
	DTO_INIT(MessageDTO, DTO)

	DTO_FIELD(Int32, statusCode);
	DTO_FIELD(String, message);
};

#include OATPP_CODEGEN_END(DTO)

class Handler : public oatpp::web::server::HttpRequestHandler {
private:
	std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;
public:
	Handler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper) : m_objectMapper(objectMapper) {}
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		auto message = MessageDTO::createShared();
		message->statusCode = 1024;
		message->message = "Hello DTO!";
		return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
	}
};

void run() {
	auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
	auto router = oatpp::web::server::HttpRouter::createShared();
	router->route("GET", "/hello", std::make_shared<Handler>(objectMapper));
	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});
	oatpp::network::Server server(connectionProvider, connectionHandler);
	OATPP_LOGI("Blog", "Server running on port %s", connectionProvider->getProperty("port").getData());
	server.run();
}

int main() {
	oatpp::base::Environment::init();
	run();
	oatpp::base::Environment::destroy();
	return 0;
}
