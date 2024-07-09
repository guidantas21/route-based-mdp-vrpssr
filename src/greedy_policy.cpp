#include "greedy_policy.hpp"

std::vector<size_t> greedy_policy(
    const size_t time,
    const size_t location,
    const std::vector<Status> &location_status,
    const ConfigEnv &config)
{
    std::vector<size_t> route;
    size_t route_time = time;

    unsigned int travel_time = 0;

    for (size_t i = 0; i < location_status.size() - 1; ++i)
    {
        if (location_status[i] == Status::UNSERVICED)
        {
            if (route.empty())
            {
                travel_time += config.get_travel_time(location, i);
            }
            else
            {
                travel_time += config.get_travel_time(route.back(), i);
            }

            if ((route_time + travel_time 
                + config.get_travel_time(i,0)) <= config.get_time_horizon_max())
            {
                route.push_back(i);
                route_time += travel_time;
            }
        }
    }
    return route;
}
