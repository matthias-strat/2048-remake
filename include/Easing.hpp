#pragma once

#include <cassert>
#include <cmath>

constexpr float PI{3.14159265358979f};

// C++ version of Robert Penner's easing equations 
namespace easing
{
    template <typename T>
    struct In
    {
        inline static auto get() noexcept
        {
            return &T::in;
        }
    };

    template <typename T>
    struct Out
    {
        inline static auto get() noexcept
        {
            return &T::out;
        }
    };

    template <typename T>
    struct InOut
    {
        inline static auto get() noexcept
        {
            return &T::inOut;
        }
    };

    namespace Impl
    {
        template <typename T>
        struct Dispatcher
        {
            template <template <typename> class TEase, template <typename> class TKind>
            inline static T getMap(const T& i, const T& iMin, const T& iMax, const T& oMin, const T& oMax)
            {
                return TKind<TEase<T>>::get()(iMin + i, oMin, oMax - oMin, iMax - iMin);
            }
        };
    }

    template <typename T>
    struct Linear
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * t / d + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            return in(t, b, c, d);
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            return in(t, b, c, d);
        }
    };

    template <typename T>
    struct Sine
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return -c * std::cos(t/d*(PI/T(2))) + c + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * std::sin(t/d*(PI/T(2))) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return -c / T(2)*(std::cos(PI * t / d) - T(1)) + b;
        }
    };

    template <typename T>
    struct Back
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            T postFix(t /= d), s(1.70158);
            return c*(postFix)*t*((s + T(1)) * t - s) + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            T s(1.70158);
            return c * ((t = t / d - T(1))*t*((s + T(1)) * t + s) + T(1)) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            T s(1.70158);
            if ((t /= d / T(2)) < T(1))
                return c/T(2)*(t*t(((s *= T(1.525)) + T(1)) * t - s)) + b;

            T postFix(t -= 2);
            return c / T(2)*((postFix)*t*(((s *= T(1.525)) + 1) * t + s) + T(2)) + b;
        }
    };

    template <typename T>
    struct Cubic
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * (t /= d)*t*t + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * ((t = t / d - T(1)) * t * t + T(1)) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if ((t /= d / T(2)) < T(1))
                return c/T(2)*t*t*t+b;
            auto p1(c / T(2)*t);
            t -= T(2);
            return p1 * t * t + T(2) + b;
        }
    };
}