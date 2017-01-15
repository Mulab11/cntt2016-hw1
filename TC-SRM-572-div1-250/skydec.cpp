#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int fa[N];int n,k;
int a[N];
int get(int x){if(x==fa[x])return x;return fa[x]=get(fa[x]);}
int cnt[N];
int Main(){
    //用并查集的方式求出哪些字符一定要相同
    rep(i,1,n)fa[i]=i;
    rep(i,1,k){
        fa[get(i)]=get(n-k+i);
    }
    int ans=0;
    rep(i,1,n)if(fa[i]==i){
        //对于每个联通块计算答案
        memset(cnt,0,sizeof cnt);
        int all=0;
        rep(j,1,n)if(get(j)==i){
            cnt[a[j]]++;
            ++all;
        }
        //找出不用改变的那个字符，一定是出现次数最多的
        int ret=0;
        rep(j,0,25)if(cnt[j]>ret)ret=cnt[j];
        ans+=all-ret;
    }
    return ans;
}
class NewArenaPassword{
public:
    int minChange(string oldPassword, int K){
        //预处理
        n=oldPassword.size();
        rep(i,1,n){
            a[i]=oldPassword[i-1]-'a';
        }
        k=K;
        return Main();
    }
};




