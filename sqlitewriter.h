#pragma once

#include <string>

class SQLiteWriter
{
    public:
        SQLiteWriter(const std::string& filepath);
        void operator()() const;
    private:
        std::string d_filepath;

};
