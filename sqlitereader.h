#pragma once
#include <string>

class SQLiteReader
{
    public:
        SQLiteReader(const std::string& filepath);
        void operator()();
    private:
        std::string d_filepath;
};
