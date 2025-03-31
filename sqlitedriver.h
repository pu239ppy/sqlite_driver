#pragma once
#include <atomic>
#include <string>
#include <sqlite3.h>
#include "datarequest.h"
#include <deque>


extern std::atomic<bool> ok_to_write;
extern std::atomic<bool> ok_to_read;

extern bool opendb(std::string path, sqlite3 **db, int flags);

const int QUEUE_DEPTH = 1000;
extern std::deque<DataRequest> requestQueue;