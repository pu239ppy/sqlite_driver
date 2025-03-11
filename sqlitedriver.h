#pragma once

#include <atomic>
#include <string>
#include <sqlite3.h>

extern std::atomic<bool> ok_to_write;
extern std::atomic<bool> ok_to_read;

extern bool opendb(std::string path, sqlite3 **db, int flags);