/**
 * 声明：和 set 什么的类似，如 setment_tree<ll> a_tree;
 * 记得改 N！！！
 * 一定要开在全局变量！！！或者数组改成 vector
 * 初始化：指定整棵树覆盖的区间的左右端点，如 a_tree.build(1, n);
 * 单点加/区间加：前一/二个参数为加的位置/范围，下一个为加的量，如 a_tree.updata(a_pos, x); a_tree.updata_(l, r, x);
 * 查询区间和/区间最值：指定区间左右端点即可，如 ans = a_tree.query(l, r); ans = query_(l, r);
 */
template<typename T>
struct segment_tree {
    const int N = 4e5 + 10; // 记得改！！！
    int L, R;
    T a[N * 4], sum[N * 4], mx[N * 4], tag[N * 4]; // sum[] 区间和，mx[] 区间最大值，tag[] 懒标记
    void pushup(int x) { // 上传标记
        mx[x] = max(mx[x * 2], mx[x * 2 + 1]);
        sum[x] = sum[x * 2] + sum[x * 2 + 1];
    }
    void build(int l, int r, int x = 1) { // 建树
        if (x == 1) {
            L = l; R = r;
        }
        if (l == r) {
            mx[x] = a[l]; sum[x] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, x * 2);
        build(mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    void updata(int pos, T k, int l = L, int r = R, int x = 1) { // 单点加，a[pos] 加上 k
        if (l == r) {
            mx[x] += k; sum[x] += k;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) updata(pos, k, l, mid, x * 2);
        else updata(pos, k, mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    T query(int ll, int rr, int l = L, int r = R, int x = 1) { // 查询 [ll, rr] 最大值
        if (rr < l || ll > r) return 0; // 不相交
        if (l >= ll && r <= rr) return mx[x]; // 当前区间被查询区间所包含
        // 其他情况
        int mid = (l + r) / 2;
        return max(query(ll, rr, l, mid, x * 2), query(ll, rr, mid + 1, r, x * 2 + 1));
    }
    void pushdown(int l, int r, int x) { // 懒标记下传
        if (tag[x]) {
            int mid = (l + r) / 2, ls = x * 2, rs = x * 2 + 1;
            tag[ls] += tag[x];
            mx[ls] += tag[x];
            sum[ls] += tag[x] * (mid - l + 1);
            tag[rs] += tag[x];
            mx[rs] += tag[x];
            sum[rs] += tag[x] * (r - mid);
            tag[x] = 0;
        }
    }
    void updata_(int ll, int rr, T k, int l = L, int r = R, int x = 1) { // [ll, rr] 区间加 k
        if (ll > r || rr < l) return;
        if (l >= ll && r <= rr) {
            tag[x] += k;
            mx[x] += k;
            sum[x] += k * (r - l + 1);
            return;
        }
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        updata_(ll, rr, k, l, mid, x * 2);
        updata_(ll, rr, k, mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    T query_(int ll, int rr, int l = L, int r = R, int x = 1) { // 查询 [ll, rr] 区间和
        if (rr < l || ll > r) return 0; // 不相交
        if (l >= ll && r <= rr) return sum[x]; // 当前区间被查询区间所包含
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        T ans = query_(ll, rr, l, mid, x * 2) + query_(ll, rr, mid + 1, r, x * 2 + 1);
        pushup(x);
        return ans;
    }
};
