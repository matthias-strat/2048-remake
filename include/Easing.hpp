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
            return c * ((t = t/d - T(1)) * t * ((s + T(1)) * t + s) + T(1)) + b;
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

    template <typename T>
    struct Bounce
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            return c - out(d - t, T(0), c, d) + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if ((t /= d) < (T(1) / T(2.75)))
                return c*(T(7.5625) * t * t) + b;
            if (t < (T(2) / T(2.75)))
            {
                T postFix(t -= (T(1.5) / T(2.75)));
                return c * (T(7.5625) * postFix * t + T(0.75)) + b;
            }
            if (t < (T(2.5) / T(2.75)))
            {
                T postFix(t -= (T(2.25) / T(2.75)));
                return c * (T(7.5625) * postFix * t + T(0.9375)) + b;
            }

            T postFix(t -= (T(2.625) / T(2.75)));
            return c * (T(7.5625) * postFix * t + T(0.984375)) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            if (t < d / T(2))
                return in(t * T(2), T(0), c, d) * T(0.5) + b;
            return out(t * T(2) - d, T(0), c, d) * T(0.5) + c * T(0.5) + b;
        }
    };

    template <typename T>
    struct Circ
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return -c * (std::sqrt(T(1) - (t /= d) * t) - T(1)) + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * std::sqrt(T(1) - (t = t/d - T(1)) * t) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if ((t /= d / T(2)) < T(1))
                return -c / T(2) * (std::sqrt(T(1) - t * t) - T(1)) + b;
            return c / T(2) * (std::sqrt(T(1) - t * (t -= T(2))) + T(1)) + b;
        }
    };

    template <typename T>
    struct Elastic
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if (t == T(0)) return b;
            if ((t /= d) == T(1)) return b + c;

            T p(d * T(0.3)), a(c), s(p/T(4));
            T postFix(a * std::pow(T(2), T(10) * (t -= T(1))));
            assert(p != 0);

            return -(postFix * std::sin((t * d - s) * (T(2) * PI) / p)) + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if (t == T(0)) return b;
            if ((t /= d) == T(1)) return b + c;

            T p(d * T(0.3)), a(c), s(p/T(4));
            assert(p != 0);

            return (a * std::pow(T(2), T(-10) * t) * std::sin((t * d - s) * (T(2) * PI) / p) + c + b);
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if (t == T(0)) return b;
            if ((t /= d / 2) == T(2)) return b + c;

            T p(d * T(0.3 * 1.5)), a(c), s(p/T(4));
            assert(p != 0);

            if (t < T(1))
            {
                T postFix(a * std::pow(T(2), T(10) * (t -= T(1))));
                return -T(0.5) * (postFix * std::sin((t * d - s) * (T(2) * PI) / p)) + b;
            }

            T postFix(a * std::pow(T(2), T(-10) * (t -= T(1))));
            return postFix * std::sin((t * d - s) * (T(2) * PI) / p) * T(0.5) + c + b;
        }
    };

    template <typename T>
    struct Expo
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return (t == T(0)) ? b : c * std::pow(T(2), T(10)*(t/d-T(1))) + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return (t == d) ? b + c : c * (-std::pow(T(2), T(-10) * t/d) + T(1)) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if (t == T(0)) return b;
            if (t == d) return b + c;
            if ((t /= d / T(2)) < T(1))
                return c / T(2) * std::pow(T(2), T(10) * (t - T(1))) + b;
            return c/T(2) * (-std::pow(T(2), T(-10) * --t) + T(2)) + b;
        }
    };

    template <typename T>
    struct Quad
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * (t /= d) * t + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return -c * (t /= d) * (t - T(2)) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if ((t /= d / T(2)) < T(1))
                return ((c / T(2)) * t * t) + b;
            return -c / T(2) * ((--t) * (t - T(2)) - T(1)) + b;
        }
    };

    template <typename T>
    struct Quart
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * (t /= d) * t * t * t + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            t = t / d - T(1);
            return -c * (t * t  * t * t - T(1)) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if ((t /= d / T(2)) < T(1))
                return c / T(2) * t * t * t * t + b;
            return -c / T(2) * ((t -= T(2)) * t * t * t - T(2)) + b;
        }
    };

    template <typename T>
    struct Quint
    {
        inline static T in(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * (t /= d) * t * t * t * t + b;
        }

        inline static T out(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            return c * ((t = t / d - T(1)) * t * t * t * t + T(1)) + b;
        }

        inline static T inOut(T t, T b, T c, T d) noexcept
        {
            assert(d != 0);
            if ((t /= d / T(2)) < T(1))
                return c / T(2) * t * t * t * t * t + b;
            return c / T(2) * ((t -= T(2)) * t * t * t * t + T(2)) + b;
        }
    };
}