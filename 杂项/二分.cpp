int l = 0,r = MAX,mid,ans;
while(l <= r) {
    mid = (l + r)>>1;
    if(check(mid)){
        ans = mid;
        l = mid + 1;
    }
    else r = mid - 1;
}
