#pragma once

#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
#include <vector>

#include "config.hpp"

class Vehicle
{
private:
    ConfigEnv *_config;

    size_t _location;
    size_t _arrival_time;
    std::vector<size_t> _route;

public:
    inline Vehicle(ConfigEnv *config)
    {
        _config = config;
    }
    
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

    inline size_t get_route_size() const
    {
        return _route.size();
    }

    // methods

    inline void init()
    {
        _location = 0;
        _arrival_time = 0;
        _route = { 0 };
    }

    inline void update()
    {
        _arrival_time += _config->get_travel_time(_location, _route.front());

        _location = _route.front();

        #ifdef DEBUG
        std::cout << "(DEBUG) vehicle location: " << _location << std::endl;
        std::cout << "(DEBUG) vehicle arrival time: " << _arrival_time << std::endl;
        #endif
    }
};

#endif