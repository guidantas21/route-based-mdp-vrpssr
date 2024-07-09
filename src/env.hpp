#pragma once

#ifndef ENV_HPP
#define ENV_HPP

#include <iostream>
#include <vector>

#include "vehicle.hpp"
#include "dispatcher.hpp"
#include "request.hpp"
#include "config.hpp"

enum Status
{
    NOT_REQUESTED,
    UNSERVICED,
    SERVICED
};

class VRPSSR_env
{
private:

    ///// enviroment configurations

    ConfigEnv *_config;

    ///// system state information

    std::vector<Status> _location_status;

    size_t _decision_point;
    size_t _time;
    size_t _reward;

    Vehicle _vehicle;
    
public:

    VRPSSR_env(ConfigEnv *config);

    // getters

    inline Vehicle get_vehicle() const
    {
        return _vehicle; 
    }

    inline size_t get_reward() const
    {
        return _reward;
    }

    inline size_t get_decision_point() const
    { 
        return _decision_point; 
    }

    inline size_t get_time() const
    { 
        return _time; 
    }

    inline std::vector<Status> get_location_status() const
    {
        return _location_status;
    }

    // methods

    void init();

    void update(std::vector<Request> &revealed_requests);

    void step(std::vector<size_t> &route);
    


    inline bool is_done() const
    {
        return _time >= _config->get_time_horizon_max();
    }
};

#endif