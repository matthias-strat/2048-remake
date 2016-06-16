#pragma once
#include "Easing.hpp"
#include "Common.hpp"

class Tile;
struct BaseTask
{
    using EaseFunc = Func<float(float, float, float, float)>;
    using CompleteFunc = Func<void()>;
    using UpdateFunc = Func<void(Tile& tile, float)>;

    float time{0.f};
    float start, end, duration;
    EaseFunc easeFunc;
    UpdateFunc updateFunc;
    CompleteFunc onCompleted;
    bool finished{false};

    BaseTask(float start, float end, float duration, EaseFunc easeFunc,
             UpdateFunc updateFunc, CompleteFunc onCompleted)
        : start{start}, end{end}, duration{duration},
          updateFunc{updateFunc},
          easeFunc{easeFunc},
          onCompleted{onCompleted}
    { }

    float operator()(float t)
    {
        time += t;
        auto value(easeFunc(time, start, end - start, duration));
        if (time >= duration)
        {
            finished = true;
            value = end;
        }

        return value;
    }
};

struct MoveTask : public BaseTask
{
    MoveTask(float start, float end, float duration, UpdateFunc updateFunc,
             CompleteFunc onCompleted = nullptr)
        : BaseTask{start, end, duration, easing::Linear<float>::out, updateFunc, onCompleted}
    { }
};

struct PopTask : public BaseTask
{
    PopTask(float start, float end, float duration, UpdateFunc updateFunc,
            CompleteFunc onCompleted = nullptr)
        : BaseTask{start, end, duration, easing::Quart<float>::out, updateFunc, onCompleted}
    { }
};