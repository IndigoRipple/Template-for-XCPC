using ll = long long;
using ld = long double;

const ld eps;

template<typename T>
using matrix = vector<vector<T>>;

template<typename T>
ld det(matrix<T> m) {
    ll n = a.size();
    ld ret = 1;
    for (ll i = 0; i < n; i++) {
        ll k = i;
        for (ll j = i + 1; j < n; j++) {
            if (abs(m[j][i]) > abs(m[k][i])) {
                k = j;
            }
        }
        if (abs(m[k][i]) < eps) return 0;
        swap(m[i], m[k]);
        if (i != k) ret = -ret;
        ret *= m[i][i];
        for (ll j = i + 1; j < n; j++) m[i][j] /= m[i][i];
        for (ll j = 0; j < n; j++) {
            if (j != i && abs(m[j][i]) > eps) {
                for (ll k = i + 1; k < n; k++) {
                    m[j][k] -= m[i][k] * m[j][i];
                }
            }
        }
    }
    return ret;
}
