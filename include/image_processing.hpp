#pragma once
#include <vector>
#include <array>

enum class GrayscaleMethod {
    Lightness,
    Average,
    Luminosity,
    RootMeanSquare,
    RedChannel,
    GreenChannel,
    BlueChannel,
    Invalid
};

void convertToGrayscale(const std::vector<std::vector<std::array<int, 3>>>& rgbImage,
                        int rows, int cols,
                        GrayscaleMethod method, std::vector<std::vector<int>>& grayscaleImage);
