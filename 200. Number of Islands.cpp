// 典型的简单问题复杂化，一开始把BFS和DFS的复杂度想成O(n^2)了，于是想出这么个弱智的解法……我先去撞会墙

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        const auto& width = grid.size();
        const auto& length = grid[0].size();
        
        int** land_map = new int*[2];
        land_map[0] = new int[length];
        land_map[1] = new int[length];
        
        for (size_t x = 0; x < width; ++x) {
            for (size_t y = 0; y < length; ++y) {
                if (grid[x][y] - '0') record_land(land_map, x, y);
                else land_map[x % 2][y] = 0;
            }
        }
        //cout << island_count << " " << combine_count;
        return island_count - combine_count;
    }
    
private:
    int island_count = 0;
    int combine_count = 0;
    std::unordered_map<int, int> combine_map;
    
    void record_land(int** map, const size_t& x, const size_t& y) {
        const bool& line = x % 2;
        const auto& neighbor_1 = (x > 0) ? map[!line][y] : 0;
        const auto& neighbor_2 = (y > 0) ? map[line][y - 1] : 0;
        //cout << "n1:" << neighbor_1 << " n2:" << neighbor_2 << endl;
        if (!neighbor_1 && !neighbor_2) {
            //cout << x << " " << y << endl;
            map[line][y] = ++island_count;
        
        } else if (neighbor_1 && !neighbor_2) {
            map[line][y] = neighbor_1;
            
        } else if (!neighbor_1 && neighbor_2) {
            map[line][y] = neighbor_2;
        
        } else if (neighbor_1 == neighbor_2) {
            map[line][y] = neighbor_2;
        
        } else { // neighbor_1 != neighbor_2
            const auto& top_1 = get_top(neighbor_1);
            const auto& top_2 = get_top(neighbor_2);
            if (top_1 == top_2) {
                map[line][y] = neighbor_2;
                if (top_2 > neighbor_1) combine_map[neighbor_1] = top_2;
                if (top_2 > neighbor_2) combine_map[neighbor_2] = top_2;
            } else {
                map[line][y] = neighbor_2;
                const auto& max = std::max(top_1, top_2);
                const auto& min = std::min(top_1, top_2);
                combine_map[min] = max;
                if (max > neighbor_1) combine_map[neighbor_1] = max;
                if (max > neighbor_2) combine_map[neighbor_2] = max;
                ++combine_count;
            }
            
        }
    }
    
    int get_top(int landno) {
        decltype(combine_map)::iterator it;
        while ((it = combine_map.find(landno)) != combine_map.end()) landno = it->second;
        return landno;
    }
};
