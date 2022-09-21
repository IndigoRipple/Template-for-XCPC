// 保证模的结果在 [0, mod) 之间

using ll = long long;

struct fastmod {
    ll _mod;
    __int128_t _base;
    fastmod(): _mod(0), _base(0) {}
    fastmod(const ll& mod): _mod(mod) {
        _base = ((__int128_t)1 << 64) / mod;
    }
    void set_mod(const ll& mod) {
        _mod = mod;
        _base = ((__int128_t)1 << 64) / mod;
    }
};

ll operator%(const ll& x, const fastmod& m) {
    return x - m._mod * (m._base * x >> 64);
}

ll operator%=(ll& x, const fastmod& m) {
    return x = x % m;
}