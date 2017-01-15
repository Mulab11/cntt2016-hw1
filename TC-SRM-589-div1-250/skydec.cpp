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
int fa[N];
int get(int x){if(x==fa[x])return x;return fa[x]=get(fa[x]);}
class GooseTattarrattatDiv1{
public:
    int getmin(string S){
        int res=0;
        rep(i,0,25)fa[i]=i;
        rep(i,0,S.size()-1){
            int a=S[i]-'a';
            int b=S[S.size()-i-1]-'a';

            fa[get(a)]=get(b);
        }

        rep(i,0,25)if(get(i)==i){
            int sum=0;
            int ma=0;
            rep(j,0,25)if(get(j)==i){
                int ret=0;
                rep(k,0,S.size()-1)if(S[k]==j+'a')ret++;
                if(ret>ma)ma=ret;
                sum+=ret;
            }
            res+=sum-ma;
        }
        return res;
    }
};