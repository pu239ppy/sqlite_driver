#pragma once
#include <string>
#include <mutex>
#include <deque>
#include "datarequest.h"

//const int QUEUE_DEPTH = 1000;

class SQLiteReader
{
    public:
        SQLiteReader(const std::string& filepath);
        void operator()();
        //bool enqueueRequest(DataRequest& request);
        //bool deueueRequest(DataRequest& request);
    private:
        std::string d_filepath;
        //std::deque<DataRequest> d_requestQueue;
        //std::mutex d_queueLock;
        //int d_queueDepth = QUEUE_DEPTH;
};
