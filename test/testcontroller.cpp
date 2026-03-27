#include <QTest>

// add necessary includes here

class TestController : public QObject
{
    Q_OBJECT
private slots:
    void test_case1();
    void test_case2();

};

void TestController::test_case1() {
    QVERIFY2(1,"");
}

void TestController::test_case2() {
    QCOMPARE(2,2);
}

QTEST_MAIN(TestController)
#include "testcontroller.moc"