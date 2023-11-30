#include <iostream>
#include <png.h>
// #include <assert.h>
// #include <stdio.h>
#include <cmath>

#include "PngImage.hpp"

img::PNG_PIXEL_RGBA_16_ROWS
horizontal_flip(img::PNG_PIXEL_RGBA_16_ROWS & image_data) {
    unsigned int height = image_data.size();
    unsigned int width  = image_data[0].size();

    img::PNG_PIXEL_RGBA_16_ROWS flipped_image;
    flipped_image.reserve(height);

    for(unsigned int i = 0; i < height; i++) {
        img::PNG_PIXEL_RGBA_16_ROW row;
        row.reserve(width);
        for(unsigned int j = 0; j < width; j++) {
            row.push_back(image_data[i][width - j - 1]);
        }
        flipped_image.push_back(row);
    }
    return flipped_image;
}


int main() {
  img::PNG png("./images/test.png");
  auto rows = png.asRGBA16();
  std::cout << "Uncompressed Image Size (Mbytes): " << png.size() / std::pow(1024, 2) << std::endl;
  auto flipped_rows = horizontal_flip(rows);
  png.fromRGBA16(flipped_rows);
  png.saveToFile("./images/test-flipped.png");
}