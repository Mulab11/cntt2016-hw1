#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=3005;
int f[N];
bool check1(int n,int w,int x){
    if(w==1&&((x==1)||(x==n)))return 1;
    if(x==1&&n<=w)return 1;
    if(n<=w&&x==n)return 1;
    if(x==w&&n<2*w)return 1;
    if((x%w==1)&&(x==n))return 1;
    return 0;
}
bool check2(int n,int w,int x){
    bool ans=0;
    ans|=check1(min(((x+w-1)/w)*w,n),w,x);

    rep(i,1,n)if(f[i]<=((x+w-1)/w)-1)
    ans|=check1(n-i,w,x-i);

    rep(i,1,(x-1)%w)rep(j,1,(x+w-1)/w){
        int res=n-(n/w-j+1)*i-min(n%w,i);

        ans|=check1(res,w,x-(((x+w-1)/w)-j+1)*i);
    }

    rep(i,1,(w-(x%w))%w)rep(j,1,x/w){
        int res=n-(n/w-j+1)*i-max(0,min((n%w)-(x%w+1)+1,i));

        ans|=check1(res,w,x-((x/w)-j+1)*i);
    }

    return ans;
}
bool check3(int n,int w,int x){
    bool ans=0;
    ans|=check2(min(((x+w-1)/w)*w,n),w,x);

    rep(i,1,n)if(f[i]<=((x+w-1)/w)-1)
    ans|=check2(n-i,w,x-i);

    rep(i,1,(x-1)%w)rep(j,1,(x+w-1)/w){
        int res=n-(n/w-j+1)*i-min(n%w,i);

        ans|=check2(res,w,x-(((x+w-1)/w)-j+1)*i);
    }

    rep(i,1,(w-(x%w))%w)rep(j,1,x/w){
        int res=n-(n/w-j+1)*i-max(0,min((n%w)-(x%w+1)+1,i));

        ans|=check2(res,w,x-((x/w)-j+1)*i);
    }

    return ans;
}
class FoxAndAvatar{
public:
    int minimalSteps(int n, int w, int x){
        memset(f,63,sizeof f);
        rep(i,1,w)rep(j,1,n/i)f[i*j]=min(f[i*j],j);

        if(n==1)return 0;
        if(check1(n,w,x))return 1;
        if(check2(n,w,x))return 2;
        if(check3(n,w,x))return 3;
        return 4;
    }
}gt;