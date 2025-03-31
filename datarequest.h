#pragma once
#include <string>


class DataRequest
{
public:
    DataRequest() = default;
    DataRequest(const DataRequest& othr)
    : sqlLquery(othr.sqlLquery),
      requestIdentifier(othr.requestIdentifier)
    {}
    
    DataRequest& operator=(const DataRequest& othr)
    {
        if (this != &othr)
        {
            sqlLquery = othr.sqlLquery;
            requestIdentifier = othr.requestIdentifier;
        }
        return *this;
    }
    DataRequest(DataRequest&& other):
    sqlLquery(std::move(other.sqlLquery)),
    requestIdentifier(std::move(other.requestIdentifier))
    {}
    DataRequest& operator=(DataRequest&& other)
    {
        if (this != &other)
        {
            sqlLquery = std::move(other.sqlLquery);
            requestIdentifier = std::move(other.requestIdentifier);
        }
        return *this;
    }

    ~DataRequest() = default;

    private:
        std::string sqlLquery;
        std::string requestIdentifier;
};