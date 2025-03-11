#pragma once

#include <atomic>

extern std::atomic<bool> ok_to_write;
extern std::atomic<bool> ok_to_read;
