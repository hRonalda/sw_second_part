#include "image_processing.hpp"
#include <gtest/gtest.h>

TEST(GrayscaleTest, RedChannelConversion) {
    std::vector<std::vector<std::array<int, 3>>> image = {{{255, 0, 0}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::RedChannel, result);
    EXPECT_EQ(result[0][0], 255); // Red channel only
}

TEST(GrayscaleTest, LuminosityConversion) {
    std::vector<std::vector<std::array<int, 3>>> image = {{{255, 255, 255}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::Luminosity, result);
    EXPECT_EQ(result[0][0], 255); // White pixel, should remain max gray
}

TEST(GrayscaleTest, AverageConversion) {
    std::vector<std::vector<std::array<int, 3>>> image = {{{30, 90, 150}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::Average, result);
    EXPECT_EQ(result[0][0], (30 + 90 + 150) / 3); // Arithmetic mean
}


//
// =================================== RED CHANNEL TESTS ===================================
// These tests verify that the RedChannel method correctly extracts the red component
// from each RGB pixel and ignores the green and blue values.
//

TEST(GrayscaleTest, RedUsesOnlyRedComponent) {
    /*
     * Test case: RGB = (120, 45, 200)
     * Purpose: Ensures that only the red component (120) is used when converting to grayscale
     * using the RedChannel method. The output should be exactly equal to 120, regardless of
     * the values in the green or blue channels.
     * Failure here indicates that the implementation may be using the wrong channel or
     * averaging components instead of isolating the red value.
     */
    std::vector<std::vector<std::array<int, 3>>> image = {{{120, 45, 200}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::RedChannel, result);
    EXPECT_EQ(result[0][0], 120);
}

//
// ================================== GREEN CHANNEL TESTS ==================================
// Ensures proper isolation of the green channel when using the GreenChannel method.
//

TEST(GrayscaleTest, GreenIsolatedCorrectly) {
    /*
     * Test case: RGB = (10, 220, 5)
     * Purpose: Confirms that the grayscale result equals the green component (220).
     * This is critical to verify that the GreenChannel method is not hardcoded or incorrectly
     * referencing red or blue values.
     * Failures may indicate incorrect channel indexing or use of static values.
     */
    std::vector<std::vector<std::array<int, 3>>> image = {{{10, 220, 5}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::GreenChannel, result);
    EXPECT_EQ(result[0][0], 220);
}

//
// =================================== BLUE CHANNEL TESTS ==================================
// Verifies correct behavior of BlueChannel conversion by isolating blue values.
//

TEST(GrayscaleTest, BlueChannelCorrectness) {
    /*
     * Test case: RGB = (0, 0, 255)
     * Purpose: Validates that the output is 255, which is the blue component.
     * Important for confirming that the blue channel is not being mixed with other channels,
     * or scaled inappropriately.
     * Any deviation from 255 would highlight a misimplementation of blue channel access.
     */
    std::vector<std::vector<std::array<int, 3>>> image = {{{0, 0, 255}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::BlueChannel, result);
    EXPECT_EQ(result[0][0], 255);
}

//
// =============================== AVERAGE METHOD TESTS ====================================
// Tests the arithmetic mean of the RGB values, ensuring overflow and underflow are handled.
//

TEST(GrayscaleTest, AverageOfUniformColor) {
    /*
     * Test case: RGB = (100, 100, 100)
     * Purpose: A sanity check — the grayscale average of equal RGB values should return the same value.
     * A failure here indicates a structural issue with how averaging is computed or weighted.
     */
    std::vector<std::vector<std::array<int, 3>>> image = {{{100, 100, 100}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::Average, result);
    EXPECT_EQ(result[0][0], 100);
}

TEST(GrayscaleTest, AverageHandlesHighValues) {
    /*
     * Test case: RGB = (255, 255, 255)
     * Purpose: Checks that the maximum possible pixel value still results in the correct average.
     * Output should be 255, not a higher number or overflow.
     * Useful for confirming that the function doesn't exceed the 8-bit grayscale limit.
     */
    std::vector<std::vector<std::array<int, 3>>> image = {{{255, 255, 255}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::Average, result);
    EXPECT_EQ(result[0][0], 255);
}

TEST(GrayscaleTest, AverageWithNegativeValues) {
    /*
     * Test case: RGB = (-100, 50, 100)
     * Purpose: This test checks the function’s robustness when faced with invalid negative input.
     * Even if negative values are not expected, the function should not crash or return nonsensical results.
     * Depending on how error handling is implemented, either clamping or raw calculation could occur.
     * Here we expect raw mean = (−100 + 50 + 100) / 3 = 16.
     */
    std::vector<std::vector<std::array<int, 3>>> image = {{{-100, 50, 100}}};
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 1, 1, GrayscaleMethod::Average, result);
    EXPECT_EQ(result[0][0], 16);
}

//
// =============================== MULTI-PIXEL MATRIX TEST =================================
// Verifies that matrix-based images are processed correctly pixel-by-pixel.
//

TEST(GrayscaleTest, MultiPixelAverage) {
    /*
     * Test case: 2x2 matrix with varied RGB values.
     * Purpose: Ensures that the grayscale conversion is applied to each pixel independently
     * and correctly. Checks for logic errors when iterating across rows and columns.
     * Each output value should match the expected per-pixel average.
     */
    std::vector<std::vector<std::array<int, 3>>> image = {
        {{10, 20, 30}, {30, 60, 90}},
        {{90, 90, 90}, {255, 0, 0}}
    };
    std::vector<std::vector<int>> result;
    convertToGrayscale(image, 2, 2, GrayscaleMethod::Average, result);

    EXPECT_EQ(result[0][0], (10 + 20 + 30) / 3);    // 20
    EXPECT_EQ(result[0][1], (30 + 60 + 90) / 3);    // 60
    EXPECT_EQ(result[1][0], 90);                    // Uniform color
    EXPECT_EQ(result[1][1], 85);                    // Red only
}
