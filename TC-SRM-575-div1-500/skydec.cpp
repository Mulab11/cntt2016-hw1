#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=55;
int a[N*N],n,k;
int C(int n,int b){
    //组合数，这里其实只会算到C(a,2)
    if(b==2)return n*(n-1)/2;
    return 23333;
}
double Main(){
    //预处理一些概率
    double A=1.*(C(n-1,2)-1)/(C(n,2)*1.);
    double B=1./(C(n,2)*1.);

    double p=B*((1-pow(A,k))/(1-A))+pow(A,k);

    double all=0;
    double ans=0;
    //all表示所有的可能的数对
    rep(i,1,n)all+=i*(n-i+1);
    rep(i,1,n){
        //枚举位置，计算该位置的贡献
        ans+=(all-i*(n-i+1))*((1-p)/(n-1))*a[i];
        ans+=p*i*(n-i+1)*a[i];
    }
    //计算贡献
    ans/=C(n+1,2);
    return ans;
}
class TheSwapsDivOne{
public:
    double find(vector<string> seq, int k){
        //预处理
        rep(i,0,seq.size()-1)rep(j,0,seq[i].size()-1){
            a[++n]=seq[i][j]-'0';
        }
        ::k=k;
        return Main();
    }
};