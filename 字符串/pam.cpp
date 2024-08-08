struct Palindrome_Automaton {
    int ch[N][Sigma], fail[N], len[N], cnt[N], tot, last;
    Palindrome_Automaton() {
        tot = 1;
        fail[0] = 1, fail[1] = 1, len[1] = -1;
    }
    int getfail(int x, int i) {
        while (i - len[x] - 1 < 0 || s[i - len[x] - 1] != s[i])
            x = fail[x];
        return x;
    }
    void insert(char c, int i) {
        int x = getfail(last, i), w = c - 'a';
        if (!ch[x][w]) {
            len[++tot] = len[x] + 2;
            int tmp = getfail(fail[x], i);
            fail[tot] = ch[tmp][w];
            cnt[tot] = cnt[fail[tot]] + 1;
            ch[x][w] = tot;
        }
        last = ch[x][w];
    }

} PAM;

// Ӧ�ã�
// 1����s���ʲ�ͬ���Ĵ��������Զ���״̬��
// 2�������л����Ӵ��ֱ���ִ���:�����ʱ��cnt[last]++��Ȼ���ѯ��ʱ����cnt[fail[i]]+=cnt[i]
// 3: �Ե�i��λ��Ϊ��β�Ļ��Ĵ�������cnt[i]=cnt[fail[i]]+1���߼ӱ߲�cnt[last]
// 4:
