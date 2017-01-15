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
int cnt[N];
int n;
int Main(){
    int ans=n;
    rep(i,0,n){
        int dj=2*(n-i);
        rep(j,i+1,n)if(cnt[j]==1){
            dj+=(-(n-i))+j-1-i;break;
        }
        if(dj>ans)ans=dj;
    }
    return ans;
}
class TheTree{
public:
    int maximumDiameter(vector <int> cnt){
        n=cnt.size();
        rep(i,1,n)::cnt[i]=cnt[i-1];
        return Main();
    }
};