#ifndef BLOGDBCLIENT_HPP
#define BLOGDBCLIENT_HPP

#include "oatpp-postgresql/orm.hpp"
#include "../dto/UserDto.hpp"
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/orm/DbClient.hpp>
#include <oatpp/orm/Executor.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

// BlogDbClient client definitions
class BlogDbClient : public oatpp::orm::DbClient {
public:
	BlogDbClient(const std::shared_ptr<oatpp::orm::Executor>& executor)
		: oatpp::orm::DbClient(executor) {
		oatpp::orm::SchemaMigration migration(executor);
		migration.addFile(1, "/home/bashthestampede/dev/BlogO/sql/001_init.sql");
		migration.migrate();
		auto version = executor->getSchemaVersion();
		OATPP_LOGD("BlogDbClient", "Migration - OK. Version=%d.", version);
	}

	QUERY(createUser,
       		"INSERT INTO users"
       		"(id, username, email, password, role) VALUES "
       		"(gen_random_uuid(), :user.username, :user.email, :user.password, :user.role"
       		"RETURNING *;",
       		PREPARE(true),
		PARAM(oatpp::Object<UserDto>, user))
	
	QUERY(updateUser,
       		"UPDATE users "
       		"SET "
       		" username=:user.username, "
       		" email=:user.email, "
       		" password=:user.password, "
       		" role=:user.role "
       		"WHERE "
       		" id=:user.id "
       		"RETURNING *;",
       		PREPARE(true),
		PARAM(oatpp::Object<UserDto>, user))
	
	QUERY(getUserById,
       		"SELECT * FROM users WHERE id=:id",
       		PREPARE(true),
       		PARAM(oatpp::String, id))

	QUERY(getAllUsers,
       		"SELECT * FROM users LIMIT :limit OFFSET :offset;",
       		PREPARE(true),
       		PARAM(oatpp::UInt32, offset),
       		PARAM(oatpp::UInt32, limit))
	
	QUERY(deleteUserById,
       		"DELETE FROM users WHERE id=:id",
       		PREPARE(true),
       		PARAM(oatpp::String, id))
};

#include OATPP_CODEGEN_END(DbClient)

#endif
