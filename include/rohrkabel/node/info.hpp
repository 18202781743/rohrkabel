#pragma once

#include "../spa/dict.hpp"
#include "../spa/param.hpp"

#include <string>
#include <vector>
#include <cstdint>

struct pw_node_info;

namespace pipewire
{
    enum class node_state : std::int8_t
    {
        error = -1,
        suspended,
        idle,
        running
    };

    struct node_info
    {
        std::uint32_t id;

        struct
        {
            std::uint32_t max;
            std::uint32_t current;
        } input;

        struct
        {
            std::uint32_t max;
            std::uint32_t current;
        } output;

        spa::dict props;
        node_state state;

        std::string error;
        std::uint64_t change_mask;

        std::vector<spa::param_info> params;

      public:
        static node_info from(const pw_node_info *);
    };
} // namespace pipewire
