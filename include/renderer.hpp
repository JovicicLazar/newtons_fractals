#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <cstdint>
#include "types.hpp"

class Renderer
{
public:
    static void renderFractal(Image &image, const int degree, const int maxIter,
                              const double xmin, const double xmax, const double ymin, const double ymax);
};

#endif // RENDERER_HPP