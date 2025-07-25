// 匹配最长前缀的长度
vector<int> prefunction(string s) {
    int n = s.size();
    vector<int> p(n);
    for (int i = 1; i < n; i ++) {
        int j = p[i - 1];
        while (j && s[j] != s[i]) {
            j = p[j - 1];
        }
        j += s[j] == s[i];
        p[i] = j;
    }
    return p;
}