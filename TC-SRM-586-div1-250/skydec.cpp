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
int n,f[N];
int l[N],r[N];
int Main(){
    rep(i,1,n-1)if(f[i]==f[i+1])return -1;

    rep(i,1,n)f[i]=f[i]*2;

    rep(i,1,n-1){
        if(i==1){
            l[i]=f[i];
            r[i]=f[i+1];
            if(l[i]>r[i])swap(l[i],r[i]);
        }
        else{
            if(f[i]<f[i+1]){
                l[i]=f[i]+1;
                r[i]=f[i+1];
            }
            else{
                l[i]=f[i+1];
                r[i]=f[i]-1;
            }
        }
    }

    int ans=0;
    rep(i,1,n-1){
        int ret;
        ret=0;
        rep(j,1,n-1)if(l[j]<=l[i]&&l[i]<=r[j])ret++;
        if(ret>ans)ans=ret;
        ret=0;
        rep(j,1,n-1)if(l[j]<=r[i]&&r[i]<=r[j])ret++;
        if(ret>ans)ans=ret;
    }
    return ans;
}
class PiecewiseLinearFunction{
public:
    int maximumSolutions(vector<int> f){
        n=f.size();
        rep(i,1,n)::f[i]=f[i-1];
        return Main();
    }
};