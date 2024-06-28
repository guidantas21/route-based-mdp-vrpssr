#pragma once

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <queue>
#include <vector>

#include "config.hpp"

class Request
{
private:
    size_t _location;
    size_t _request_time_point;
    
public:
    inline Request(
        const size_t location, 
        const size_t request_time_point
    ) : _location(location), _request_time_point(request_time_point) {}

    // getters

    inline size_t get_location() const { return _location; }

    inline size_t get_request_time_point() const { return _request_time_point; }

    // methods

    inline bool operator>(const Request& other) const {
        return _request_time_point > other._request_time_point;
    }
};

#endif