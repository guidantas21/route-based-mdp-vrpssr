#include "env.hpp"

VRPSSR_env::VRPSSR_env(ConfigEnv *config) : _vehicle(config) 
{
    _config = config;
    _reward = 0;

    for (size_t i = 0; i < _config->get_num_locations(); ++i)
    {
        _location_status.push_back(Status::NOT_REQUESTED);
    }
}

void VRPSSR_env::init()
{
    _decision_point = 0;
    _time = 0;
    _reward = 0;

    for (size_t i = 0; i < _config->get_num_locations(); ++i)
    {
        _location_status[i] = Status::NOT_REQUESTED;
    }
    _vehicle.init();
}

void VRPSSR_env::update(std::vector<Request> &revealed_requests)
{
    #ifdef DEBUG
    std::cout << "\n(DEBUG) update pre-decision state" << std::endl;
    #endif

    for (size_t i = 0; i < revealed_requests.size(); ++i)
    {
        #ifdef DEBUG
        std::cout << "(DEBUG) new unserved location: " << revealed_requests[i].get_location();
        std::cout << " (travel time: " << _config->get_travel_time(_vehicle.get_location(), revealed_requests[i].get_location()) << ')' << std::endl;
        #endif
        _location_status[revealed_requests[i].get_location()] = Status::UNSERVICED;
    }
}

void VRPSSR_env::step(std::vector<size_t> &route)
{
    #ifdef DEBUG
    std::cout << "\n(DEBUG) update post-decision state" << std::endl;
    #endif

    _vehicle.set_route(route);

    if (route.empty() == false)
    {
        _vehicle.update();

        _time = _vehicle.get_arrival_time();
        _location_status[_vehicle.get_location()] = Status::SERVICED;
        std::cout << "(DEBUG) serviced location: " << _vehicle.get_location() << std::endl;
        _reward += route.size();

        #ifdef DEBUG
        std::cout << "(DEBUG) route: ";
        for (size_t i = 0; i < route.size(); ++i)
        {
            std::cout << route[i] << " ";
        }
        std::cout << std::endl;
        #endif
    }
    else
    {
        #ifdef DEBUG
        std::cout << "(DEBUG) route: empty"<< std::endl;
        #endif
        _time += 1;
    }
    #ifdef DEBUG
    std::cout << "(DEBUG) current time: " << _time << std::endl;
    std::cout << "(DEBUG) total reward: " << _reward << std::endl;
    #endif

    _decision_point += 1;
}