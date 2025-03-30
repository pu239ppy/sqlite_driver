#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sqlite3.h>
#include "sqlitewriter.h"
#include <sstream>
#include <string>
#include <unistd.h>
#include "sqlitedriver.h"

SQLiteWriter::SQLiteWriter(const std::string& filepath):
    d_filepath(std::move(filepath))
{}

void SQLiteWriter::operator()() const
{
    sqlite3 *db;
    bool openres = opendb(d_filepath, &db, SQLITE_OPEN_READWRITE);
    if (false == openres)
    {
        std::cerr << "Exiting writer thread" << std::endl;
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
            std::cerr << "Exiting writer thread" << std::endl;
            return;
        }
        sqlite3_close(db);
        sleep(20);
    }
    sqlite3_close(db);
    std::cout << "Exiting writer thread" << std::endl;
    return;
}
