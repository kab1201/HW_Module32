#pragma once
#include <string>
#include "mysql.h"

using namespace std;

class DBConnectionInterface {
public:
    DBConnectionInterface() {}
    virtual ~DBConnectionInterface() {}
    virtual bool init() = 0;
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual int execQuery(std::string const& sql_query) = 0;
};

class DBConnection : public DBConnectionInterface
{
public:
    DBConnection(const string& host,
        const string& user,
        const string& password,
        const string& database,
        unsigned int port);
    virtual ~DBConnection();
    virtual bool init() override;
    virtual bool open() override;
    virtual void close() override;
    virtual int execQuery(string const& sql_query) override;

private:
    MYSQL _mysql;
    const string _host;
    const string _user;
    const string _password;
    const string _database;
    unsigned int _port{ 0 };
};

class ClassThatUseDb {
private:
    DBConnection* connection_;
public:
    ClassThatUseDb(DBConnection* connection);
    ~ClassThatUseDb();
    bool init();
    bool openConnection();
    void closeConnection();
    int useConnection(string sql_query);
};