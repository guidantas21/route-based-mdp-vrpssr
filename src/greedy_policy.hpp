#pragma once

#ifndef GREEDY_POLICY_HPP
#define GREEDY_POLICY_HPP

#include <iostream>
#include <vector>

#include "env.hpp"

std::vector<size_t> greedy_policy(
    const size_t time,
    const size_t location,
    const std::vector<Status> &location_status,
    const ConfigEnv &config
);

#endif