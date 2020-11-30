#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "bitmap.h"

namespace preprocessor {
	//define tiles, size as 3x3
	struct tile {
		int index;
		bool map[9];
	};

	//function to rotate a tile, clockwise by 90 degrees
	void rotate(tile& o, tile& t);
	//function to reflect a tile horizontally
	void reflect(tile& o, tile& t);
	//function to compare if a tile is equal to another
	bool is_equal(tile& a, tile& b);

	//function to retrieve a list of tiles from a bitmap
	void retrieve_tiles(std::vector<tile>& tiles, bitmap::bitmap bm);
}

#endif