#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

constexpr int WIDTH = 3000;
constexpr int HEIGHT = 3000;
constexpr int MAX_ITER = 50;
constexpr double XMIN = -2.0, XMAX = 2.0;
constexpr double YMIN = -2.0, YMAX = 2.0;

struct Config
{
    int degree = 3;
    int width = WIDTH;
    int height = HEIGHT;
    int maxIter = MAX_ITER;
    double xmin = XMIN;
    double xmax = XMAX;
    double ymin = YMIN;
    double ymax = YMAX;
};

struct Image
{
    std::string file_name;
    int width;
    int height;
    std::vector<uint8_t> image_data;
};

#endif // TYPES_HPP