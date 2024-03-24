struct Linear_Base {
    int siz;
    vector<int> a;  
    Linear_Base(int _siz) {
        siz = _siz;
        a.resize(siz + 1);
    }
    void insert(int x) {//����
        for (int i = siz; i >= 0; i--) if (x & (1ll << i)) {
            if (!a[i]) { a[i] = x; return; }
            else x ^= a[i];
        }
    }
    bool check(int x) {//��ѯx�Ƿ��ܱ�������
        for (int i = siz; i >= 0; i--) if (x & (1ll << i)) {
            if (!a[i]) break;
            x ^= a[i];
        }
        return x == 0;
    }
    int querymax(int res) {//��ѯ�������
        for (int i = siz; i >= 0; i--) if ((res ^ a[i]) > res) res ^= a[i];
        return res;
    }
    int querymin(int res) {//��ѯ��С
        for (int i = siz; i >= 0; i--) if (res & (1ll << i)) res ^= a[i];
        return res;
    }
    int querykth(int k) {//��ѯ��k�������
        vector<int> tmp(siz + 10);
        int res = 0, cnt = 0;
        for (int i = 0; i <= siz; i++) {
            for (int j = i - 1; j >= 0; j--) if (a[i] & (1ll << j)) a[i] ^= a[j];
            if(a[i]) tmp[cnt++] = a[i];
        }
        for (int i = 0; i < cnt; i++) if (k & (1ll << i)) res ^= tmp[i];
        return res;
    }
    void merge(const Linear_Base& other)//�ϲ�
    {
        for (int i = 0; i <= siz; i++) insert(other.a[i]);
    }
};
