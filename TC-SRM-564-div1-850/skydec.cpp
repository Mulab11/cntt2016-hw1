#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int a[N],n,S;
int f[N][2][2];
int Main(){
    int ans=0;
    per(i,29,0){
        //枚举第i位时有某个数实际的值不等于上界
        //因为这样的话那个后在后面i-1位的值是任意选的，所以后面i-1位的异或值是可控的
        //于是剩下n-1个数后面i-1位就可以乱选了，留一个不等于上界的最后来校准即可
        memset(f,0,sizeof f);
        f[0][0][0]=1;
        //f[i][j][k]表示dp了第i个，异或为j，k表示是否有实际值不等于上界的
        rep(j,0,n-1)rep(bit,0,1)rep(hav,0,1){
            int w=((a[j+1]&(1<<i))>0);
            int ret=f[j][bit][hav];
            //如果上界是1，那么可以选实际值位0，那么hav就|=1
            //且由于这里上界和实际值不同了，后面i-1位随便选，方案数就是2^i
            if(w)add(f[j+1][bit][1],ret*1ll*(i>0?Pow(2,i):1)%P);
            //直接无脑选上界，方案数是a[j+1]的后面i-1位的值
            add(f[j+1][bit^w][hav],ret*1ll*((a[j+1]&((1<<i)-1))+1)%P);
        }
        int d=((S&(1<<i))>0);
        //注意要除掉一个，因为有一个是留着校准的，不能乱动
        add(ans,f[n][d][1]*1ll*(i>0?Pow(Pow(2,i),P-2):1)%P);
        int c=0;
        //接下来要考虑i-1位了，所以要check下第i位全选上界是否满足条件
        rep(j,1,n)c^=((a[j]&(1<<i))>0);
        if(c^d)break;
        //还需要考虑全部每一位都选上界的情况
        if((c==d)&&(i==0))add(ans,1);
    }
    return ans;
}
class DefectiveAddition{
public:
    int count(vector<int> cards, int S){
        //预处理
        n=cards.size();
        rep(i,1,n)a[i]=cards[i-1];
        ::S=S;
        return Main();
    }
}gt;




