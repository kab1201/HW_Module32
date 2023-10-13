#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "DBConnection.h"

DBConnection mysql_db(static_cast<string>("localhost"), static_cast<string>("alla"), static_cast<string>("bdfqyj7mys"), static_cast<string>("Chat_DB"), 3306);

class MockDBConnection : public DBConnectionInterface {
public:
    ~MockDBConnection() override = default;
    MOCK_METHOD(bool, init, (), (override));
    MOCK_METHOD(bool, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, execQuery, (std::string const& query), (override));
};


//создаем фикстуру и тирдаун для наших тестов «на всякий случай»
class SomeTestSuite : public ::testing::Test {
protected:
    void SetUp() {
        someClassThatUseDb = new ClassThatUseDb(&mysql_db);
    }

    void TearDown() {
        delete someClassThatUseDb;
    }

protected:
    ClassThatUseDb* someClassThatUseDb;
};

TEST_F(SomeTestSuite, testOpen)
{
    MockDBConnection dBConnectionMock;
    bool reference = true;

    EXPECT_CALL(dBConnectionMock, open).WillOnce(::testing::Return(true));
    bool responce = someClassThatUseDb->openConnection();

    ASSERT_EQ(reference, responce);
}

TEST_F(SomeTestSuite, testExecQuery)
{
    MockDBConnection dBConnectionMock;
    int queryResult_reference = 0;

    EXPECT_CALL(dBConnectionMock, open).Times(1);
    EXPECT_CALL(dBConnectionMock, execQuery).WillOnce(::testing::Return(0));
    int queryResult_responce = someClassThatUseDb->useConnection("SELECT COUNT(*) FROM Users");

    ASSERT_EQ(queryResult_reference, queryResult_responce);
}

TEST_F(SomeTestSuite, testClose)
{
    MockDBConnection dBConnectionMock;

    EXPECT_CALL(dBConnectionMock, close).Times(1);
    someClassThatUseDb->closeConnection();
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    /*mysql_db.init();
    mysql_db.open();

    int queryResult = mysql_db.execQuery("SELECT COUNT(*) FROM Users");*/

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
