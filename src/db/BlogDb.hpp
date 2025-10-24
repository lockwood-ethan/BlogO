#ifndef BLOGDB_HPP
#define BLOGDB_HPP

#include "oatpp-postgresql/orm.hpp"
#include "../dto/UserDto.hpp"
#include <oatpp/core/base/Environment.hpp>
#include <oatpp/orm/DbClient.hpp>
#include <oatpp/orm/Executor.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

// BlogDb client definitions
class BlogDb : public oatpp::orm::DbClient {
public:
	BlogDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
		: oatpp::orm::DbClient(executor) {
		oatpp::orm::SchemaMigration migration(executor);
		migration.addFile(1, "/home/bashthestampede/dev/BlogO/sql/001_init.sql");
		migration.migrate();
		auto version = executor->getSchemaVersion();
		OATPP_LOGD("BlogDb", "Migration - OK. Version=%d.", version);
	}

	QUERY(createUser,
       		"INSERT INTO users"
       		"(id, username, email, password, role) VALUES "
       		"(gen_random_uuid(), :user.username, :user.email, :user.password, :user.role"
       		"RETURNING *;",
       		PREPARE(true),
		PARAM(oatpp::Object<UserDto>, user))
	
};

#endif
