#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sqlite3.h>
#include "sqlitewriter.h"
#include <sstream>
#include <string>
#include <unistd.h>
#include "sqlitedriver.h"

SQLiteWriter::SQLiteWriter(std::string &&filepath):
    d_filepath(std::move(filepath))
{}

void SQLiteWriter::operator()() const
{
    sqlite3 *db;
    int openrc = sqlite3_open_v2(d_filepath.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
    if( openrc )
    {
        std::cerr << "Can't open database: " <<  sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }


    while (true == ok_to_write.load())
    {
        int value = std::rand();
        std::string key = std::to_string(value);
        std::stringstream sqlstream;
        sqlstream << "INSERT INTO DATA (KEY, VALUE) VALUES (" << "'" << key << "'" << ", " << value << ")";
        std::string SQL = sqlstream.str();

        char *errMsg = 0;
        int exec_rc = sqlite3_exec(db, SQL.c_str(), NULL, NULL, &errMsg);
        if (SQLITE_OK != exec_rc)
        {
            std::cerr << "SQL Error " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
            return;
        }
        sleep(20);
    }
    sqlite3_close(db);
    return;
}
