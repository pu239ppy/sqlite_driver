#ifndef INCLUDE_SQLWRITER_H
#define INCLUDE_SQLWRITER_H

#include <string>

class SQLiteWriter
{
    public:
        SQLiteWriter(std::string &&filepath);
        void operator()() const;
    private:
        std::string d_filepath;

};



#endif // INCLUDE_SQLWRITER_H
