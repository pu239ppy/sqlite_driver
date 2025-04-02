#pragma once
#include <type_traits>


class ConnectionHandler
{
public:
    /*ConnectionHandler(SQLiteReader& reader)
    : d_reader(reader)
    {
    }*/
    ConnectionHandler() = default;
    void operator()();

    /*private:
        SQLiteReader& d_reader;*/
};

