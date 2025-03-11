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

bool opendb(std::string path, sqlite3 **db, int flags)
{
    int openrc = sqlite3_open_v2(path.c_str(), db, flags, NULL);
    if( openrc )
    {
        std::cerr << "Can't open database: " <<  sqlite3_errmsg(*db) << std::endl;
        sqlite3_close(*db);
        return false;
    }
    return true;
}

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
    std::thread readerThread(SQLiteReader("kvdb.db"));
    writerThread.join();
    readerThread.join();
}
