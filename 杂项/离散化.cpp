int lsh[N];
for(int i = 1; i <= n; i++) lsh[i] = a[i];
sort(lsh + 1,lsh + n + 1);
int SIZE = unique(lsh + 1,lsh + n + 1) - (lsh + 1);  
for(int i = 1; i <= n; i++){
    a[i] = upper_bound(lsh + 1,lsh + SIZE + 1,a[i]) - (lsh + 1);
}
