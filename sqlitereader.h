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
        bool enqueueRequest(DataRequest& request);
        bool deueueRequest(DataRequest& request);
    private:
        std::string d_filepath;
        std::mutex queueLock;
        std::deque<DataRequest> requestQueue;
};
