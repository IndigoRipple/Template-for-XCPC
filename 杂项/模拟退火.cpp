#define int long long
int fans;
int ans = 1e18;
int cal(int x){
    fans=0;
    //calculate a answer by x
    return fans;
}
void SA(){
    double T = 1926087; //起始温度
    int x = 0; //起始x值
    while(T > 1e-14){ //终止温度
        int new_x = x - (rand() * 2 - RAND_MAX) * T;
        int new_ans = cal(new_x);
        int dE = new_ans - ans;
        if(dE < 0){
            x = new_x;
            ans = new_ans;
        }
        else if(exp(-dE / T) * RAND_MAX > rand()){
            x = new_x;
        }
        T *= 0.993; //降温系数
    }
}
