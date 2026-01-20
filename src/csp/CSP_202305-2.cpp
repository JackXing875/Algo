#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> transform(const vector<vector<long long>>& A) {
    long long r = A.size(), c = A[0].size();

    vector<vector<long long>> res(c, vector<long long>(r));

    for (long long i = 0; i < c; i++) 
        for (long long j = 0; j < r; j++) 
            res[i][j] = A[j][i];
    
    return res;
}

vector<vector<long long>> mul(const vector<vector<long long>>& A, const vector<vector<long long>>& B) {
    long long n = A.size(), d = A[0].size();
    vector<vector<long long>> res(A.size(), vector<long long>(B[0].size()));

    for (long long i = 0; i < A.size(); i++) 
        for (long long j = 0; j < B[0].size(); j++)
            for (long long k = 0; k < d; k++) 
                res[i][j] += A[i][k] * B[k][j];

    return res;
}

vector<vector<long long>> H(const vector<long long>& W, const vector<vector<long long>>& A) {
    vector<vector<long long>> res(A.size(), vector<long long>(A[0].size()));
    for (long long i = 0; i < W.size(); i++) 
        for (long long j = 0; j < A[0].size(); j++)
            res[i][j] = W[i] *A[i][j];
    return res;
}

int main() {
    long long n, d;
    cin >> n >> d;
    vector<vector<long long>> Q(n, vector<long long>(d)), K(n, vector<long long>(d)), V(n, vector<long long>(d));

    for (long long i = 0; i < n; i++) 
        for (long long j = 0; j < d; j++)
            cin >> Q[i][j];

    for (long long i = 0; i < n; i++) 
        for (long long j = 0; j < d; j++)
            cin >> K[i][j];

    for (long long i = 0; i < n; i++) 
        for (long long j = 0; j < d; j++)
            cin >> V[i][j];

    vector<long long> W(n);
    for (long long i = 0; i < n; i++)
        cin >> W[i];


    vector<vector<long long>> M(d, vector<long long>(d, 0));

    for (long long k = 0; k < n; k++)
        for (long long t = 0; t < d; t++)
            for (long long j = 0; j < d; j++)
                M[t][j] += 1LL * K[k][t] * V[k][j];

    vector<vector<long long>> ans(n, vector<long long>(d, 0));

    for (long long i = 0; i < n; i++) {
        for (long long t = 0; t < d; t++) {
            long long coef = 1LL * W[i] * Q[i][t];
            for (long long j = 0; j < d; j++)
                ans[i][j] += coef * M[t][j];
        }
    }




    for (long long i = 0; i < ans.size(); i++) {
        for (long long j = 0; j < ans[0].size(); j++)
            cout << ans[i][j] << " ";
        cout << "\n";
    }
       
    return 0;
}