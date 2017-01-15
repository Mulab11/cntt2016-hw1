#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
struct gt{
    int w;
    LL num;
};
inline bool cmp(const gt &a,const gt &b){return a.w<b.w;}
const int N=55;
int a[N];gt b[N];
int n,m;
bool check(LL t){
    if(a[n]<b[m].w)return 0;
    int r=n;
    LL rest=0;
    per(i,m,1){
        while(r>=1&&a[r]>=b[i].w){
            r--;rest+=t;
        }
        if(rest<b[i].num)return 0;
        rest-=b[i].num;
    }
    return 1;
}
LL Main(){
    sort(a+1,a+1+n);
    sort(b+1,b+1+m,cmp);

    LL l=0;LL r=(LL)1e16;
    LL ans=-1;
    while(l<r){
        LL mid=(l+r)>>1;
        if(check(mid))ans=mid,r=mid;
        else l=mid+1;
    }
    if(check(l))ans=l;
    return ans;
}
class SpaceWarDiv1{
public:
    LL minimalFatigue(vector <int> a, vector <int> b, vector<long long> c){
        n=a.size();rep(i,1,n)::a[i]=a[i-1];
        m=b.size();rep(i,1,m){::b[i].w=b[i-1];::b[i].num=c[i-1];}
        return Main();
    }
};