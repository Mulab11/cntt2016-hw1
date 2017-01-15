#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=2010000;
char a[N];int n;
const int P=1000000007;
int sumw[N],sumo[N];
int sum(int *A,int l,int r){if(!l)return A[r];return (A[r]-A[l-1]+P)%P;}
int f[N];
int sumf[N];
bool check(int l,int r){
    if((r-l+1)&1)return 0;
    int mid=(l+r)>>1;
    if(sum(sumo,l,mid)||sum(sumw,mid+1,r))return 0;
    return 1;
}
int pre[N];
int prew[N];
struct lex{
    int l,r;
    lex(int _l,int _r){l=_l;r=_r;}
};
inline bool operator <(const lex &a,const lex &b){if(a.r*2-a.l!=b.r*2-b.l)return a.r*2-a.l<b.r*2-b.l;return a.l<b.l;}
set<lex> now;
int Main(){
    rep(i,1,n)sumw[i]=sumw[i-1]+(a[i]=='w');
    rep(i,1,n)sumo[i]=sumo[i-1]+(a[i]=='o');
    f[0]=1;sumf[0]=1;
    sumf[1]=1;
    int fi=0;
    rep(i,1,n){
        pre[i]=fi;
        if(a[i]=='o')fi=i;
    }
    fi=0;
    rep(i,1,n){
        if(a[i]=='w')fi=i;
        prew[i]=fi;
    }
    for(int i=2;i<=n;i+=2){
        //if(i%100000==0)printf("%d\n",now.size());
        if(a[i-1]=='w'||a[i]=='w'){
            now.clear();
            if(a[i]=='w'){
                now.insert(lex(pre[i]+1,i));
            }
            else if(a[i-1]=='w'){
                if(a[i]!='o')now.insert(lex(pre[i-1]+1,i));
                else now.insert(lex(pre[i-1]+1,i-1));
            }
        }
        else{
            if(a[i-1]=='o'&&a[i]=='?')now.insert(lex(i,i));
            if(a[i-1]=='?'){
                if(!(i==2||a[i-2]=='o')){
                    lex uu=*now.find(lex(pre[i-1]+1,i-2));
                    now.erase(uu);
                    if(a[i]=='?')uu.r=i;else uu.r=i-1;
                    now.insert(uu);
                }
                else{
                    if(a[i]=='?')now.insert(lex(i-1,i));
                    else now.insert(lex(i-1,i-1));
                }
            }
        }
        rep(calcproduce,1,1){
            set<lex>::iterator it=now.end();
            if(it==now.begin())continue;
            it--;
            int cnt=0;
            while(1){
                if(2*it->r-it->l>=i-1){
                    int L,R;L=it->l;
                    R=2*it->r-i+1;
                    if(it->r<R)R=it->r;
                    if(sum(sumw,it->l,it->r)){
                        int mid=prew[it->r];
                        int xx=2*mid-i+1;
                        if(xx>L)L=xx;
                    }
                    if(L<=R){
                        f[i]=(f[i]+sum(sumf,L-1,R-1))%P;
                    }
                    if(it==now.begin())break;
                    --it;
                }
                else{
                    if(it->r!=i-2){
                        if(it==now.begin()){now.erase(now.begin());break;}
                        set<lex>::iterator tt=it;
                        --tt;
                        lex gg=*tt;
                        now.erase(it);
                        it=now.find(gg);
                    }
                    else{
                        if(it==now.begin())break;
                        --it;
                    }
                }
            }
        }
        sumf[i]=sumf[i+1]=(sumf[i-2]+f[i])%P;
    }
    return f[n];
}
class WolfDelaymasterHard{
    public:
    int countWords(int N,int wlen,int w0,int wmul,int wadd,int olen,int o0,int omul,int oadd){
        if(N&1)return 0;
        n=N;
        rep(i,1,n)a[i]='?';
        int x=w0;
        rep(i,0,wlen-1){
            a[x+1]='w';
            x=(x*1ll*wmul+wadd)%n;
        }
        x=o0;
        rep(i,0,olen-1){
            a[x+1]='o';
            x=(x*1ll*omul+oadd)%n;
        }
        return Main();
    }
}gt;