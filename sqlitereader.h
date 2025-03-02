#include <string>

class SQLiteReader
{
    public:
        SQLiteReader(std::string &&filepath);
        void operator()() const;
    private:
        std::string d_filepath;
};
