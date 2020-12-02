#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <vector>

//this file defines the bitmap type used for WFC, rows' priority
namespace bitmap {
	typedef bool pixel;
	typedef std::vector<pixel> pixel_row;
	typedef std::vector<pixel_row> bitmap;

	//function to read a bitmap from a stb image, treating all averaged color values above 50% brightness as white/true
	inline void stb_image_to_bitmap(bitmap& result, uint8_t* data, int width, int height, int chans) {
		//populate bitmap with all black first
		for (int i = 0; i < height; i++) {
			pixel_row new_row(width, 0);
			result.push_back(new_row);
		}
		//go through stb data and repopulate if necessary
		int span = 0;
		for (int i = 0; i < width * height * chans; i += chans) {
			uint8_t c = 0;
			for (int j = 0; j < chans; j++) {
				c += data[i + j] / chans;
				c += 0;
			}
			if (c > 128) result[span / width][span % width] = 1;
			span += 1;
		}
	}
}

#endif // !BITMAP_H
