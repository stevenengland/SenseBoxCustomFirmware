#pragma once

namespace Sketch
{
    class ISketchCoupling
    {
    public:
        virtual ~ISketchCoupling() = default;

        virtual void Setup() = 0;
        virtual void Loop() = 0;
    };
}
