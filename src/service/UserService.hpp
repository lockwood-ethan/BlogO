#ifndef USERSERVICE_HPP
#define USERSERVICE_HPP

#include "../db/BlogDbClient.hpp"
#include "../dto/PageDto.hpp"
#include "../dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"
#include <oatpp/core/Types.hpp>

class UserService {
private:
	typedef oatpp::web::protocol::http::Status Status;
private:
	OATPP_COMPONENT(std::shared_ptr<BlogDbClient>, m_database);
public:

	oatpp::Object<UserDto> createUser(const oatpp::Object<UserDto>& dto);
	oatpp::Object<UserDto> updateUser(const oatpp::Object<UserDto>& dto);
	oatpp::Object<UserDto> getUserById(const oatpp::String& id);
	oatpp::Object<PageDto<oatpp::Object<UserDto>>> getAllUsers(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
	oatpp::Object<StatusDto> deleteUserById(const oatpp::String& id);
};

#endif
