#pragma once

#include <atomic>
#include <string>
#include <sqlite3.h>
#include <deque>

extern std::atomic<bool> ok_to_write;
extern std::atomic<bool> ok_to_read;

extern bool opendb(std::string path, sqlite3 **db, int flags);


class RequestCallbackFunction
{
public:
    RequestCallbackFunction() = default;
    RequestCallbackFunction(const RequestCallbackFunction&) = delete;
    RequestCallbackFunction& operator=(const RequestCallbackFunction&) = delete;
    RequestCallbackFunction(RequestCallbackFunction&&) = default;
    RequestCallbackFunction& operator=(RequestCallbackFunction&&) = default;
    ~RequestCallbackFunction() = default;
    int operator()(void* data);
};

class DataRequest
{
public:
    DataRequest() = default;
    DataRequest(const DataRequest&) = delete;
    DataRequest& operator=(const DataRequest&) = delete;
    DataRequest(DataRequest&&) = default;
    DataRequest& operator=(DataRequest&&) = default;
    ~DataRequest() = default;

    private:
        std::string sqlLquery;
        std::string requestIdentifier;
        RequestCallbackFunction callbackFunction;
};

const int QUEUE_DEPTH = 1000;
extern std::deque<DataRequest> requestQueue;