#include <iostream>
#include <vector>
#include <cstdlib>

#include "include/renderer.hpp"
#include "include/image_writer.hpp"
#include "include/types.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <degree n>" << std::endl;
        return 1;
    }

    int degree = std::atoi(argv[1]);

    if(degree <= 0) {
        std::cerr << "Degree must be greater than 0 " << std::endl;
        return 1;
    }
    std::vector<uint8_t> image(WIDTH * HEIGHT * 3);

    Renderer::renderFractal(WIDTH, HEIGHT, degree, MAX_ITER,
                            XMIN, XMAX, YMIN, YMAX, image);

    std::string file_name = "newton_fractal_n" + std::to_string(degree) + "_.bmp";

    ImageWriter::saveBMP(file_name, image, WIDTH, HEIGHT);

    std::cout << "Saved to: " <<  file_name << std::endl;
    
    return 0;
}
