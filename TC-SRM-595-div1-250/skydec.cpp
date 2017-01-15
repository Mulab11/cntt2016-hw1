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
int l[N],r[N],n,m;
bool a[1005];
LL Main(){
    LL ans=1;
    rep(i,1,n){
        memset(a,0,sizeof a);
        rep(j,i+1,n)rep(k,l[j],r[j])a[k]=1;
        bool flag=0;
        rep(j,l[i],r[i])flag|=(!a[j]);
        if(flag)ans*=2;
    }
    return ans;
}
class LittleElephantAndIntervalsDiv1{
public: 
    LL getNumber(int M, vector <int> L, vector <int> R){
        n=L.size();m=M;
        rep(i,1,n){
            l[i]=L[i-1];
            r[i]=R[i-1];
        }
        return Main();
    }
};