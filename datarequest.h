#pragma once
#include <string>
#include <functional>


class DataRequest
{
public:
    DataRequest() = default;
    DataRequest(
        std::string sqlLquery,
        std::string requestIdentifier,
        std::function<void(std::string)> callback)
        : d_sqlLquery(std::move(sqlLquery)),
        d_requestIdentifier(std::move(requestIdentifier)),
        d_callback(std::move(callback))
    {};
    DataRequest(const DataRequest& othr)
    : d_sqlLquery(othr.d_sqlLquery),
      d_requestIdentifier(othr.d_requestIdentifier),
      d_callback(othr.d_callback)
    {}
    
    DataRequest& operator=(const DataRequest& othr)
    {
        if (this != &othr)
        {
            d_sqlLquery = othr.d_sqlLquery;
            d_requestIdentifier = othr.d_requestIdentifier;
            d_callback = othr.d_callback;
        }
        return *this;
    }
    DataRequest(DataRequest&& other):
    d_sqlLquery(std::move(other.d_sqlLquery)),
    d_requestIdentifier(std::move(other.d_requestIdentifier))
    {}
    DataRequest& operator=(DataRequest&& other)
    {
        if (this != &other)
        {
            d_sqlLquery = std::move(other.d_sqlLquery);
            d_requestIdentifier = std::move(other.d_requestIdentifier);
            d_callback = std::move(other.d_callback);
        }
        return *this;
    }
    void executeCallBack(std::string response)
    {
        if (d_callback)
        {
            d_callback(response);
        }
    }

    ~DataRequest() = default;

    private:
        std::string d_sqlLquery;
        std::string d_requestIdentifier;
        std::function<void(std::string)> d_callback;
};