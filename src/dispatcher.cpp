#include "dispatcher.hpp"

std::vector<Request> RequestDispatcher::get_requests_at_time(const size_t time_point)
{
    std::vector<Request> requests_at_time_point;

    while (_requests.empty() == false 
        && _requests.top().get_request_time_point() <= time_point)
    {
        #ifdef DEBUG
        std::cout << "(DEBUG) request found at time " << time_point << ": " << _requests.top().get_location() << std::endl;
        #endif

        requests_at_time_point.push_back(_requests.top());
        _requests.pop();
    }
    return requests_at_time_point;
}

