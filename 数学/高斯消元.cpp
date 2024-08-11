// ʱ�临�Ӷȣ�O(m * n^2), -1�޽⣬0Ψһ�⣬���������
// aΪ������� ��r:[0, n) ��c:[0, m]��a[i][m]Ϊb[0, n)������Ϊ x[0, m)
int Gauss(vector<vector<double>> &a, vector<double> &x, int n, int m, double eps = 1e-7){
    int r = 0, c = 0;
    for(r = 0; r < n && c < m; r++, c++) {
        int maxr = r;
        for(int i = r + 1; i < n; i++) {
            if(abs(a[i][c]) > abs(a[maxr][c]))
                maxr = i;
        }
        if(maxr != r) std::swap(a[r], a[maxr]);
        if(fabs(a[r][c]) < eps) {
            r--;
            continue;
        }
        for(int i = r + 1; i < n; i++) {
            if(fabs(a[i][c]) > eps){
                double k = a[i][c] / a[r][c];
                for(int j = c; j < m + 1; j++) a[i][j] -= a[r][j] * k;
                a[i][c] = 0;
            }
        }
    } 
    for(int i = r; i < m; i++) {
    	if(fabs(a[i][c]) > eps) return -1;//�޽�
    }    
    if(r < m) return m - r;//��������Ԫ����
    for(int i = m-1; i >= 0; i--) {
        for(int j = i + 1; j < m; j++) a[i][m] -= a[i][j] * x[j];
        x[i] = a[i][m] / a[i][i];
    }
    return 0;//��Ψһ��
}
