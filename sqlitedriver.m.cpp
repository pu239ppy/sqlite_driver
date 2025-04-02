#include "connectionhandler.h"
#include "sqlitewriter.h"
#include "sqlitereader.h"
#include "sqlitedriver.h"
#include <csignal>
#include <thread>
#include <atomic>
#include <string>
#include <iostream>
#include <sqlite3.h>


std::atomic<bool> ok_to_write;
std::atomic<bool> ok_to_read;
std::atomic<bool> ok_to_handle_reads;

int main()
{   
    std::signal(SIGINT, [](int signal)
    {
        ok_to_read.store(false);
        ok_to_write.store(false);
        ok_to_handle_reads.store(false);
    });

    ok_to_read.store(true);
    ok_to_write.store(true);
    ok_to_handle_reads.store(true);

    std::thread connectionThread(ConnectionHandler());
    std::thread writerThread(SQLiteWriter("kvdb.db"));
    std::thread readerThread(SQLiteReader("kvdb.db"));
    //connectionThread.join();
    // if connection handler exits for some reason we should quit
    ok_to_read.store(false);
    ok_to_write.store(false);
    writerThread.join();
    readerThread.join();
}
