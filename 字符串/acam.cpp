static constexpr int MAXN = 5e5 + 10;

static constexpr int ALPHABET = 26;
int cnt[MAXN];
struct ACAM {
    int tot = 0;
    int trie[MAXN][ALPHABET]{};
    int fail[MAXN]{};
    int id[MAXN]{};  // ��endpos��¼�����
    void add(string s, int idx) {
        int u = 0;
        for (auto i : s) {
            int x = i - 'a';
            if (!trie[u][x]) {
                trie[u][x] = ++tot;
            }
            u = trie[u][x];
        }
        id[idx] = u;
    }

    void get_fail() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            int c = trie[0][i];
            if (c) {
                q.push(c);
                fail[c] = 0;
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int f = fail[u];
            for (int i = 0; i < 26; i++) {
                int c = trie[u][i];
                if (c) {
                    q.push(c);
                    fail[c] = trie[f][i];
                } else {
                    trie[u][i] = trie[f][i];
                }
            }
        }
    }

    void clear() {
        for (int i = 0; i <= tot; i++) {
            for (int j = 0; j < 26; j++) {
                trie[i][j] = 0;
            }
            fail[i] = 0;
        }
        tot = 0;
    }
} ac;
// fail����Ҫ����:ֻҪ��fail ����ÿ�������ı����Ľ��Ȩֵ��Ϊ 1����ô�ڵ� x
// ��������Ȩֵ���� x ����Ĵ����ı����г��ֵĴ�����
// ���ý��ۣ�һ��������ƥ�䴮S �г��ִ���֮�ͣ���������S
// ������ǰ׺����Ϊ��׺���� �Ĵ���֮�͡�