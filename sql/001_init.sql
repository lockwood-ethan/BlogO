CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE IF NOT EXISTS users (
	id		VARCHAR(256) PRIMARY KEY,
	username	VARCHAR(256) NOT NULL,
	email		VARCHAR(256) NOT NULL,
	password	VARCHAR(256) NOT NULL,
	role		VARCHAR(256) NULL,
	CONSTRAINT	UK_USER_USERNAME UNIQUE (username),
	CONSTRAINT	UK_USER_EMAIL UNIQUE (email)
);

INSERT INTO users
(id, username, email, password) VALUES (gen_random_uuid(), 'admin', 'admin@domain.com', 'admin', 'ROLE_ADMIN');

CREATE TABLE IF NOT EXISTS posts (
	id		VARCHAR(256) PRIMARY KEY,
	title		VARCHAR(256) NOT NULL,
	content		TEXT NOT NULL,
	created_at	TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	updated_at	TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	user_id		INT,
	FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE OR REPLACE FUNCTION update_modified_column()
RETURNS TRIGGER AS $posts_update$
BEGIN
	NEW.updated_at = now();
	RETURN NEW;
END;
$posts_update$ LANGUAGE 'plpgsql';

CREATE TRIGGER update_posts_modtime
	BEFORE UPDATE ON posts
	FOR EACH ROW EXECUTE FUNCTION update_modified_column();

CREATE TABLE IF NOT EXISTS comments (
	id 		VARCHAR(256) PRIMARY KEY,
	content		TEXT NOT NULL,
	created_at	TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
	post_id		VARCHAR(256),
	user_id		VARCHAR(256),
	FOREIGN KEY (post_id) REFERENCES posts(id),
	FOREIGN KEY (user_id) REFERENCES users(id)
);
