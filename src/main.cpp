#include <iostream>
#include <vector>

#include "env.hpp"
#include "request.hpp"
#include "dispatcher.hpp"
#include "config.hpp"

int main()
{
    size_t TIME_HORIZON_SIZE = 100;
    size_t NUM_LOCATIONS = 5;
    std::vector<std::vector<double>> distance_matrix = {
        {0,1,4,3,2},
        {1,0,3,4,1},
        {4,3,0,7,2},
        {3,4,7,0,5},
        {2,1,2,5,0}
    };

    ConfigEnv config(TIME_HORIZON_SIZE, NUM_LOCATIONS, distance_matrix);

    RequestDispatcher dispatcher(config);

    dispatcher.add_request(5, 10);
    dispatcher.add_request(7, 10);

    VRPSSR_env env(config);

    dispatcher.get_requests_at_time(10);

    env.init();

    return 0;
}