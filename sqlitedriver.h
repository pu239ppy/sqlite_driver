#pragma once

#include <algorithm>
#include <atomic>
#include <string>
#include <sqlite3.h>
#include <deque>
#include <functional>

extern std::atomic<bool> ok_to_write;
extern std::atomic<bool> ok_to_read;

extern bool opendb(std::string path, sqlite3 **db, int flags);

class DataRequest
{
public:
    DataRequest() = default;
    DataRequest(const DataRequest& othr) = delete;
    DataRequest& operator=(const DataRequest& othr)
    {
        if (this != &othr)
        {
            sqlLquery = othr.sqlLquery;
            requestIdentifier = othr.requestIdentifier;
        }
        return *this;
    }
    DataRequest(DataRequest&&) = default;
    DataRequest& operator=(DataRequest&&) = default;
    ~DataRequest() = default;

    private:
        std::string sqlLquery;
        std::string requestIdentifier;
};

const int QUEUE_DEPTH = 1000;
extern std::deque<DataRequest> requestQueue;