#pragma once
#include "info.hpp"
#include "global.hpp"
#include "spa/pod/pod.hpp"

#include <map>
#include <memory>
#include <cstdint>

#include "utils/annotations.hpp"
struct pw_device;
namespace pipewire
{
    class registry;
    class device
    {
        struct impl;

      private:
        std::unique_ptr<impl> m_impl;

      public:
        ~device();

      public:
        device(device &&) noexcept;
        device(registry &, const global &);

      public:
        device &operator=(device &&) noexcept;

      public:
        [[needs_sync]] void set_param(std::uint32_t id, const spa::pod &pod);

      public:
        [[nodiscard]] device_info info() const;
        [[nodiscard]] [[needs_sync]] const std::map<std::uint32_t, spa::pod> &params() const;

      public:
        [[nodiscard]] pw_device *get() const;

      public:
        static const std::string type;
        static const std::uint32_t version;
    };
} // namespace pipewire
#include "utils/annotations.hpp"