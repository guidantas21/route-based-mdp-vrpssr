#pragma once

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <vector>

class ConfigEnv
{
private:
    size_t _time_horizon_max = 0; // {0, 1, ..., _time_horizon_max}
    size_t _time_horizon_length = 0; // |{0, 1, ..., _time_horizon_max}| = _time_horizon_max + 1
    size_t _num_locations = 1; // = |{0, 1, ..., n}| = n+1
    std::vector<std::vector<double>> _travel_time_matrix;
public:

    inline ConfigEnv(
        const size_t time_horizon_length,
        const size_t num_locations,
        const std::vector<std::vector<double>> &travel_time_matrix
    )
    {
        if (_time_horizon_length > 0)
        {
            _time_horizon_length = time_horizon_length;
            _time_horizon_max = _time_horizon_length - 1;

            _num_locations = num_locations;

            if (num_locations == travel_time_matrix.size() 
                && travel_time_matrix.size() == travel_time_matrix[0].size())
            {
                _travel_time_matrix = travel_time_matrix;
            }
        }
    }

    // getters

    inline size_t get_time_horizon_length() const
    {
        return _time_horizon_length;
    }

    inline size_t get_time_horizon_max() const
    {
        return _time_horizon_max;
    }

    inline size_t get_num_locations() const
    {
        return _num_locations;
    }

    inline double get_distance(const unsigned int i, const unsigned int j) const
    {
        return _travel_time_matrix[i][j];
    }
};

#endif