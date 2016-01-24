#pragma once

#include <functional>
#include <memory>
#include <chrono>

#include <SFML/System/Vector2.hpp>

// std::forward macro
#define FWD(x) std::forward<decltype(x)>(x)

// SFML shortcuts
template <typename T>
using Vec2 = sf::Vector2<T>;
using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;

// STL shortcuts
template <typename T>
using Func = std::function<T>;
template <typename... Ts>
using Common = std::common_type_t<Ts...>;
using HRClock = std::chrono::high_resolution_clock;

// Smart pointers
template <typename T>
using UPtr = std::unique_ptr<T>;
template <typename T>
using SPtr = std::unique_ptr<T>;

template <typename T, typename... TArgs>
inline decltype(auto) mkUPtr(TArgs&&... args)
{
    return std::make_unique<T>(FWD(args)...);
}

template <typename T, typename... TArgs>
inline decltype(auto) mkSPtr(TArgs&&... args)
{
    return std::make_shared<T>(FWD(args)...);
}
