#ifndef WFC_CORE_H
#define WFC_CORE_H
//this interface is responsible for the actual procedural generation

#include "bitmap.h"
#include "Preprocessor.h"

namespace wfc_core {
	//constant overlapped areas for two tiles, used for compatibility checks
	//sequence is center to peripheral
	typedef std::pair<int, int> overlap;
	const overlap left_overlap[6] = {
		{0,1}, {1,2}, {3,4}, {4,5}, {6,7}, {7,8}
	};
	const overlap right_overlap[6] = {
		{1,0}, {2,1}, {4,3}, {5,4}, {7,6}, {8,7}
	};
	const overlap up_overlap[6] = {
		{0,3}, {1,4}, {2,5}, {3,6}, {4,7}, {5,8}
	};
	const overlap down_overlap[6] = {
		{3,0}, {4,1}, {5,2}, {6,3}, {7,4}, {8,5}
	};

	//function to rotate a tile, clockwise by 90 degrees
	void rotate(preprocessor::tile& o, preprocessor::tile& t);
	//function to reflect a tile horizontally, direction 0 for horizontal, 1 for vertical
	void reflect(preprocessor::tile& o, preprocessor::tile& t, int direction);

	//compare overlapping areas, return true only if all cells match
	bool is_same_in_overlap(preprocessor::tile& core, preprocessor::tile& peri, const overlap* ol);
	//function to check if a tile is compatible with another, direction given as b to a's
	//note we also check wether they fit in combinations of rotation and reflection
	//we return an integer representing:
	//-1-not fit 0-no transform 1-rotate once 2-rotate twice 3-rotate thrice 4-horizontal reflect 5-vertical reflect
	int is_compatible(preprocessor::tile& core, preprocessor::tile& peri, int direction);

	//core function, takes a bitmap and generates another based on dimensions given
	void generate(bitmap::bitmap& out, bitmap::bitmap& in, int width, int height);
}

#endif
