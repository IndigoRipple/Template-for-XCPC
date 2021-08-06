// Size Balanced Tree

/**
 * 必须开全局变量！清除这棵树的内容可以用 clear()
 * maxn 是这棵树的最多结点数 + 1
 * 声明一个 sbt 的例子：sbt<int, 1000001> s;
 */
template <typename T, int maxn>
class sbt {
    using Pair = pair<int, bool>;
    private:
    T val[maxn] = {0}; // 存的内容
    int lchild[maxn] = {0}, rchild[maxn] = {0}; // 左儿子、右儿子
    int subsize[maxn] = {0}; // 该节点为根的子树的大小
    int root = 0;
    stack<Pair> maintain_stack;
    void lrotate(const int& root) {
        int temp = rchild[root];
        subsize[temp] = subsize[lchild[root]] + subsize[lchild[temp]];
        swap(val[root], val[temp]);
        rchild[root] = rchild[temp];
        rchild[temp] = lchild[temp];
        lchild[temp] = lchild[root];
        lchild[root] = temp;
    }
    void rrotate(const int& root) {
        int temp = lchild[root];
        subsize[temp] = subsize[rchild[root]] + subsize[rchild[temp]];
        swap(val[root], val[temp]);
        lchild[root] = lchild[temp];
        lchild[temp] = rchild[temp];
        rchild[temp] = rchild[root];
        rchild[root] = temp;
    }
    void maintain() {
        while (!maintain_stack.empty()) {
            const int pos = maintain_stack.top().first;
            const bool flag = maintain_stack.top().second;
            maintain_stack.pop();
            if (!pos) continue;
            if (flag)
                if (subsize[rchild[rchild[pos]]] > subsize[lchild[pos]]) lrotate(pos);
                else if (subsize[lchild[rchild[pos]]] > subsize[lchild[pos]]) {
                    rrotate(rchild[pos]);
                    lrotate(pos);
                } else continue;
            else
                if (subsize[lchild[lchild[pos]]] > subsize[rchild[pos]]) rrotate(pos);
                else if (subsize[rchild[lchild[pos]]] > subsize[rchild[pos]]) {
                    lrotate(lchild[pos]);
                    rrotate(pos);
                } else continue;
            maintain_stack.push({pos, 1});
            maintain_stack.push({pos, 0});
            maintain_stack.push({rchild[pos], 1});
            maintain_stack.push({lchild[pos], 0});
        }
    }
    public:
    int size() { return subsize[root]; }
    int count(const T& x) {
        if (!root) return 0;
        int pos = root;
        while (1)
            if (val[pos] == x) return 1;
            else if (val[pos] < x)
                if (rchild[pos]) pos = rchild[pos];
                else return 0;
            else
                if (lchild[pos]) pos = lchild[pos];
                else return 0;
    }
    int count_greater(const T& x) {
        int pos = root, ret = 0;
        while (1)
            if (val[pos] == x) return ret + subsize[rchild[pos]]; // 要查询大于等于 x 的话这里加一下 1
            else if (val[pos] < x)
                if (rchild[pos]) pos = rchild[pos];
                else return ret;
            else {
                ret += subsize[rchild[pos]] + 1;
                if (lchild[pos]) pos = lchild[pos];
                else return ret;
            }
    }
    int kth_smallest(int k) {
        int pos = root;
        while (1)
            if (subsize[lchild[pos]] == k - 1) return val[pos];
            else if (subsize[lchild[pos]] < k) {
                k -= subsize[lchlid[pos]];
                pos = rchild[pos];
            } else pos = lchild[pos];
    }
    void insert(const T& x) {
        if (!root) {
            root = 1;
            val[1] = x;
            subsize[1] = x;
            return;
        }
        int pos = root;
        stack<int> s;
        while (1)
            if (val[pos] == x) {
                maintain_stack.clear();
                return;
            } else if (val[pos] < x) {
                maintain_stack.push({pos, 1});
                s.push(pos);
                if (rchild[pos]) pos = rchild[pos];
                else {
                    int newpos = subsize[root] + 1;
                    rchild[pos] = newpos;
                    val[pos] = x;
                    subsize[pos] = 1;
                    break;
                }
            } else {
                maintain_stack.push({pos, 0});
                s.push(pos);
                if (lchild[pos]) pos = lchild[pos];
                else {
                    int newpos = subsize[root] + 1;
                    lchild[pos] = newpos;
                    val[pos] = x;
                    subsize[pos] = 1;
                    break;
                }
            }
        while (!s.empty()) {
            ++subsize[s.top()];
            s.pop();
        }
        maintain();
    }
    void clear() {
        for (int i = subsize[root]; i; --i) lchild[i] = rchild[i] = subsize[i] = 0;
        root = 0;
    }
};