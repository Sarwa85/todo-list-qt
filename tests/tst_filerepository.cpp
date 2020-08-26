#include <QtTest>
#include <QDebug>

#include "filerepository.h"

class FileRepositoryTest : public QObject
{
    Q_OBJECT

public:
    FileRepositoryTest()
    {

    }
    ~FileRepositoryTest()
    {

    }

private slots:

    void initTestCase() {
        m_task_counter = 0;
    }

    void init() {
        m_repo = new FileRepository("test-repo", this);
    }

    void addTest_data() {
        QTest::addColumn<QString>("title");
        QTest::addColumn<QString>("text");
        QTest::addColumn<QString>("datetime");
        QTest::addColumn<bool>("valid");

        QTest::newRow("wszystko git") << "Zadanie 1" << "HELLO" << "2025-01-01 00:00:00" << true;
        QTest::newRow("brak tytułu") << "" << "HELLO" << "2025-01-01 00:00:00" << false;
        QTest::newRow("brak treści") << "Zadanie 3" << "" << "2025-01-01 00:00:00" << false;
        QTest::newRow("brak daty") << "Zadanie 3" << "HELLO" << "" << true;
    }

    void addTest()
    {
        QFETCH(QString, title);
        QFETCH(QString, text);
        QFETCH(QString, datetime);
        QFETCH(bool, valid);

        Task t(title, text, QDateTime::fromString(datetime, "yyyy-MM-dd hh:mm:ss"));
        QCOMPARE(m_repo->save(t), valid);
        if (valid)
            ++m_task_counter;

        auto tasks = m_repo->readAll();
        QCOMPARE(tasks.count(), m_task_counter);
    }

    void clean()
    {
        QFile repo_file(m_repo->name());
        m_repo->deleteLater();
        if (repo_file.exists())
            QVERIFY(QFile::remove(m_repo->name()));
        QVERIFY(!repo_file.exists());
    }

private:
    QPointer<Repository> m_repo;
    int m_task_counter;
};

QTEST_APPLESS_MAIN(FileRepositoryTest)

#include "tst_filerepository.moc"
