#include <QTest>
#include <string>
#include "..\src\estatemanager.h"
#include "..\src\realestate.h"

class TestManager : public QObject
{
    Q_OBJECT

private slots:
    // Будет выполняться перед каждым тестом
    void init() {
        manager = new EstateManager();
    }

    // Будет выполняться после каждого теста
    void cleanup() {
        delete manager;
    }

    void testAddEstate() {
        RealEstate re("Ivanov", "2023.10.10", "Red", 10000);
        manager->addEstate(re);

        const auto& list = manager->getEstates();
        QCOMPARE(list.size(), 1);
        QCOMPARE(list[0].owner, std::string("Ivanov"));
        QCOMPARE(list[0].cost, 10000);
    }

    void testRemoveByIndex() {
        manager->addEstate(RealEstate("A", "2021", "Blue", 100));
        manager->addEstate(RealEstate("B", "2022", "Green", 200));

        manager->removeEstate(0);

        const auto& list = manager->getEstates();
        QCOMPARE(list.size(), 1);
        QCOMPARE(list[0].owner, std::string("B"));
    }

    void testRemoveContainsDate() {
        manager->addEstate(RealEstate("User1", "2020-01-01", "White", 1000));
        manager->addEstate(RealEstate("User2", "2021-05-15", "Black", 2000));
        manager->addEstate(RealEstate("User3", "2020-12-31", "Grey", 3000));

        manager->removeContainsDate("2020");

        const auto& list = manager->getEstates();
        QCOMPARE(list.size(), 1);
        QCOMPARE(list[0].date, std::string("2021-05-15"));
    }

    void testRemoveContainsDateNoMatch() {
        manager->addEstate(RealEstate("User1", "2023", "Red", 100));
        manager->removeContainsDate("1999");

        QCOMPARE(manager->getEstates().size(), 1);
    }

private:
    EstateManager *manager;
};

QTEST_MAIN(TestManager)
#include "testmanager.moc"