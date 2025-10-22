#include "oatpp-1.4.0/oatpp/oatpp/web/server/AsyncHttpConnectionHandler.hpp"

#include "oatpp-1.4.0/oatpp/oatpp/network/Server.hpp"
#include "oatpp-1.4.0/oatpp/oatpp/network/tcp/server/ConnectionProvider.hpp"
#include <oatpp-1.4.0/oatpp/oatpp/network/Address.hpp>
#include <oatpp-1.4.0/oatpp/oatpp/web/server/HttpConnectionHandler.hpp>

void run() {
	auto router = oatpp::web::server::HttpRouter::createShared();

	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"192.168.0.92", 3307, oatpp::network::Address::IP_4});

	oatpp::network::Server server(connectionProvider, connectionHandler);

	OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

	server.run();
}

int main() {

	oatpp::base::Environment::init();

	run();

	oatpp::base::Environment::destroy();

	return 0;
}
