#include "registry/events.hpp"
#include "registry/registry.hpp"

#include <pipewire/pipewire.h>

namespace pipewire
{
    struct registry_listener::impl
    {
        pw_registry_events events;
    };

    registry_listener::~registry_listener() = default;

    registry_listener::registry_listener(pw_registry *registry) : m_impl(std::make_unique<impl>())
    {
        m_impl->events.version = PW_VERSION_REGISTRY_EVENTS;

        m_impl->events.global = [](void *data, std::uint32_t id, std::uint32_t permissions, const char *type,
                                   std::uint32_t version, const spa_dict *props) {
            auto &thiz = *reinterpret_cast<registry_listener *>(data);
            thiz.m_events.at<registry_event::global>().fire(global{id, version, permissions, props, type});
        };

        m_impl->events.global_remove = [](void *data, std::uint32_t id) {
            auto &thiz = *reinterpret_cast<registry_listener *>(data);
            thiz.m_events.at<registry_event::global_removed>().fire(id);
        };

        // NOLINTNEXTLINE(*-optional-access)
        pw_registry_add_listener(registry, listener::get(), &m_impl->events, this);
    }

    registry_listener::registry_listener(registry_listener &&registry_listener) noexcept
        : listener(std::move(registry_listener)), m_impl(std::move(registry_listener.m_impl))
    {
    }
} // namespace pipewire