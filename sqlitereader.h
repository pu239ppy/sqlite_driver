#ifndef INCLIDE_SQLITEREADER_H
#define INCLIDE_SQLITEREADER_H

#include <string>

class SQLiteReader
{
    public:
        SQLiteReader(std::string &&filepath);
        void operator()() const;
    private:
        std::string d_filepath;
};

#endif
