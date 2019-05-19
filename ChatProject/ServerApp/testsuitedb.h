#ifndef TESTSUITEDB_H
#define TESTSUITEDB_H


class TestSuiteDB
{
public:
    TestSuiteDB();
    void performTests();
    bool passed();
private:
    int passNum = 0;
    int totalNum = 0;
};

#endif // TESTSUITEDB_H
