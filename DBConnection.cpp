#include "DBConnection.h"

DBConnection::DBConnection(const string& host,
	const string& user,
	const string& password,
	const string& database,
	unsigned int port) :
	_host(host),
	_user(user),
	_password(password),
	_database(database),
	_port(port) {}
DBConnection::~DBConnection() {}

bool DBConnection::init()
{
	mysql_init(&_mysql);

	if (&_mysql == nullptr) {
		return false;
	}

	return true;
}
bool DBConnection::open()
{
	if (!mysql_real_connect(&_mysql, _host.c_str(), _user.c_str(), _password.c_str(), _database.c_str(), _port, NULL, 0)) {
		return false;
	}
	
    return true;
}
void  DBConnection::close()
{
    DBConnection::~DBConnection();
}
int DBConnection::execQuery(std::string const& sql_query)
{
    return mysql_query(&_mysql, sql_query.c_str());
}

ClassThatUseDb::ClassThatUseDb(DBConnection* connection) : connection_(connection) {}
ClassThatUseDb::~ClassThatUseDb() {}
bool ClassThatUseDb::init()
{
	return connection_->init();
}
bool ClassThatUseDb::openConnection()
{
	connection_->init();
    return connection_->open();
}
void ClassThatUseDb::closeConnection()
{
    connection_->close();
}
int ClassThatUseDb::useConnection(std::string sql_query)
{
    return connection_->execQuery(sql_query);
}