using ll = long long;

void solve() {
    ll n, k;
    cin >> n >> k;
    // k��dp, ÿ��nλ
    vector<ll> f(n + 1), g(n + 1); // ��������

    // б���Ż�, ��(X, Y), б��K, 
    auto X = [&](int i) { return 1; }; // 
    auto Y = [&](int i) { return 1; }; // 
    auto K = [&](int i) { return 1; }; // 

    // ����б��
    auto slope = [&](int i, int j) -> long double{
        if(X(j) == X(i)) return (Y(j) >= Y(i) ? 1e18 : -1e18);
        else {
            return (long double)(Y(j) - Y(i)) / (X(j) - X(i));
        }
    };
    
    // ���д�͹��
    vector<int> q(n + 3);

    for(int i = 1; i <= n; ++i) {
        // g[i] = ... ;
        // ��ʼ��k = 1��һ�����ֱ�Ӽ���
    }

    // ��͹��Ϊ��
    for(int c = 2; c <= k; ++c) {
        int head = 1, tail = 0;
        q[++tail] = 0;
        for(int i = 1; i <= n; ++i) {
            while(head < tail && slope(q[head], q[head + 1]) <= K(i)) ++head;
            ll B = Y(q[head]) - K(i) * X(q[head]);
            // f[i] = B + ...; f[i] �� B ֮���ʽ��
            while(head < tail && i != n && slope(q[tail - 1], q[tail]) >= slope(q[tail], i)) --tail;
            q[++tail] = i;
        }
        std::swap(f, g);
    }
    cout << g[n];
}
