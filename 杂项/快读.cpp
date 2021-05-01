template <typename T>
void read(T& x) { // 只支持整数
    x = 0;
    char ch = getchar();
    bool flag = 0;
    if (ch == '-') {
        flag = 1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    if (flag) x = -x;
}

template <typename T>
void putnum(T x) { // 比 printf 还慢
    char out[40];
    int digitnum = 0;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    while (x) {
        out[digitnum++] = x % 10 + '0';
        x /= 10;
    }
    while (--digitnum >= 0) putchar(out[digitnum]);
}