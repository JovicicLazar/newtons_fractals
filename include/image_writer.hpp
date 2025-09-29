#ifndef IMAGE_WRITER_HPP
#define IMAGE_WRITER_HPP

#include <vector>
#include <cstdint>
#include <string>

class ImageWriter {
    public:
        static void saveBMP(const std::string& filename, const std::vector<uint8_t>& image, int width, int height);
};


#endif // IMAGE_WRITER_HPP