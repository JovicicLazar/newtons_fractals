#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <cstdint>

class Renderer
{
public:
    static void renderFractal(const int width, const int height, const int degree, const int maxIter,
                              const double xmin, const double xmax, const double ymin, const double ymax,
                              std::vector<uint8_t> &image);
};

#endif // RENDERER_HPP