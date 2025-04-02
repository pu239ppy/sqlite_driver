#pragma once

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

