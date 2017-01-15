#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<assert.h>
#include<map>
#include<string>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int P=1000000009;
inline int Pow(int a,LL b){
    //快速幂
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
int px,py;
int n,m;
char str[15][15];
int A,B;
vector<LL>spj;
map<LL,char>mp;
int test(LL len){
    mp.clear();LL rest=len;
    rep(i,1,A)rep(j,1,B){
        LL pos=(i+px-1)*1ll*m+j+py;
        pos%=len;
        //因为已知长度，可以知道哪些位置是哪些数
        //顺便判断下合法性
        if(mp.find(pos)!=mp.end()){
            if(mp[pos]!=str[i][j])return 0;
        }
        else{
            mp[pos]=str[i][j];rest--;
        }
    }
    //剩下rest个随便填，答案是26^rest
    return Pow(26,rest);
}
int get(LL r){
    //(26^(r+1)-1)/25
    if(r<0)return 0;
    int ans=(Pow(26,r+1)+P-1)%P;
    ans=ans*1ll*Pow(25,P-2)%P;
    return ans;
}
int calc(LL l,LL r){
    //26^(l-A*B)~26^(r-A*B)
    l-=A*B;r-=A*B;
    assert(l>=0);
    assert(r>=0);
    return (get(r)+P-get(l-1))%P;
}
int Main(){
    rep(i,1,A)rep(j,-B,B)if(!(i==1&&j==1)){
        //先处理出所有的间隔
        LL jian=(i-1)*1ll*m+j;
        if(jian<=0)continue;
        for(LL k=1;k*k<=jian;k++)if(jian%k==0){
            //筛出该间隔的所有约数，用来方便后面的计算
            if(k<=m)
            spj.push_back(k);
            if(jian/k<=m)
            spj.push_back(jian/k);
        }
    }
    spj.push_back(1);spj.push_back(m);
    sort(spj.begin(),spj.end());
    LL pre=0;
    int ans=0;
    for(vector<LL>::iterator it=spj.begin();it!=spj.end();it++){
        //枚举所有约数作为长度
        LL v=*it;
        if(v==pre)continue;
        ans=(ans+test(v))%P;
        //对于那些不是任何间隔的约数的点，没有点会共用位置
        //所以等比数列求和爆算即可
        if(pre+1<=v-1)ans=(ans+calc(pre+1,v-1))%P;
        pre=v;
    }
    return ans;
}
class CharacterBoard{
    public:
    int countGenerators(vector<string> fra,int W,int i0,int j0){
        //预处理
        n=1000000000;
        m=W;
        px=i0;py=j0;
        A=fra.size();B=fra[0].size();
        rep(i,1,A)rep(j,1,B)str[i][j]=fra[i-1][j-1];
        return Main();
    }
};


