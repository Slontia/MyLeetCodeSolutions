
// DP
class Solution {
public:
    int numTrees(int n) {
        if (n <= 0) return 0;
        int res[n + 1] = {0};
        
        res[0] = 1;
        res[1] = 1;
        
        for (int i = 2; i <= n; ++i ) {
            for (int root = 1; root <= i / 2; ++root) {
                res[i] += res[root - 1] * res[i - root];
            }
            res[i] *= 2;
            if (i % 2) res[i] += res[i / 2] * res[i / 2];
        }
        
        return res[n];
    }
};
