#include <QTest>

// add necessary includes here

class test : public QObject
{
    Q_OBJECT

public:
    test();
    ~test() override;

private slots:
    void test_case1();
};

test::test() {}

test::~test() = default;

void test::test_case1() {}

QTEST_APPLESS_MAIN(test)

#include "tst_test.moc"
