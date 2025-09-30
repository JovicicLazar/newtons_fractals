#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

#include "include/renderer.hpp"
#include "include/image_writer.hpp"
#include "include/types.hpp"

void printUsage(const char *progName)
{
    std::cout << "Usage: " << progName << " [options]\n"
              << "Options:\n"
              << "  -n <degree>      Polynomial degree (default: 3)\n"
              << "  -width <pixels>  Image width (default: 3000)\n"
              << "  -height <pixels> Image height (default: 3000)\n"
              << "  -iter <count>    Max iterations (default: 50)\n"
              << "  -h, --help       Show this help\n";
}

bool parseArgs(int argc, char *argv[], Config &config)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
        {
            config.degree = std::atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-width") == 0 && i + 1 < argc)
        {
            config.width = std::atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-height") == 0 && i + 1 < argc)
        {
            config.height = std::atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-iter") == 0 && i + 1 < argc)
        {
            config.maxIter = std::atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            return false;
        }
        else
        {
            std::cerr << "Unknown option: " << argv[i] << "\n";
            return false;
        }
    }

    if (config.degree <= 0 || config.width <= 0 || config.height <= 0 || config.maxIter <= 0)
    {
        std::cerr << "Error: All values must be greater than 0\n";
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    Config config;

    if (!parseArgs(argc, argv, config))
    {
        printUsage(argv[0]);
        return 1;
    }

    std::string file_name = "newton_fractal_n" + std::to_string(config.degree) + ".bmp";

    Image new_image;
    new_image.file_name = file_name;
    new_image.width = config.width;
    new_image.height = config.height;
    new_image.image_data.resize(config.width * config.height * 3);

    Renderer::renderFractal(new_image, config.degree, config.maxIter,
                            config.xmin, config.xmax, config.ymin, config.ymax);

    ImageWriter::saveBMP(new_image);

    std::cout << "Saved to: " << file_name << std::endl;

    return 0;
}