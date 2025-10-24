#ifndef UserDto_hpp
#define UserDto_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include <oatpp/core/base/Environment.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(Role, v_int32,
     VALUE(GUEST, 0, "ROLE_GUEST"),
     VALUE(ADMIN, 1, "ROLE_ADMIN")
)

class UserDto : public oatpp::DTO{

	DTO_INIT(UserDto, DTO)

	DTO_FIELD(String, id);
	DTO_FIELD(String, userName, "username");
	DTO_FIELD(String, email, "email");
	DTO_FIELD(String, password, "password");
	DTO_FIELD(Enum<Role>::AsString, role, "role");
};

/* TODO - Add more DTOs here */

#include OATPP_CODEGEN_END(DTO)

#endif
