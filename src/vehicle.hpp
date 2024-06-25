#pragma once

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
#include <vector>

#include "config.hpp"

class Vehicle
{
private:
    ConfigEnv &_config;

    size_t _location = 0;
    size_t _arrival_time = 0;
    std::vector<size_t> _route = { 0 };

public:
    inline Vehicle(ConfigEnv &config) : _config(config) {}
    
    // setters

    inline void set_route(const std::vector<size_t> &route)
    {
        _route = route;
    }

    // getters

    inline size_t get_location() const
    {
        return _location;
    }

    inline size_t get_arrival_time() const
    {
        return _arrival_time;
    }

    // methods

    inline void update()
    {
        _arrival_time += _config.get_distance(_location, _route[0]);

        _location = _route[0];
    }

    inline void init()
    {
        _location = 0;
        _arrival_time = 0;
        _route = { 0 };
    }
};

#endif