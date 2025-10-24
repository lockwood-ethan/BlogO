#include "MyControllerTest.hpp"

#include "/home/bashthestampede/dev/BlogO/src/controller/MyController.hpp"

#include "app/MyApiTestClient.hpp"
#include "app/TestComponent.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"

#include "oatpp-test/web/ClientServerTestRunner.hpp"

void MyControllerTest::onRun() {
	TestComponent component;
	oatpp::test::web::ClientServerTestRunner runner;
	runner.addController(std::make_shared<MyController>());
	runner.run([this, &runner] {
		OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);
		OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);
		auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);
		auto client = MyApiTestClient::createShared(requestExecutor, objectMapper);
		auto response = client->getHello();
		OATPP_ASSERT(response->getStatusCode() == 200);
		auto message = response->readBodyToDto<oatpp::Object<MessageDto>>(objectMapper.get());
		OATPP_ASSERT(message);
		OATPP_ASSERT(message->statusCode == 200);
		OATPP_ASSERT(message->message == "Hello World!");
	}, std::chrono::minutes(10));

	std::this_thread::sleep_for(std::chrono::seconds(1));
}
