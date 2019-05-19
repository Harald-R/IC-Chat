#include "testsuitedb.h"
#include <iostream>
#include "dbmanager.h"

TestSuiteDB::TestSuiteDB()
{}

void TestSuiteDB::performTests()
{
    DbManager db;
    db.connect();

    int retVal = 0;

    // CHECK VALID USER
    retVal = db.checkCredentials("user_1", "password");
    if( retVal == 25 )
    {
        std::cout<<"PASSED: VALID USER"<<std::endl;
        passNum++;
    }
    else
    {
        std::cout<<"FAILED: VALID USER"<<std::endl;
    }
    totalNum++;

    // CHECK NON VALID USER
    retVal = db.checkCredentials("non_valid_user", "non_valid_password");
    if( retVal == -1 )
    {
        std::cout<<"PASSED: NON VALID USER"<<std::endl;
        passNum++;
    }
    else
    {
        std::cout<<"FAILED: NON VALID USER"<<std::endl;
    }
    totalNum++;

    // CHECK ADD VALID USER
    // REMOVE BY USER ID DOES NOT WORK, CAN'T FIND UID COLUMN

    if (db.userExists("valid_user"))
        db.removeUser("valid_user");

    retVal = db.addUser("valid_user", "valid_password", "test@email.com");
    if( retVal != -1)
    {
        std::cout<<"PASSED: ADD VALID USER\n\tINDEX:"<<retVal<<std::endl;
        passNum++;

        // TEST IF IT ALSO REMOVES IT BY INDEX
        retVal = db.removeUser((unsigned int)retVal);

        if( retVal == -1)
        {
            std::cout<<"PASSED: REMOVE VALID INDEX"<<std::endl;
            passNum++;
        }
        else
        {
            std::cout<<"FAILED: REMOVE VALID INDEX"<<std::endl;
        }
        totalNum++;
    }
    else
    {
        std::cout<<"FAILED: ADD VALID USER"<<std::endl;
    }
    totalNum++;

    // CHECK ADD EXISTING USER
    retVal = db.addUser("user_1", "password", "email@email.com");
    if( retVal == -1)
    {
        std::cout<<"PASSED: ADD NON VALID USER"<<std::endl;
        passNum++;
    }
    else
    {
        std::cout<<"FAILED: ADD VALID USER"<<std::endl;
    }
    totalNum++;

    // CHECK ADD EMPTY USER
    retVal = db.addUser("", "", "");
    if( retVal == -1)
    {
        std::cout<<"PASSED: ADD EMPTY USER"<<std::endl;
        passNum++;
    }
    else
    {
        std::cout<<"FAILED: ADD EMPTY USER"<<std::endl;
    }
    totalNum++;

    // CHECK REMOVE USER BY USERNAME
    retVal = db.addUser("temp_user", "temp_pass", "temp@email.com");

    if(retVal)
    {
        retVal = db.removeUser("temp_user");

        if( retVal != -1)
        {
            std::cout<<"PASSED: REMOVE VALID USERNAME"<<std::endl;
            passNum++;
        }
        else
        {
            std::cout<<"FAILED: REMOVE VALID USERNAME"<<std::endl;
        }
        totalNum++;
    }

    db.closeConnection();
}

bool TestSuiteDB::passed()
{
    if(passNum == totalNum)
        return true;
    return false;
}
