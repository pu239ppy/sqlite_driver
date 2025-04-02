#include "sqlitedriver.h"
#include <iostream>

std::deque<DataRequest> requestQueue;
std::mutex queueLock;

bool enqueueRequest(DataRequest& request)
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

bool dequeueRequest(DataRequest& request)
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
