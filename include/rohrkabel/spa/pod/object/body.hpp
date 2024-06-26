#pragma once

#include "../prop.hpp"

#include <memory>
#include <cstdint>

struct spa_type_info;
struct spa_pod_object_body;

namespace pipewire::spa
{
    class pod_object_body
    {
        struct impl;

      public:
        using raw_body = spa_pod_object_body;
        using raw_info = spa_type_info;

      public:
        class iterator;
        class sentinel;

      private:
        std::unique_ptr<impl> m_impl;

      public:
        ~pod_object_body();

      private:
        pod_object_body();

      public:
        pod_object_body(pod_object_body &&) noexcept;
        pod_object_body(const pod_object_body &) noexcept;

      public:
        pod_object_body &operator=(pod_object_body &&) noexcept;
        pod_object_body &operator=(const pod_object_body &) noexcept;

      public:
        [[nodiscard]] bool has(std::uint32_t key) const;
        [[nodiscard]] pod_prop at(std::uint32_t key) const;

      public:
        [[nodiscard]] std::size_t size() const;

      public:
        [[nodiscard]] sentinel end() const;
        [[nodiscard]] iterator begin() const;

      public:
        [[nodiscard]] pod_type type() const;
        [[nodiscard]] std::uint32_t id() const;

      public:
        [[nodiscard]] raw_body *get() const;
        [[nodiscard]] const raw_info *type_info() const;

      public:
        [[nodiscard]] operator raw_body *() const &;
        [[nodiscard]] operator raw_body *() const && = delete;

      public:
        [[nodiscard]] static pod_object_body view(raw_body *body, std::size_t size);
    };
} // namespace pipewire::spa

#include "iterator.hpp"
