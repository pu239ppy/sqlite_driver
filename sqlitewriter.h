#pragma once

#include <string>

class SQLiteWriter
{
    public:
        SQLiteWriter(std::string &&filepath);
        void operator()() const;
    private:
        std::string d_filepath;

};
