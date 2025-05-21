/*
   Copyright 2025 Simone Reale

   Licensed under the Apache License, Version 2.0 (the "License");

   you may not use this file except in compliance with the License.

   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software

   distributed under the License is distributed on an "AS IS" BASIS,

   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

   See the License for the specific language governing permissions and

   limitations under the License.
*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <filesystem>
#include <algorithm>
#include "image_processing.hpp"


void convertToGrayscale(const std::vector<std::vector<std::array<int, 3>>>& rgbImage,
                        int rows, int cols,
                        GrayscaleMethod method, std::vector<std::vector<int>>& grayscaleImage) {
    grayscaleImage.resize(rows, std::vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int R = rgbImage[i][j][0];
            int G = rgbImage[i][j][1];
            int B = rgbImage[i][j][2];
            int gray = 0;
            switch (method) {
                case GrayscaleMethod::Lightness:
                    gray = (std::max({R, G, B}) + std::min({R, G, B})) / 2;
                    break;
                case GrayscaleMethod::Average:
                    gray = (R + G + B) / 3;
                    break;
                case GrayscaleMethod::Luminosity:
                    gray = static_cast<int>(0.21 * R + 0.72 * G + 0.07 * B);
                    break;
                case GrayscaleMethod::RootMeanSquare:
                    gray = static_cast<int>(std::sqrt((R * R + G * G + B * B) / 3.0));
                    break;
                case GrayscaleMethod::RedChannel:
                    gray = R;
                    break;
                case GrayscaleMethod::GreenChannel:
                    gray = G;
                    break;
                case GrayscaleMethod::BlueChannel:
                    gray = B;
                    break;
            }
            grayscaleImage[i][j] = gray;
        }
    }
}


