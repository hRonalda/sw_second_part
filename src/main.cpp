#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <filesystem>
#include <algorithm>
#include "image_processing.cpp"


namespace fs = std::filesystem;


GrayscaleMethod stringToGrayscaleMethod(const std::string& method) {
    if (method == "Lightness") return GrayscaleMethod::Lightness;
    if (method == "Average") return GrayscaleMethod::Average;
    if (method == "Luminosity") return GrayscaleMethod::Luminosity;
    if (method == "RootMeanSquare") return GrayscaleMethod::RootMeanSquare;
    if (method == "RedChannel") return GrayscaleMethod::RedChannel;
    if (method == "GreenChannel") return GrayscaleMethod::GreenChannel;
    if (method == "BlueChannel") return GrayscaleMethod::BlueChannel;
    return GrayscaleMethod::Invalid;
}


bool readPPM(const std::string& filename, std::vector<std::vector<std::array<int, 3>>>& image, int& rows, int& cols) {
    std::ifstream in(filename);
    if (!in) return false;

    std::string magic;
    in >> magic;
    if (magic != "P3") return false;

    int maxVal;
    in >> cols >> rows >> maxVal;
    image.resize(rows, std::vector<std::array<int, 3>>(cols));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            in >> image[i][j][0] >> image[i][j][1] >> image[i][j][2];

    return true;
}


bool writePGM(const std::string& filename, const std::vector<std::vector<int>>& grayscaleImage) {
    std::ofstream out(filename);
    if (!out) return false;

    int rows = grayscaleImage.size();
    int cols = grayscaleImage[0].size();

    out << "P2\n" << cols << " " << rows << "\n255\n";
    for (const auto& row : grayscaleImage) {
        for (int val : row)
            out << val << " ";
        out << "\n";
    }
    return true;
}


int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: ./convert_grayscale <input_folder> <output_folder> <grayscale_method>\n";
        return 1;
    }

    std::string inputFolder = argv[1];
    std::string outputFolder = argv[2];
    std::string methodString = argv[3];

    GrayscaleMethod method = stringToGrayscaleMethod(methodString);
    if (method == GrayscaleMethod::Invalid) {
        std::cerr << "Invalid grayscale method: " << methodString << "\n";
        std::cerr << "Valid methods are: Lightness, Average, Luminosity, Desaturation, RedChannel, GreenChannel, BlueChannel\n";
        return 1;
    }

    fs::create_directories(outputFolder);

    for (const auto& entry : fs::directory_iterator(inputFolder)) {
        if (entry.path().extension() == ".ppm") {
            std::vector<std::vector<std::array<int, 3>>> colorImage;
            std::vector<std::vector<int>> grayscaleImage;
            int rows = 0, cols = 0;

            std::string inputPath = entry.path().string();
            if (!readPPM(inputPath, colorImage, rows, cols)) {
                std::cerr << "Failed to read " << inputPath << "\n";
                continue;
            }

            convertToGrayscale(colorImage, rows, cols, method, grayscaleImage);

            std::string outputPath = fs::path(outputFolder) / entry.path().stem();
            outputPath += ".pgm";
            if (!writePGM(outputPath, grayscaleImage)) {
                std::cerr << "Failed to write " << outputPath << "\n";
            } else {
                std::cout << "Converted: " << inputPath << " -> " << outputPath << "\n";
            }
        }
    }

    return 0;
}
