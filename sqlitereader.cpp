#include "sqlitereader.h"
#include <sqlite3.h>
#include <iostream>
#include <unistd.h>
#include "sqlitedriver.h"

static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    std::cerr << (const char*)data << std::endl;
    for (i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

SQLiteReader::SQLiteReader(std::string &&filepath):
    d_filepath(std::move(filepath))
{}

void SQLiteReader::operator()() const
{
    sqlite3 *db;
    int openrc = sqlite3_open_v2(d_filepath.c_str(), &db, SQLITE_OPEN_READONLY, NULL);
    if( openrc )
    {
        std::cerr << "Can't open database: " <<  sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    while (true == ok_to_read.load())
    {
        std::string SQL = "SELECT * FROM DATA LIMIT 10";
        char *errMsg = 0;
        const char* data = "Callback function called";
        int exec_rc = sqlite3_exec(db, SQL.c_str(), &callback, (void*)data, &errMsg);
        if (SQLITE_OK != exec_rc)
        {
            std::cerr << "SQL Error " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
            return;
        }
        sleep(5);
    }
    return;
}
