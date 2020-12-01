#include "Preprocessor.h"

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

bool preprocessor::is_equal(adj_rule& a, adj_rule& b) {
	return a.first == b.first && a.second == b.second;
}

bool preprocessor::is_in(std::vector<adj_rule>& rules, adj_rule& rule) {
	for (adj_rule r : rules) {
		if (is_equal(r, rule)) return true;
	}
	return false;
}

void preprocessor::retrieve_tiles(std::vector<tile>& tiles, tile_pool& t_pool, bitmap::bitmap bm) {
	int height = bm.size();
	int width = bm[0].size();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//retrieve the new tile
			tile new_tile;
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					//note we treat the bitmap as infinite tiling here by adding mods
					new_tile.map[x * 3 + y] = bm[(i + x) % height][(j + y) % width];
				}
			}
			//compare it with the list, if not repeated add to it, if repeated update the freq rule
			bool repeat_index = INFINITY;
			int ti = 0;
			for (tile t : tiles) {
				if (is_equal(new_tile, t)) {
					repeat_index = ti;
					t.freq += 1;
					break;
				}
				ti += 1;
			}
			//new tile to add
			if (repeat_index == INFINITY) {
				new_tile.index = tiles.size();
				new_tile.freq = 1;
				t_pool[i][j] = new_tile.index;
				tiles.push_back(new_tile);
			}
			//old tile to update
			else t_pool[i][j] = repeat_index;
		}
	}
}

void preprocessor::retrieve_adj_rules(std::vector<tile>& tiles, tile_pool& t_pool) {
	//walk through each tile and update adj rules, treat map as infinitely tiling
	int pool_height = t_pool.size();
	int pool_width = t_pool[0].size();
	for (tile t : tiles) {
		for (int i = 0; i < pool_height; i++) {
			for (int j = 0; j < pool_width; j++) {
				if (t.index == t_pool[i][j]) {
					adj_rule up_rule;
					int up_index = i - 1;
					if (up_index < 0) up_index += pool_height;
					up_rule.first = t_pool[up_index][j];
					adj_rule down_rule;
					down_rule.first = t_pool[(i + 1) % pool_height][j];
					adj_rule left_rule;
					int left_index = j - 1;
					if (left_index < 0) left_index += pool_width;
					left_rule.first = t_pool[i][left_index];
					adj_rule right_rule;
					right_rule.first = t_pool[i][(j + 1) % pool_width];
					//update only when necessary
					if (!is_in(t.adj_list, up_rule)) t.adj_list.push_back(up_rule);
					if (!is_in(t.adj_list, down_rule)) t.adj_list.push_back(down_rule);
					if (!is_in(t.adj_list, left_rule)) t.adj_list.push_back(left_rule);
					if (!is_in(t.adj_list, right_rule)) t.adj_list.push_back(right_rule);
				}
			}
		}
	}
}
