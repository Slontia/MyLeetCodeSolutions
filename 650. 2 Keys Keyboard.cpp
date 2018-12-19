class Solution {
public:
    int minSteps(int n) {
        if (n <= 1) return 0;
        
        std::vector<int> sum(n + 1);
        
        for (size_t i = 2; i <= n; ++i) sum[i] = i;
        
        for (size_t i = 1; i <= n / 2; ++i) {
            for (size_t mul = 2; i * mul <= n; ++mul) {
                sum[i * mul] = std::min((int)(sum[i] + mul), (int)sum[i * mul]);
            }
        }
        
        return sum[n];
    }
};
