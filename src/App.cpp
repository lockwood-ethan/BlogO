#include "AppComponent.hpp"
#include "controller/MyController.hpp"

#include "oatpp/network/Server.hpp"

void run() {
	AppComponent components;
	OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
	auto myController = std::make_shared<MyController>();
	router->addController(myController);
	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
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
