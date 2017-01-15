#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=1010000;
LL res[N];
LL tmp[N];
LL bb[N];
int cnt[N];
void calc(int m,int p,int r){
    rep(i,0,m-1)tmp[i]=(1ll<<60)-1;
    memset(cnt,0,sizeof cnt);

    for(int k=0;k<p*r;k++){
        LL k2=k*1ll*k;
        for(int i=(k2%m)%p;i<m;i+=p)if(cnt[i]<r){
            LL w=((i-k2)%m+m)%m;
            if(w==0)cnt[i]=r;
            else{
                while(w%p==0){
                    w/=p;cnt[i]++;
                }
            }
            if(cnt[i]>=r)tmp[i]=k2+1;
        }
    }
}
void merge(LL *A,int len1,LL *B,int len2){
    rep(i,0,len1*len2-1)bb[i]=max(A[i%len1],B[i%len2]);
}
class SparseFactorial{
public:
    LL getCount(long long l, long long r, long long m){
        int len=1;
        rep(i,2,m)if(m%i==0){
            int rr=0;
            LL x=1;
            while(m%i==0){
                m/=i;
                rr++;
                x*=i;
            }
            calc(x,i,rr);
            merge(tmp,x,res,len);
            rep(j,0,len*x-1)res[j]=bb[j];
            len*=x;
        }

        LL ans=0;
        rep(i,0,len-1)if(res[i]<=r){
            LL lp=max(res[i]-1,l-1);
            ans+=(r-i+len)/len-(lp-i+len)/len;
        }
        return ans;
    }
}gt;