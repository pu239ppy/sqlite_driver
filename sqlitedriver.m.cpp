#include "sqlitewriter.h"
#include "sqlitereader.h"
#include "sqlitedriver.h"
#include <csignal>
#include <thread>
#include <atomic>

std::atomic<bool> ok_to_write;
std::atomic<bool> ok_to_read;

int main()
{
    std::signal(SIGINT, [](int signal)
    {
        ok_to_read.store(false);
        ok_to_write.store(false);
    });

    ok_to_read.store(true);
    ok_to_write.store(true);

    std::thread writerThread(SQLiteWriter("kvdb.db"));
    writerThread.join();

    std::thread readerThread(SQLiteReader("kvdb.db"));
    readerThread.join();
}
