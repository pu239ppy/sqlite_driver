#pragma once
#include <sqlitereader.h>


class ConnectionHandler
{
public:
    ConnectionHandler(SQLiteReader& reader)
    : d_reader(reader)
    {
    }
    void operator()();

    private:
        SQLiteReader& d_reader;
};

