#pragma once
#include <atomic>
#include <string>
#include <sqlite3.h>
#include <deque>
#include <mutex>
#include "datarequest.h"

extern std::atomic<bool> ok_to_write;
extern std::atomic<bool> ok_to_read;
extern std::atomic<bool> ok_to_handle_reads;

extern std::deque<DataRequest> requestQueue;
extern std::mutex queueLock;
const int QUEUE_DEPTH = 1000;

extern bool opendb(std::string path, sqlite3 **db, int flags);
bool dequeueRequest(DataRequest& request);
bool enqueueRequest(DataRequest& request);