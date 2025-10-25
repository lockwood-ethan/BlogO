#ifndef DATABASECOMPONENT_HPP
#define DATABASECOMPONENT_HPP

#include "db/BlogDbClient.hpp"
#include "dto/ConfigDto.hpp"

#include "oatpp/core/macro/component.hpp"

class DatabaseComponent {
public:
	  OATPP_CREATE_COMPONENT(std::shared_ptr<BlogDbClient>, blogDbClient)([] {
	    OATPP_COMPONENT(oatpp::Object<ConfigDto>, config);
    		auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(config->dbConnectionString);
    		auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider, 10, std::chrono::seconds(5));
    		auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);
    		return std::make_shared<BlogDbClient>(executor);
  }());
};

#endif
