#include <QtTest>
#include "qtnetworkng.h"

using namespace qtng;

class TestCoroutines: public QObject
{
    Q_OBJECT
private slots:
    void testStart();
    void testKill();
    void testKillall();
    void testJoinall();
    void testMap();
    void testeach();
};


void TestCoroutines::testStart()
{
    QSharedPointer<Event> event(new Event);
    QSharedPointer<Coroutine> c(Coroutine::spawn([event]{
        event->set();
    }));
    c->join();
    QVERIFY(event->isSet());
}


void TestCoroutines::testKill()
{
    QSharedPointer<Event> event(new Event);
    QSharedPointer<Coroutine> c(Coroutine::spawn([event]{
        Coroutine::sleep(0.1);
        event->set();
    }));
    Coroutine::sleep(0.01);
    c->kill();
    c->join();
    QVERIFY(!event->isSet());
}


void TestCoroutines::testKillall()
{
    CoroutineGroup operations;
    operations.spawn([]{
        Coroutine::sleep(0.1);
    });
    Coroutine::sleep(0.01);
    operations.killall();
    QVERIFY(operations.isEmpty());
}


void print_pow2(int i)
{
    Coroutine::sleep(0.1);
    qDebug() << i;
}

void TestCoroutines::testJoinall()
{
    CoroutineGroup operations;
    for(int i = 0; i < 10; ++i) {
        operations.spawn([i] { print_pow2(i); });
    }
    operations.joinall();
}

int pow2(int i)
{
    return i * i;
}


void TestCoroutines::testMap()
{
    QList<int> range10;
    for(int i = 0; i < 10; ++i)
        range10.append(i);

    QList<int> result = CoroutineGroup::map<int,int>(pow2, range10);
    for(int i =0; i < result.size(); ++i)
        qDebug() << result[i];
}

void output(int i)
{
    qDebug() << i;
}


void TestCoroutines::testeach()
{
    QList<int> range10;
    for(int i = 0; i < 10; ++i)
        range10.append(i);
    CoroutineGroup::each<int>(output, range10);
}


QTEST_MAIN(TestCoroutines)

#include "test_coroutines.moc"
