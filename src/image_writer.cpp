#include "../include/image_writer.hpp"
#include <fstream>
#include <iostream>

void ImageWriter::saveBMP(const Image &image)
{
    std::string file_name = image.file_name;
    int image_width = image.width;
    int image_height = image.height;
    const auto& image_data = image.image_data;

    std::ofstream file(file_name, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open " << file_name << " for writing.\n";
        return;
    }

    int rowSize = (3 * image_width + 3) & (~3);
    int dataSize = rowSize * image_height;
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
    header[18] = image_width;
    header[19] = image_width >> 8;
    header[20] = image_width >> 16;
    header[21] = image_width >> 24;

    // Height
    header[22] = image_height;
    header[23] = image_height >> 8;
    header[24] = image_height >> 16;
    header[25] = image_height >> 24;

    file.write(reinterpret_cast<char *>(header), 54);

    std::vector<uint8_t> padding(rowSize - image_width * 3, 0);

    for (int y = image_height - 1; y >= 0; --y)
    {
        file.write(reinterpret_cast<const char *>(&image_data[y * image_width * 3]), image_width * 3);
        file.write(reinterpret_cast<const char *>(padding.data()), padding.size());
    }

    file.close();
}