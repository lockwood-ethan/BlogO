#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include <oatpp/Environment.hpp>
#include <oatpp/base/Log.hpp>
#include <oatpp/web/server/HttpRouter.hpp>

void run() {
	auto router = oatpp::web::server::HttpRouter::createShared();

	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"192.168.0.92", 3307, oatpp::network::Address::IP_4});

	oatpp::network::Server server(connectionProvider, connectionHandler);

	OATPP_LOGi("Blog", "Server running on port %s", connectionProvider->getProperty("port").getData());

	server.run();
}

int main() {
	oatpp::Environment::init();

	run();

	oatpp::Environment::destroy();
}
