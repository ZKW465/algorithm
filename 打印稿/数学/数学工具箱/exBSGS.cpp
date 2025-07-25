/**
 * Algorithm: Extended Baby-Step Giant-Step (BSGS)
 * Purpose: Solves a^x ¡Ô b (mod m) for x, even when a and m are not coprime
 * 
 * Parameters:
 *   a - base
 *   b - result
 *   m - modulus
 *   k - internal parameter used in recursion (default 1)
 * 
 * Returns:
 *   The smallest non-negative integer x satisfying the equation, or -1 if no solution exists
 * 
 * Time Complexity: O(¡Ìm)
 * Space Complexity: O(¡Ìm)
 * 
 * Note: For better performance with large m, consider using a custom hash table
 */
int exBSGS(int a, int b, int m, int k = 1) {
    auto BSGS = [&](int a, int b, int m, int k = 1) {
        std::map<int, int> map;  // use hash table will be better
        int cur = 1, t = sqrt(m) + 1;
        for (int B = 1; B <= t; ++B) {
            cur = 1LL * cur * a % m;
            map[1LL * b * cur % m] = B;
        }
        int now = 1LL * cur * k % m;
        for (int A = 1; A <= t; ++A) {
            auto it = map.find(now);
            if (it != map.end()) {
                i64 res = 1LL * A * t - it->second;
                assert(res <= std::numeric_limits<int>::max());
                return int(res);
            }
            now = 1LL * now * cur % m;
        }
        return int(-1); // ÎÞ½â
    };
    int A = a %= m, B = b %= m, M = m;
    if (b == 1) 
        return 0;
    int cur = 1 % m;
    for (int i = 0;; i++) {
        if (cur == B) 
            return i;
        cur = 1LL * cur * A % M;
        int d = std::gcd(a, m);
        if(b % d) 
            return -1;
        if (d == 1) {
            int ans = BSGS(a, b, m, 1LL * k * a % m);
            return ans == -1 ? ans : ans + i + 1;
        }
        k = 1LL * k * a / d % m, b /= d, m /= d;
    }
}