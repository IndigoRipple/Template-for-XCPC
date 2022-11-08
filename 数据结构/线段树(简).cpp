/**
 * 声明： set_tree t;
 * 一定要开在全局变量！！！或者数组改成 vector
 * 初始化：指定整棵树覆盖的区间的左右端点，如 t.init(1, n);
 * 单点加/区间加：前一/二个参数为加的位置/范围，下一个为加的量，如 a_tree.update_add1(a_pos, x); a_tree.update_add2(l, r, x);
 * 查询区间和/区间最值：指定区间左右端点即可，如 ans = t.query_sum(l, r); ans = t.query_max(l, r);
 */
const int N;
int a[N], L, R;
struct seg_tree {
    int sum[N * 4], mx[N * 4], tag[N * 4]; // sum[] 区间和，mx[] 区间最大值，tag[] 懒标记
    void pushup(int x) { // 上传标记
        mx[x] = max(mx[x * 2], mx[x * 2 + 1]);
        sum[x] = sum[x * 2] + sum[x * 2 + 1];
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
    void build(int l, int r, int a[], int x = 1) { // 建树
        if (l == r) {
            mx[x] = sum[x] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, a, x * 2);
        build(mid + 1, r, a, x * 2 + 1);
        pushup(x);
    }
    void init(int a[], int l, int r) {
        L = l; R = r;
        build(L, R, a);
    }
    void update_add1(int pos, int k, int l = L, int r = R, int x = 1) { // a[pos] += k
        if (l == r) {
            mx[x] += k; sum[x] += k;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update_add1(pos, k, l, mid, x * 2);
        else update_add1(pos, k, mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    void update_add2(int ll, int rr, int k, int l = L, int r = R, int x = 1) { // a[ll...rr] += k
        if (ll > r || rr < l) return;
        if (l >= ll && r <= rr) {
            tag[x] += k;
            mx[x] += k;
            sum[x] += k * (r - l + 1);
            return;
        }
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        update_add2(ll, rr, k, l, mid, x * 2);
        update_add2(ll, rr, k, mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    int query_max(int ll, int rr, int l = L, int r = R, int x = 1) { // max(a[ll...rr])
        if (rr < l || ll > r) return 0; // 不相交
        if (l >= ll && r <= rr) return mx[x]; // 当前区间被查询区间所包含
        // 其他情况
        int mid = (l + r) / 2;
        return max(query_max(ll, rr, l, mid, x * 2), query_max(ll, rr, mid + 1, r, x * 2 + 1));
    }
    int query_sum(int ll, int rr, int l = L, int r = R, int x = 1) { // sum(a[ll...rr])
        if (rr < l || ll > r) return 0; // 不相交
        if (l >= ll && r <= rr) return sum[x]; // 当前区间被查询区间所包含
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        int ans = query_sum(ll, rr, l, mid, x * 2) + query_sum(ll, rr, mid + 1, r, x * 2 + 1);
        pushup(x);
        return ans;
    }
};
