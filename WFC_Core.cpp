#include "WFC_Core.h"

//the utility functions are implemented for constant time ops
void wfc_core::rotate(preprocessor::tile& o, preprocessor::tile& t) {
	o.index = t.index;
	o.map[0] = t.map[6];
	o.map[1] = t.map[3];
	o.map[2] = t.map[0];
	o.map[3] = t.map[7];
	o.map[4] = t.map[4];
	o.map[5] = t.map[1];
	o.map[6] = t.map[8];
	o.map[7] = t.map[5];
	o.map[8] = t.map[2];
}

//the utility functions are implemented for constant time ops
void wfc_core::reflect(preprocessor::tile& o, preprocessor::tile& t, int direction) {
	o.index = t.index;
	if (direction == 0) { //horizontal
		o.map[0] = t.map[6];
		o.map[1] = t.map[7];
		o.map[2] = t.map[8];
		o.map[3] = t.map[3];
		o.map[4] = t.map[4];
		o.map[5] = t.map[5];
		o.map[6] = t.map[0];
		o.map[7] = t.map[1];
		o.map[8] = t.map[2];
	}
	else { //vertical
		o.map[0] = t.map[2];
		o.map[1] = t.map[1];
		o.map[2] = t.map[0];
		o.map[3] = t.map[5];
		o.map[4] = t.map[4];
		o.map[5] = t.map[3];
		o.map[6] = t.map[8];
		o.map[7] = t.map[7];
		o.map[8] = t.map[6];
	}
}

bool wfc_core::is_same_in_overlap(preprocessor::tile& core, preprocessor::tile& peri, const overlap* ol) {
	for (int i = 0; i < 6; i++) {
		if (core.map[ol[i].first] != peri.map[ol[i].second]) return false;
	}
	return true;
}

//this implementation could be made constant time by caching the comparisons
int wfc_core::is_compatible(preprocessor::tile& core, preprocessor::tile& peri, int direction) {
	int result = -1;
	//determine overlap matrix
	overlap ol[6];
	if (direction == 0) std::copy(std::begin(up_overlap), std::end(up_overlap), std::begin(ol));
	else if (direction == 1) std::copy(std::begin(right_overlap), std::end(right_overlap), std::begin(ol));
	else if (direction == 2) std::copy(std::begin(down_overlap), std::end(down_overlap), std::begin(ol));
	else if (direction == 3) std::copy(std::begin(left_overlap), std::end(left_overlap), std::begin(ol));

	//compare orignals
	if (is_same_in_overlap(core, peri, ol)) return 0;

	//compare with different transforms
	//rotate
	for (int i = 0; i < 3; i++) {
		preprocessor::tile rotated_t;
		rotate(rotated_t, core);
		if (is_same_in_overlap(rotated_t, peri, ol)) return i + 1;
	}
	//reflect
	preprocessor::tile reflected_t;
	//horizontal
	reflect(reflected_t, core, 0);
	if (is_same_in_overlap(reflected_t, peri, ol)) return 4;
	//vertical
	reflect(reflected_t, core, 1);
	if (is_same_in_overlap(reflected_t, peri, ol)) return 5;

	return result;
}

void wfc_core::generate(bitmap::bitmap& out, bitmap::bitmap& in, int width, int height) {
	//retrieve tiles with adj rules and freq rules
	using namespace preprocessor;
	std::vector<tile> tiles;
	tile_pool pool;
	retrieve_tiles(tiles, pool, in);
	retrieve_adj_rules(tiles, pool);

	//initialize out bitmap
	for (int i = 0; i < height; i++) {
		bitmap::pixel_row new_row(width, 0);
		out.push_back(new_row);
	}

	//generate based on these rules
	//[note]this part is omitted since it's private code
	//the author, Wei Guo, will decide for its further release

}
