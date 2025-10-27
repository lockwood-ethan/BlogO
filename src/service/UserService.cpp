#include "UserService.hpp"
#include <oatpp/core/Types.hpp>
#include <oatpp/web/protocol/http/Http.hpp>

oatpp::Object<UserDto> UserService::createUser(const oatpp::Object<UserDto>& dto) {

	auto dbResult = m_database->createUser(dto);
	OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

	auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
	OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
	return result[0];
}

oatpp::Object<UserDto> UserService::updateUser(const oatpp::Object<UserDto>& dto) {

	auto dbResult = m_database->updateUser(dto);
	OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
	auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
	OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");
	return result[0];
}

oatpp::Object<UserDto> UserService::getUserById(const oatpp::String& id) {
	
	auto dbResult = m_database->getUserById(id);
	OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
	OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "User not found");

	auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<UserDto>>>();
	OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

	return result[0];
}


