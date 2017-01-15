#include<bits/stdc++.h>
#define pb push_back
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int P=1000000009;
const int N=55;
int disA[N],disB[N],disC[N];
int n;
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline bool equ(int a,int b,int c){return (a==b)&&(b==c);}
inline bool cmpA(const int &a,const int &b){return disA[a]<disA[b];}
inline bool cmpB(const int &a,const int &b){return disB[a]<disB[b];}
inline bool cmpC(const int &a,const int &b){return disC[a]<disC[b];}
bool vis[N];
int q[N];
int Triple(){
    int mi=1;
    //显然三点之和最小的就是三个点的LCA
    //以他作为根，就很好做了
    rep(i,2,n)if(disA[i]+disB[i]+disC[i]<disA[mi]+disB[mi]+disC[mi]){
        mi=i;
    }
    int rt=mi;

    int AB=disA[rt]+disB[rt];
    int AC=disA[rt]+disC[rt];
    int BC=disB[rt]+disC[rt];

    vector<int>mA,mB,mC;
    mA.clear();mB.clear();mC.clear();
    memset(vis,0,sizeof vis);
    //下面跟check函数里差不多
    rep(i,1,n)if(i^rt){
        if(disA[i]+disB[i]==AB)if(disA[i]+disC[i]==AC){
            mA.push_back(i);
            if(disA[i]>=disA[rt])return 0;
            if(vis[i])return 0;
            vis[i]=1;
        }
        if(disA[i]+disB[i]==AB)if(disB[i]+disC[i]==BC){
            mB.push_back(i);
            if(disB[i]>=disB[rt])return 0;
            if(vis[i])return 0;
            vis[i]=1;
        }
        if(disA[i]+disC[i]==AC)if(disB[i]+disC[i]==BC){
            mC.push_back(i);
            if(disC[i]>=disC[rt])return 0;
            if(vis[i])return 0;
            vis[i]=1;
        }
    }
    //mA表示在Root-A上的点
    //mB表示在Root-B上的点
    //mC表示在Root-C上的点
    sort(mA.begin(),mA.end(),cmpA);
    sort(mB.begin(),mB.end(),cmpB);
    sort(mC.begin(),mC.end(),cmpC);

    //有两个点dis一样则无解
    if(mA.size()>=2)rep(i,0,mA.size()-2)if(disA[mA[i]]==disA[mA[i+1]])return 0;
    if(mB.size()>=2)rep(i,0,mB.size()-2)if(disB[mB[i]]==disB[mB[i+1]])return 0;
    if(mC.size()>=2)rep(i,0,mC.size()-2)if(disC[mC[i]]==disC[mC[i+1]])return 0;

    //dis的范围不对则无解
    rep(i,0,mA.size()-1)if((disA[mA[i]]<=0)||(disA[mA[i]]>=disA[rt]))return 0;
    rep(i,0,mB.size()-1)if((disB[mB[i]]<=0)||(disB[mB[i]]>=disB[rt]))return 0;
    rep(i,0,mC.size()-1)if((disC[mC[i]]<=0)||(disC[mC[i]]>=disC[rt]))return 0;

    rep(i,1,n)q[i]=i;
    sort(q+1,q+1+n,cmpA);
    int ans=1;
    rep(i,1,n)if((!vis[q[i]])&&(q[i]!=rt)){
        int ret=0;
        //给每个点定父亲
        rep(j,1,i-1)if(disA[q[i]]>disA[q[j]])if(equ(disA[q[i]]-disA[q[j]],disB[q[i]]-disB[q[j]],disC[q[i]]-disC[q[j]])){
            ret++;
        }
        if(equ(disA[q[i]],disB[q[i]]-AB,disC[q[i]]-AC))ret++;
        if(equ(disB[q[i]],disA[q[i]]-AB,disC[q[i]]-BC))ret++;
        if(equ(disC[q[i]],disA[q[i]]-AC,disB[q[i]]-BC))ret++;
        ans=ans*1ll*ret%P;
    }
    return ans;
}
int check(int AB,int AC){
    //传入AB和AC的距离，求方案数
    if(AB==0)return 0;
    if(AC==0)return 0;
    vector<int>mB,mC;
    mB.clear();mC.clear();
    //mB表示在AB上的点
    //mC表示在AC上的点
    memset(vis,0,sizeof vis);
    rep(i,1,n){
        if(disA[i]+disB[i]==AB){
            mB.push_back(i);
            //check一下和C的距离是否和合法
            if(disC[i]!=AC+disA[i])return 0;
            if(vis[i])return 0;
            vis[i]=1;
        }
        if(disA[i]+disC[i]==AC){
            mC.push_back(i);
            //check一下和B的距离是否也合法
            if(disB[i]!=AB+disA[i])return 0;
            if(vis[i])return 0;
            vis[i]=1;
        }
    }
    //按DisA排序一下
    sort(mB.begin(),mB.end(),cmpA);
    sort(mC.begin(),mC.end(),cmpA);
    //现在DisA是根，可以发现如果他们深度一样，又由于在一条链上，答案肯定为0
    if(mB.size()>1)rep(i,0,mB.size()-2)if(disA[mB[i]]==disA[mB[i+1]])return 0;
    if(mC.size()>1)rep(i,0,mC.size()-2)if(disA[mC[i]]==disA[mC[i+1]])return 0;
    //disA不能等于AB
    rep(i,0,mB.size()-1)if(disA[mB[i]]==AB)return 0;
    rep(i,0,mC.size()-1)if(disA[mC[i]]==AC)return 0;

    rep(i,1,n)q[i]=i;
    sort(q+1,q+1+n,cmpA);
    int ans=1;
    rep(i,1,n)if(!vis[q[i]]){
        //每个点可以挂在这一条链上的某个点上
        //显然DisA,DisB,DisC都会增加这个边权的值
        //所以只要给每个点定父亲即可
        int ret=0;
        rep(j,1,i-1)if(disA[q[i]]>disA[q[j]])
        if(equ(disA[q[i]]-disA[q[j]],disB[q[i]]-disB[q[j]],disC[q[i]]-disC[q[j]]))ret++;
        //还要考虑下挂在ABC三个点上的情况
        if(equ(disA[q[i]],disB[q[i]]-AB,disC[q[i]]-AC))ret++;
        if(equ(disB[q[i]],disA[q[i]]-AB,disC[q[i]]-AC-AB))ret++;
        if(equ(disC[q[i]],disA[q[i]]-AC,disB[q[i]]-AC-AB))ret++;
        ans=ans*1ll*ret%P;
    }
    return ans;
}
int Link(int *djB,int *djA,int *djC){
    int ans=0;
    rep(i,1,n){
        disA[i]=djA[i];
        disB[i]=djB[i];
        disC[i]=djC[i];
    }
    vector<int>AB,AC;
    AB.clear();
    AC.clear();

    //考虑DisA+DisB最小的点，可以发现显然在链AB上
    //但是如果A和B相邻的话，那所有点的DisA-DisB应该一样，而且就是DisA-DisB=AB
    {
        int ma=-(1e9);
        int mi=1e9;
        rep(i,1,n){
            ma=max(ma,abs(disA[i]-disB[i]));
            mi=min(mi,abs(disA[i]-disB[i]));
        }
        if(ma==mi){
            //判断DisA-DisB是否都一样
            AB.push_back(ma);
        }
        {
            int ABA=1e9;
            rep(i,1,n)ABA=min(ABA,disA[i]+disB[i]);
            AB.push_back(ABA);
        }
    }
    //和上一步同理
    {
        int ma=-(1e9);
        int mi=1e9;
        rep(i,1,n){
            ma=max(ma,abs(disA[i]-disC[i]));
            mi=min(mi,abs(disA[i]-disC[i]));
        }
        if(ma==mi){
            AC.push_back(ma);
        }
        {
            int ACA=1e9;
            rep(i,1,n)ACA=min(ACA,disA[i]+disC[i]);
            AC.push_back(ACA);
        }
    }
    //传进去Check一下，先不管合法性
    rep(i,0,AB.size()-1)rep(j,0,AC.size()-1)add(ans,check(AB[i],AC[j]));
    return ans;
}
int bA[N],bB[N],bC[N];
int Main(){
    rep(i,1,n){
        bA[i]=disA[i];
        bB[i]=disB[i];
        bC[i]=disC[i];
    }
    int ans=0;
    //有两种情况，三个点是链或者不是
    add(ans,Triple());
    //三个点是链，枚举中间点
    add(ans,Link(bA,bB,bC));
    add(ans,Link(bB,bA,bC));
    add(ans,Link(bA,bC,bB));
    return ans;
}
class UnknownTree{
public:
    int getCount(vector <int> disA, vector <int> disB, vector <int> disC){
        //预处理
        n=disA.size();
        rep(i,1,n){
            ::disA[i]=disA[i-1];
            ::disB[i]=disB[i-1];
            ::disC[i]=disC[i-1];
        }
        return Main();
    }
}gt;



