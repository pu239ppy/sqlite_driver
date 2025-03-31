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
        bool enqueueRequest(DataRequest& request) const;
        bool deueueRequest(DataRequest& request) const;
    private:
        std::string d_filepath;
};
