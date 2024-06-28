#pragma once

#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include "request.hpp"

class RequestDispatcher
{
private:
    ConfigEnv *_config;
    std::priority_queue<Request, std::vector<Request>, std::greater<Request>> _requests;

public:
    inline RequestDispatcher(ConfigEnv *config) 
    {
        _config = config;
    }

    std::vector<Request> get_requests_at_time(const size_t time_point);

    inline void add_request(const size_t location, const size_t request_time_point)
    {
        Request new_request(location, request_time_point);
        
        _requests.push(new_request);
    }
};

#endif