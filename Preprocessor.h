#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "bitmap.h"

namespace preprocessor {
	//define a pair of <tile index, direction> as adjacency rules
	//directions follow clockwisely: 0 - up 1 - right 2 - down 3 - left
	typedef std::pair<int, int> adj_rule;
	//define a tile pool as cache for constant time compatibility check and update
	//not we use 2d vector here for convinience and readability
	typedef std::vector<std::vector<int>> tile_pool;

	//define tiles, size as 3x3
	struct tile {
		int index;
		int freq;
		std::vector<adj_rule> adj_list;
		bool map[9];
	};

	//function to compare if a tile is equal to another
	bool is_equal(tile& a, tile& b);
	//function to compare if an adj rule is equal to another
	bool is_equal(adj_rule& a, adj_rule& b);
	//function to check if an adj rule is already in the rule list
	bool is_in(std::vector<adj_rule>& rules, adj_rule& rule);

	//function to retrieve a list of tiles from a bitmap including a map of tiles, updating each one's adj and freq rules as well
	void retrieve_tiles(std::vector<tile>& tiles, tile_pool& t_pool, bitmap::bitmap bm);
	//function to retrieve a list of tiles' adjaceny rules according to a cached tile map
	void retrieve_adj_rules(std::vector<tile>& tiles, tile_pool& t_pool);
}

#endif