class Solution {
public:
    int integerBreak(int n) {
        std::vector<int> res(n + 1, 1);
        
        for (int i = 2; i <=n; ++i) {
            for (int j = 1; j < i; ++j) {
                res[i] = std::max(res[i], std::max(res[j], j) * (i - j)); // 这里std::max(res[j], j)一开始被写成了res[j]，我没有考虑到加数可以不拆分
            }
        }
        
        return res[n];
    }
};
