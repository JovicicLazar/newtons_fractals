#include "../include/image_writer.hpp"
#include <fstream>
#include <iostream>

void ImageWriter::saveBMP(const std::string &filename, const std::vector<uint8_t> &image, int width, int height)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open " << filename << " for writing.\n";
        return;
    }

    int rowSize = (3 * width + 3) & (~3);
    int dataSize = rowSize * height;
    int fileSize = 54 + dataSize;

    // BMP Header
    uint8_t header[54] = {
        'B', 'M',
        0, 0, 0, 0,
        0, 0, 0, 0,
        54, 0, 0, 0,
        40, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 0,
        24, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0};

    // File size
    header[2] = fileSize;
    header[3] = fileSize >> 8;
    header[4] = fileSize >> 16;
    header[5] = fileSize >> 24;

    // Width
    header[18] = width;
    header[19] = width >> 8;
    header[20] = width >> 16;
    header[21] = width >> 24;

    // Height
    header[22] = height;
    header[23] = height >> 8;
    header[24] = height >> 16;
    header[25] = height >> 24;

    file.write(reinterpret_cast<char *>(header), 54);

    std::vector<uint8_t> padding(rowSize - width * 3, 0);

    for (int y = height - 1; y >= 0; --y)
    {
        file.write(reinterpret_cast<const char *>(&image[y * width * 3]), width * 3);
        file.write(reinterpret_cast<const char *>(padding.data()), padding.size());
    }

    file.close();
}