#include "sqlitereader.h"
#include <sqlite3.h>
#include <iostream>
#include <unistd.h>
#include "sqlitedriver.h"
#include <mutex>

static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    std::cerr << (const char*)data << std::endl;
    for (i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

SQLiteReader::SQLiteReader(const std::string& filepath):
    d_filepath(std::move(filepath))
{}

void SQLiteReader::operator()() const
{
    sqlite3 *db;
    bool openres = opendb(d_filepath, &db, SQLITE_OPEN_READONLY);
    if (false == openres)
    {
        std::cerr << "Exiting reader thread" << std::endl;
        return;
    }
    


    while (true == ok_to_read.load())
    {

        std::string SQL = "SELECT * FROM DATA LIMIT 10";
        char *errMsg = 0;
        const char* data = "Callback function called";
        int exec_rc = sqlite3_exec(db, SQL.c_str(), &callback, (void*)data, &errMsg);

        DataRequest request;
        bool result = deueueRequest(request);

        if (SQLITE_OK != exec_rc)
        {
            std::cerr << "SQL Error " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
            std::cerr << "Exiting reader thread" << std::endl;
            return;
        }
        sleep(5);
    }
    sqlite3_close(db);
    std::cout << "Exiting reader thread" << std::endl;
    return;
}

bool SQLiteReader::enqueueRequest(DataRequest& request)
{
    std::lock_guard<std::mutex> lock(queueLock);
    if (requestQueue.size() >= QUEUE_DEPTH)
    {
        std::cout << "Queue is full, cannot enqueue request." << std::endl;
        return false; // Queue is full
    }
    requestQueue.push_front(request);
    return true;
}

bool SQLiteReader::deueueRequest(DataRequest& request)
{
    std::lock_guard<std::mutex> lock(queueLock);
    if (requestQueue.empty())
    {
        std::cout << "Queue is empty, cannot dequeue request." << std::endl;
        return false; // Queue is empty
    }
    request = requestQueue.back();
    requestQueue.pop_back();
    return true;
}