#include "env.hpp"

VRPSSR_env::VRPSSR_env(ConfigEnv &config) : _config(config), _vehicle(config) 
{
    for (size_t i = 0; i < _config.get_num_locations(); ++i)
    {
        _location_status.push_back(-1);
    }
}

void VRPSSR_env::init()
{
    _decision_point = 0;
    _time = 0;

    for (size_t i = 0; i < _config.get_num_locations(); ++i)
    {
        _location_status[i] = -1;
    }

    _vehicle.init();
}

void VRPSSR_env::update(std::vector<Request> &revealed_requests)
{
    for (size_t i = 0; i < revealed_requests.size(); ++i)
    {
        _location_status[revealed_requests[i].get_location()] = 0;
    }

    _vehicle.update();

    _time = _vehicle.get_arrival_time();
    _location_status[_vehicle.get_location()] = 2;
}

void VRPSSR_env::step(std::vector<size_t> &route)
{
    
}