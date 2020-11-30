#include "Preprocessor.h"

//the utility functions are implemented for constant time ops
void preprocessor::rotate(tile& o, tile& t) {
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
void preprocessor::reflect(tile& o, tile& t) {
	o.index = t.index;
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

bool preprocessor::is_equal(tile& a, tile& b) {
	return a.map[0] == b.map[0] &&
		a.map[1] == b.map[1]
		&& a.map[2] == b.map[2]
		&& a.map[3] == b.map[3]
		&& a.map[4] == b.map[4]
		&& a.map[5] == b.map[5]
		&& a.map[6] == b.map[6]
		&& a.map[7] == b.map[7]
		&& a.map[8] == b.map[8];
}

void preprocessor::retrieve_tiles(std::vector<tile>& tiles, bitmap::bitmap bm) {
	int height = bm.size();
	int width = bm[0].size();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//retrieve the new tile
			tile new_tile;
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					new_tile.map[x * 3 + y] = bm[i + x][j + y];
				}
			}
			//compare it with the list, if not repeated add to it.
			bool repeat = false;
			for (tile t : tiles) {
				if (is_equal(new_tile, t)) repeat = true;
			}
			if (!repeat) {
				new_tile.index = tiles.size();
				tiles.push_back(new_tile);
			}
		}
	}
}
