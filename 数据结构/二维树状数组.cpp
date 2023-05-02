//单点修改+区间查询
void updata(int x, int y, int d){//将点(x, y)加上d
    int temp = y;
    for(; x <= n; x += lowbit(x)){
        for(y = temp; y <= n; y += lwbit(y)){
            arr[x][y] += d;
        }
    }
}
int getsum(int x, int y){//求左上角为(1,1)右下角为(x,y) 的矩阵和
    int res = 0, temp = y;
    for(;x > 0; x -= lowbit(x)){
        for(y = temp; y > 0; y -= lowbit(y)){
            res += arr[x][y];
        }
    }
    return res;
}
int query(int x,int y){//区间最值
	int maxx=0,minn=inf;
	for(int i=N-x;i;i-=lowbit(i)){
		for(int j=y;j;j-=lowbit(j)){
			maxx=max(mx[i][j],maxx);
			minn=min(mn[i][j],minn);
		}
	}
	if(minn==inf) return 0;
	return maxx-minn;
}

//区间修改+单点查询
void updata(int x, int y, int d){
	for(int i = x; i <= n; i += lowbit(i)){
		for(int j = y; j <= m; j += lowbit(j)){
			tree[i][j] += d;
		}
	}
}

ll getsum(int x, int y){
	ll res = 0;
	for(int i = x; i > 0; i -= lowbit(i)){
		for(int j = y; j > 0; j -= lowbit(j)){
			res += tree[i][j];
		}
	}
	return res;
}
void range_add(){
	cin >> a >> b >> c >> d >> k;
	updata(a,b,k);
	updata(a,d+1,-k);
	updata(c+1,b,-k);
	updata(c+1,d+1,k);
}

//区间修改+区间查询
void updata(int x, int y, int d){
	for(int i = x; i <= n; i += lowbit(i)){
		for(int j = y; j <= m; j += lowbit(j)){
			tree1[i][j] += d;
			tree2[i][j] += x * d;
			tree3[i][j] += y * d;
			tree4[i][j] += x * y * d;
		}
	}
}

ll getsum(int x, int y){
	ll res = 0;
	for(int i = x; i > 0; i -= lowbit(i)){
		for(int j = y; j > 0; j -= lowbit(j)){
			res += (x + 1) * (y +1) * tree1[i][j] - (x + 1) * tree3[i][j] - (y + 1) * tree2[i][j] + tree4[i][j];
		}
	}
	return res;
}
void range_add(){
	cin >> a >> b >> c >> d >> k;
	updata(a,b,k);
	updata(a,d+1,-k);
	updata(c+1,b,-k);
	updata(c+1,d+1,k);
}
void print(){
	cin >> a >> b >> c >> d;
	cout << getsum(c,d) - getsum(c,b-1) - getsum(a-1,d) + getsum(a-1,b-1) << endl;
}

