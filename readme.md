# Grayscale Image Conversion Utility

This project provides a utility to convert `.ppm` images to `.pgm` format using various grayscale conversion methods. The tool processes all `.ppm` images in a specified input folder and saves the converted `.pgm` images in an output folder.

---

## Features

- **Supported Grayscale Methods**:
  - `Lightness`: Average of the brightest and darkest color channels.
  - `Average`: Mean of all three color channels.
  - `Luminosity`: Weighted average emphasizing green, followed by red, and then blue.
  - `Desaturation`: Average of the maximum and minimum color channel values.
  - `RedChannel`: Uses the red channel as the grayscale value.
  - `GreenChannel`: Uses the green channel as the grayscale value.
  - `BlueChannel`: Uses the blue channel as the grayscale value.

- **Batch Processing**:
  - Converts all `.ppm` images in the input folder.
  - Saves the converted `.pgm` images in the output folder.

- **Some Error Handling stuff (already handled for you):**:
  - Validates input arguments.
  - Handles invalid grayscale methods.
  - Skips files that cannot be read or written.

---

## Usage

### Command-Line Syntax

```bash
./convert_grayscale <input_folder> <output_folder> <grayscale_method>