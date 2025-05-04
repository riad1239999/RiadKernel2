#include "graphics_loader.hpp"
#include <fstream>
#include <iostream>
#include <cstdint>

// Define the VGA screen buffer location
#define VGA_BUFFER (unsigned char*)0xA0000  // VGA Graphics Memory starts here for mode 0x13 (320x200)

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t type;          // 'BM' in little endian (0x4D42)
    uint32_t size;          // File size
    uint16_t reserved1;     // Reserved
    uint16_t reserved2;     // Reserved
    uint32_t offset;        // Offset to pixel data
};

struct DIBHeader {
    uint32_t size;          // DIB header size
    int32_t width;          // Width of the image
    int32_t height;         // Height of the image
    uint16_t planes;        // Color planes
    uint16_t bpp;           // Bits per pixel (24 for true color)
    uint32_t compression;   // Compression type
    uint32_t image_size;    // Image size
    int32_t x_resolution;   // X pixels per meter (not used)
    int32_t y_resolution;   // Y pixels per meter (not used)
    uint32_t colors;        // Number of colors (not used)
    uint32_t important_colors; // Important colors (not used)
};
#pragma pack(pop)

void load_graphics(const char* file_name) {
    // Open the BMP file
    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open image file: " << file_name << std::endl;
        return;
    }

    // Read the BMP header
    BMPHeader bmp_header;
    file.read(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));
    if (bmp_header.type != 0x4D42) {  // Check for 'BM' signature
        std::cerr << "Invalid BMP file format!" << std::endl;
        return;
    }

    // Read the DIB header (bitmap info header)
    DIBHeader dib_header;
    file.read(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));
    
    // Check if we have a 24-bit BMP (True color)
    if (dib_header.bpp != 24) {
        std::cerr << "Only 24-bit BMP images are supported!" << std::endl;
        return;
    }

    // Get the width and height of the image
    int width = dib_header.width;
    int height = dib_header.height;
    
    // Move file pointer to the pixel data offset
    file.seekg(bmp_header.offset, std::ios::beg);

    // Calculate the row padding (if any)
    int row_padded = (width * 3 + 3) & (~3);  // Row size must be a multiple of 4 bytes
    int pixel_data_size = row_padded * height;

    // Allocate memory for pixel data
    uint8_t* pixel_data = new uint8_t[pixel_data_size];

    // Read pixel data
    file.read(reinterpret_cast<char*>(pixel_data), pixel_data_size);

    // Convert the image data to a format usable by the VGA screen
    unsigned char* vga_buffer = (unsigned char*)VGA_BUFFER;
    int x, y;
    int pixel_index = 0;

    // Loop through the pixels (bottom-up as BMP format)
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            // BMP stores pixels bottom-to-top, so we reverse the y-axis
            int reversed_y = height - y - 1;

            // Get the RGB components (BMP stores in BGR format)
            uint8_t blue = pixel_data[pixel_index++];
            uint8_t green = pixel_data[pixel_index++];
            uint8_t red = pixel_data[pixel_index++];

            // Convert to VGA 16-color format (for simplicity, you can improve this later)
            unsigned short color = (red >> 3) << 10 | (green >> 3) << 5 | (blue >> 3);

            // Write the color data to VGA buffer (each pixel is 2 bytes in 320x200 mode)
            vga_buffer[(reversed_y * width + x) * 2] = color & 0xFF;       // Low byte
            vga_buffer[(reversed_y * width + x) * 2 + 1] = (color >> 8);  // High byte
        }
        // Skip padding at the end of each row (if any)
        pixel_index += row_padded - width * 3;
    }

    // Clean up
    delete[] pixel_data;
}
