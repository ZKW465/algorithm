// ��iλ��ǰiλ������ʾ�Ӹ�λ��ʼ�ĵڼ�λ
vector<int> r(N); ��ʾ���ֵ�Ӹ�λ��ʼ��iλ������
vector<int> dp(N); ��ʾû�������µ�iλ�Ĵ�
vector<int> pw(N); ��ʾpower(10, i)
vector<int> num(N); ��ʾ���ֵ%pw[i]����ǰiλ�������ֵ����

// pos ��ʾ��ǰ������posλ,
// lim��ʾ�Ƿ�����������ƣ�1Ϊtrue
// ok��ʾ�Ƿ�ǰ��ȫΪ0, 1Ϊtrue
auto dfs = [&](auto &&dfs, int pos, int lim, int ok) -> ll {
    if(pos == 0) return 1ll; //���� 0ll
	if(lim == 0 && ok == 0 && dp[pos]) return dp[pos]; 
    
    int up = (lim == 1 ? r[pos] : 9);
    ll ret = 0;
    for(int i = 0; i <= up; ++i) {
		if(ok == 1 && i == 0) 
            ret += dfs(dfs, pos - 1, lim && (i == r[pos]), 1);
        else 
            ret += dfs(dfs, pos - 1, lim && (i == r[pos]), 0);
    }
    if(lim == 0 && ok == 0) dp[pos] = ret;
    return ret;
};

auto ask = [&](ll x) {
    int len = 0;
    while(x) {
        len ++:
        r[len] = x%10;
        x /= 10;
	}
    
    pw[0] = 1;
    for(int i = 1; i <= len; ++i) {
		num[i] = num[i - 1] + r[i] * pw[i - 1];
         pw[i] = pw[i - 1] * 10; 
    }
    
    return dfs(dfs, len, 1, 1);
};
