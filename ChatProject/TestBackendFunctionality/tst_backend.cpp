#include <QtTest>

// add necessary includes here

class backend : public QObject
{
    Q_OBJECT

public:
    backend();
    ~backend();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

backend::backend()
{

}

backend::~backend()
{

}

void backend::initTestCase()
{

}

void backend::cleanupTestCase()
{

}

void backend::test_case1()
{

}

QTEST_APPLESS_MAIN(backend)

#include "tst_backend.moc"
