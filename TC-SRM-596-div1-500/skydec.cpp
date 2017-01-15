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
int cnt[65];
int n,m;
LL a[N];
vector<LL> Main(){
    rep(i,1,n)rep(j,0,59)if(a[i]&(1ll<<j))cnt[j]++;

    rep(i,1,n)rep(j,1,n)if(!(a[i]&a[j])){n=0;goto gtw;}
    rep(i,1,n)rep(j,i+1,n)rep(k,j+1,n)if((a[i]&a[j])&a[k]){n=0;goto gtw;}

    while(n<m){
        int d=m-n-1;

        rep(i,0,59)if(!cnt[i])if(d){
            cnt[i]++;
            a[n+1]|=(1ll<<i);
            d--;
        }

        if(d)break;
        rep(i,1,n){
            int bit=-1;
            rep(j,0,59)if(a[i]&(1ll<<j))if(cnt[j]==1){
                bit=j;break;
            }
            if(bit==-1)goto gtw;
            a[n+1]|=(1ll<<bit);
            cnt[bit]++;
        }
        n++;
    }

    gtw:;
    if(n<m){
        vector<LL> ans;ans.clear();return ans;
    }
    vector<LL> ans;ans.clear();
    sort(a+1,a+1+n);
    rep(i,1,n)ans.push_back(a[i]);
    return ans;
}
class BitwiseAnd{
public:
    vector<long long> lexSmallest(vector<long long> subset, int N){
        n=subset.size();
        rep(i,1,n)a[i]=subset[i-1];
        m=N;
        return Main();
    }
}gt;