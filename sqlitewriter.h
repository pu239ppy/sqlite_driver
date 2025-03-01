#ifndef INCLUDE_SQLWRITER_H
#define INCLUDE_SQLWRITER_H

#include <string>

class SQLIteWriter
{
    public:
        SQLIteWriter(std::string &&filepath);
        void operator()() const;
    private:
        std::string d_filepath;

};



#endif // INCLUDE_SQLWRITER_H
