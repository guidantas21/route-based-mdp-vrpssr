#include <iostream>
#include <vector>

#include "env.hpp"
#include "request.hpp"
#include "dispatcher.hpp"
#include "config.hpp"
#include "greedy_policy.hpp"

int main()
{
    size_t TIME_HORIZON_SIZE = 18;
    size_t NUM_LOCATIONS = 5;
    std::vector<std::vector<unsigned int>> travel_time_matrix = {
        {0,1,4,3,2},
        {1,0,3,4,1},
        {4,3,0,7,2},
        {3,4,7,0,5},
        {2,1,2,5,0}
    };

    ConfigEnv config(TIME_HORIZON_SIZE, NUM_LOCATIONS, travel_time_matrix);


    RequestDispatcher dispatcher(&config);

    dispatcher.add_request(2, 0);
    dispatcher.add_request(1, 2);
    dispatcher.add_request(3, 15);
    dispatcher.add_request(4, 12);


    VRPSSR_env env(&config);

    env.init();

    std::vector<Request> revealed_requests; 
    std::vector<size_t> route;

    while (env.is_done() == false)
    {
        #ifdef DEBUG
        std::cout << std::endl;
        std::cout << "(DEBUG) DECISION EPOCH: " << env.get_decision_point() << std::endl;
        std::cout << std::endl;
        #endif

        revealed_requests = dispatcher.get_requests_at_time(env.get_time());
        env.update(revealed_requests);

        route = greedy_policy(
            env.get_time(),
            env.get_vehicle().get_location(),
            env.get_location_status(),
            config
        );

        env.step(route);
    }
    

    return 0;
}