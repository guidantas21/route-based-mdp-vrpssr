#pragma once

#ifndef ENV_HPP
#define ENV_HPP

#include <iostream>
#include <vector>

#include "vehicle.hpp"
#include "dispatcher.hpp"
#include "request.hpp"
#include "config.hpp"

class VRPSSR_env
{
private:

    ///// enviroment configurations

    ConfigEnv &_config;

    ///// system state information

    /*
    status of location
    -1, if location has not requested service
    0, if location has a unserviced request
    1, if location has been serviced
    */
    std::vector<char> _location_status; 

    size_t _decision_point = 0;
    size_t _time = 0;

    Vehicle _vehicle;
    
public:

    VRPSSR_env(ConfigEnv &config);

    // getters

    inline size_t get_decision_point() const
    { 
        return _decision_point; 
    }

    inline size_t get_time() const
    { 
        return _time; 
    }

    // methods

    void init();

    void update(std::vector<Request> &revealed_requests);

    void step(std::vector<size_t> &route);
    

    inline bool is_done() const
    {
        return _time >= _config.get_time_horizon_max();
    }

};

#endif