#pragma once
#include <string>
#include <mutex>
#include <deque>
#include "sqlitedriver.h"



class SQLiteReader
{
    public:
        SQLiteReader(const std::string& filepath);
        void operator()() const;
        bool enqueueRequest(const DataRequest& request);
        const DataRequest& deueueRequest(void);
    private:
        std::string d_filepath;
        std::mutex queueLock;
        std::deque<DataRequest> requestQueue;
};
