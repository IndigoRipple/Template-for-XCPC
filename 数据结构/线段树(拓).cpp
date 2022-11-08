/**
 * 维护区间加法、乘法、赋值、最值
 * 操作和注意事项与“简”类似
 */
const int N, inf = INT_MAX / 2;
int a[N], L, R;
struct segment_tree {
    int sum[N * 4], mx[N * 4];
    struct LazyTag {
        int add, mul; // 三种懒标记
        optional<int> col;
    } tag[N * 4];
    void pushup(int x) { //上传标记
        sum[x] = sum[x * 2] + sum[x * 2 + 1];
        mx[x] = max(mx[x * 2], mx[x * 2 + 1]);
    }
    void pushdown(int l, int r, int x) { // 下放标记
        int ls = x * 2, rs = x * 2 + 1, mid = (l + r) / 2;
        if (tag[x].col) { // 有赋值标记
            T c = tag[x].col.value;
            tag[ls].add = tag[rs].add = 0;
            tag[ls].mul = tag[rs].mul = 1;
            sum[ls] = c * (mid - l + 1);
            sum[rs] = c * (r - mid);
            tag[ls].col = tag[rs].col = c;
            mx[ls] = mx[rs] = c;
            tag[x].col.reset();
        }
        if (tag[x].mul != 1) { // 有乘法标记
            T c = tag[x].mul;
            tag[ls].mul *= c;
            tag[rs].mul *= c;
            sum[ls] *= c;
            sum[rs] *= c;
            mx[ls] *= c;
            mx[rs] *= c;
            tag[ls].add *= c;
            tag[rs].add *= c;
            tag[x].mul = 1;
        }
        if (tag[x].add != 0) { // 有加法标记
            T c = tag[x].add;
            tag[ls].add += c;
            tag[rs].add += c;
            sum[ls] += c * (mid - l + 1);
            sum[rs] += c * (r - mid);
            mx[ls] += c;
            mx[rs] += c;
            tag[x].add = 0;
        }
        return;
    }
    void build(int l, int r, int a[], int x = 1) { // 建树
        if (l == r) {
            sum[x] = mx[x] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, x * 2);
        build(mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    void init(int a[], int l, int r) {
        L = l; R = r;
        for (int i = 1; i <= r * 4; i++) tag[i].mul = 1;
        build(L, R, a);
    }
    void update_col(int ll, int rr, int k, int l = L, int r = R, int x = 1) { // a[ll...rr] = k
        if (r < ll || l > rr) return;
        if (l >= ll && r <= rr) {
            sum[x] = k * (r - l + 1);
            mx[x] = k;
            tag[x].mul = 1;
            tag[x].add = 0;
            tag[x].col = k;
            return;
        }
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        update_col(ll, rr, k, l, mid, x * 2);
        update_col(ll, rr, k, mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    void updata_mul(int ll, int rr, int k, int l = L, int r = R, int x = 1) { // a[ll...rr] *= k
        if (r < ll || l > rr) return;
        if (l >= ll && r <= rr) {
            sum[x] = sum[x] * k;
            mx[x] = mx[x] * k;
            tag[x].mul = tag[x].mul * k;
            tag[x].add = tag[x].add * k;
            return;
        }
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        updata_mul(ll, rr, k, l, mid, x * 2);
        updata_mul(ll, rr, k, mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    void update_add(int ll, int rr, int k, int l = L, int r = R, int x = 1) { // a[ll...rr] += k
        if (r < ll || l > rr) return;
        if (l >= ll && r <= rr) {
            sum[x] = sum[x] + k * (r - l + 1);
            mx[x] = mx[x] + k;
            tag[x].add = tag[x].add + k;
            return;
        }
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        update_add(ll, rr, k, l, mid, x * 2);
        update_add(ll, rr, k, mid + 1, r, x * 2 + 1);
        pushup(x);
    }
    int query_sum(int ll, int rr, int l = L, int r = R, int x = 1) { // sum(a[ll...rr])
        if (r < ll || l > rr) return 0;
        if (l >= ll && r <= rr) return sum[x];
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        return query_sum(ll, rr, l, mid, x * 2) + query_sum(ll, rr, mid + 1, r, x * 2 + 1);
    }
    int query_mx(int ll, int rr, int l = L, int r = R, int x = 1) { // 查询 [ll, rr] 最值
        if (r < ll || l > rr) return -inf;
        if (l >= ll && r <= rr) return mx[x];
        pushdown(l, r, x);
        int mid = (l + r) / 2;
        return max(query_mx(ll, rr, l, mid, x / 2), query_mx(ll, rr, mid + 1, r, x * 2 + 1));
    }
};
