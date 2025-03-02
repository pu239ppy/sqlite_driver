#include "sqlitewriter.h"
#include "sqlitereader.h"

#include <thread>


int main()
{
    std::thread writerThread(SQLiteWriter("kvdb.db"));
    writerThread.join();

    std::thread readerThread(SQLiteReader("kvdb.db"));
    readerThread.join();

}
