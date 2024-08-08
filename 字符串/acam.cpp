struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET> next;
        Node() : len{0}, link{0}, next{} {}
    };

    std::vector<Node> t;

    AhoCorasick() { init(); }

    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int add(const std::string& a) {
        int p = 1;
        for (auto c : a) {
            int x = c - 'a';
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }

    void work() {
        std::queue<int> q;
        q.push(1);

        while (!q.empty()) {
            int x = q.front();
            q.pop();

            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }

    int next(int p, int x) { return t[p].next[x]; }

    int link(int p) { return t[p].link; }

    int len(int p) { return t[p].len; }

    int size() { return t.size(); }
};

// fail����Ҫ����:ֻҪ��fail ����ÿ�������ı����Ľ��Ȩֵ��Ϊ 1����ô�ڵ� x
// ��������Ȩֵ���� x ����Ĵ����ı����г��ֵĴ�����
// ���ý��ۣ�һ��������ƥ�䴮S �г��ִ���֮�ͣ���������S
// ������ǰ׺����Ϊ��׺���� �Ĵ���֮�͡�

//�������⣺
//��ĳ���ı���s������ģʽ����ĳ��ִ�����
//��fail ����ÿ�������ı����Ľ��Ȩֵ��Ϊ 1(ע��Ҫ��������ǰ׺������������next)����ô�ڵ� x
//��������Ȩֵ���� x ����Ĵ����ı����г��ֵĴ���

//������ģʽ�����ı�����ĳ��ִ�����������Ϣ����
//����endpos����ǣ�Ȼ�����´��ݱ�ǣ�
//�ı������ִ����Ĵ�Ϊ��next�������������е��Ȩֵ��


//���ò�������
int n;
cin >> n;
AhoCorasick ac;
vector<int> end(n + 1, 0);
for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    end[i] = ac.add(s);
}

ac.work();

vector<int> cnt(ac.size());
for (int i = 1; i <= n; i++) {
    cnt[end[i]]++;
}
vector<vector<int>> adj(ac.size());
for (int i = 2; i < ac.size(); i++) {
    adj[ac.link(i)].push_back(i);
}
auto dfs = [&](auto self, int u) -> void {
    for (auto v : adj[u]) {
        cnt[v] += cnt[u];
        self(self, v);
    }
};
dfs(dfs, 1);
