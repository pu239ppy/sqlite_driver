#pragma once
#include <string>
#include <mutex>
#include <deque>
#include "sqlitedriver.h"



class SQLiteReader
{
    public:
        SQLiteReader(const std::string& filepath);
        void operator()();
        bool enqueueRequest(DataRequest& request);
        bool deueueRequest(DataRequest& request);
    private:
        std::string d_filepath;
        std::deque<DataRequest> requestQueue;
};
