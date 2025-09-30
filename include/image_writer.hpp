#ifndef IMAGE_WRITER_HPP
#define IMAGE_WRITER_HPP

#include <vector>
#include <cstdint>
#include <string>
#include "types.hpp"

class ImageWriter {
    public:
        static void saveBMP(const Image& image);
};


#endif // IMAGE_WRITER_HPP