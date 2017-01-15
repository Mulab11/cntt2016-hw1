#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
int n,m;
int gcd(int a,int b){if(!a||!b)return a+b;return gcd(b,a%b);}
int d;
LL gtw(int x,int y){
    //\sum\sum(i<x and j<y) (i==j)||((i+j)%d==0)

    if(!x)return 0;

    if(!y)return 0;

    LL ans=x*1ll*y;

    ans-=min(x,y);

    ans--;
    if(x-1>=d-y+1)ans-=(x-1-(d-y+1)+1);

    ans+=1;

    if(d/2<x&&d/2<y)ans++;

    return ans;
}
LL Main(){
    d=2*gcd(n-1,m-1);
    LL ans=n*1ll*m;
    
    ans-=(n/d)*1ll*(m/d)*(d*1ll*d-2*d+1+((d%2)==0));

    ans-=(n/d)*1ll*gtw(d,m%d);

    ans-=(m/d)*1ll*gtw(d,n%d);

    ans-=gtw(n%d,m%d);

    //rep(i,0,d-1)rep(j,0,d-1)if(i^j)if((i+j)%d!=0)ans-=((n/d)+(i<(n%d)))*1ll*((m/d)+(j<(m%d)));

    return ans;
}
class PyramidSequences{
public:
    LL distinctPairs(int N,int M){
        n=N;m=M;
        return Main();
    }
}gt;