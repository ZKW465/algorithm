using ll = long long;
const int maxn = 1e5 + 5;

struct node {
    int id;
    ll x, y, k;
};
// a��ʾԭ���飬bΪ�鲢��������
vector<node> a(maxn), b(maxn);

ll X(int i) { return a[i].x; }
ll Y(int i) { return a[i].y; }
ll K(int i) { return a[i].k; }
long double slope(int i, int j) {
    if(X(j) == X(i)) return (Y(j) >= Y(i) ? 1e20 : -1e20);
    else {
        return (long double)(Y(j) - Y(i)) / (X(j) - X(i));
    }
};

// dp����, �м�f[]�ĳ�ʼ��
vector<ll> f(maxn, 1e18);

// ����x���й鲢
void merge(int L, int mid, int R)
{
    int p1 = L, p2 = mid + 1;
    int tp = L;
    while(p1 <= mid && p2 <= R) {
        if(a[p1].x <= a[p2].x) b[tp++] = a[p1++];
        else b[tp++] = a[p2++];
    }
    while(p1 <= mid) b[tp++] = a[p1++];
    while(p2 <= R) b[tp++] = a[p2++];
    for(int i = L; i <= R; ++i) a[i] = b[i];
}

void cdq(int L, int R) {
    if(L == R) {
        int pos = a[L].id;
        // f[pos] = ...; //��������޸ģ���Щ���Ϊǰ׺���ţ����ڴ˴��޸ġ�
        // ��f[pos] = max(f[pos], f[pos - 1]);
        // a[L].x = ;
        // a[L].y = ;
        return ;
    }

    int mid = (L + R) >> 1;
    // ��Ϊ��������
    int p1 = L, p2 = mid + 1;
    for(int i = L; i <= R; ++i) {
        if(a[i].id <= mid) b[p1++] = a[i];
        else b[p2++] = a[i];
    }
    for(int i = L; i <= R; ++i) a[i] = b[i];

    cdq(L, mid);

    // ��͹��, ��͹������Ҫ�ĳ� slope() <= slope()
    vector<int> q(R - L + 3);
    int head = 1, tail = 0;
    for(int i = L; i <= mid; ++i) {
        while(head < tail && slope(q[tail - 1], q[tail]) >= slope(q[tail], i)) --tail;
        q[++tail] = i;
    }

    // ��͹��, ��͹������Ҫ�ĳ� slope() >= K()��ͬʱf[pos] = max(f[pos], B ...)
    for(int i = mid + 1; i <= R; ++i) {
        while(head < tail && slope(q[head], q[head + 1]) <= K(i)) ++head;
        ll B = Y(q[head]) - K(i) * X(q[head]);
        int pos = a[i].id;
        // f[pos] = min(f[pos], B ...);
    }

    cdq(mid + 1, R);

    merge(L, mid, R);
}

void solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        // a[i].id = i;
        // a[i].k = 2 * h[i];
    }

    // ��͹��, ��͹���޸�Ϊ x.k > y.k;
    sort(a.begin() + 1, a.begin() + n + 1, [&](node &x, node &y){
        return x.k < y.k;
    });

    f[1] = 0; // ���������ʼ��
    cdq(1, n);
    cout << f[n]; // һ������Ϊf[n] 
}
