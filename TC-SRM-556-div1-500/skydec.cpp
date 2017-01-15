#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<string>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=55;
struct huge{
    //高精度类
    int a[N];
    void init(){memset(a,0,sizeof a);}
    void set(int x,int y){
        a[x]=y;
    }
};
int n;
inline bool operator <(const huge &a,const huge &b){
    //比较两个高精度数的值
    rep(i,1,n)if(a.a[i]!=b.a[i])
    return a.a[i]<b.a[i];
    return 0;
}
int num[N];
int a[N];
bool same(){
    bool f[N][N];
    //f[i][j]表示当前是否可存在一种方案放满了[i,j]，且[i,j]和lowerBound相同
    memset(f,0,sizeof f);
    rep(i,1,n)if(num[i]==a[n])f[i][i]=1;
    rep(l,1,n-1){
        rep(i,1,n-l+1){
            int j=i+l-1;
            if(!f[i][j])continue;
            //我们很容易知道下一个要放的数啥，枚举放在左边或者右边
            if(j<n&&num[j+1]==a[n-l])f[i][j+1]=1;
            if(i>1&&num[i-1]==a[n-l])f[i-1][j]=1;
        }
    }
    return f[1][n];
}
huge f[N][N];
bool arr[N][N];
string check(int st){
    memset(arr,0,sizeof arr);
    rep(i,1,n)rep(j,1,n)f[i][j].init();
    //arr[i][j]表示[i,j]是否可以放满
    //f[i][j]表示方案
    rep(i,1,n)if((i<st&&num[i]==a[n])||(i==st&&num[i]<a[n])||(i>st)){
        //初始化
        //根据我们枚举的前缀，[1,st-1]和lowerbound一样
        //[st,st]比lowerbound大
        //[st+1,n]随便放
        arr[i][i]=1;
        f[i][i].set(i,a[n]);
    }
    rep(l,1,n-1){
        rep(i,1,n-l+1){
            int j=i+l-1;
            if(!arr[i][j])continue;
            //考虑区间dp，再枚举下一个数放到左边还是右边
            //特判一下是否成立，再用字典序比较方案即可
            if(j<n)if((j+1<st&&num[j+1]==a[n-l])||(j+1==st&&num[j+1]<a[n-l])||(j+1>st)){
                huge bb=f[i][j];
                bb.set(j+1,a[n-l]);
                if((!arr[i][j+1])||(bb<f[i][j+1])){
                    f[i][j+1]=bb;
                    arr[i][j+1]=1;
                }
            }
            if(i>1)if((i-1<st&&num[i-1]==a[n-l])||(i-1==st&&num[i-1]<a[n-l])||(i-1>st)){
                huge bb=f[i][j];
                bb.set(i-1,a[n-l]);
                if((!arr[i-1][j])||(bb<f[i-1][j])){
                    f[i-1][j]=bb;
                    arr[i-1][j]=1;
                }
            }
        }
    }
    if(!arr[1][n])return "";
    string ans="";
    rep(i,1,n)ans=ans+(char)('0'+f[1][n].a[i]);
    return ans;
}
string Main(){
    if(same()){
        //如果给定的字符串可以重组成lowerBound，那直接返回lowerBound
        string ans="";
        rep(i,1,n)ans=ans+(char)('0'+num[i]);
        return ans;
    }
    per(i,n,1){
        //枚举答案和lowerBound在[1,i-1]上一样
        //且答案的第i位大于lowerBound
        string ans=check(i);
        if(ans.size()>=1)return ans;
    }
    return "";
}
class LeftRightDigitsGame2{
public:
    string minNumber(string digits, string lowerBound){
        //预处理
        n=digits.size();
        rep(i,1,n){
            num[i]=lowerBound[i-1]-'0';
            a[i]=digits[i-1]-'0';
        }
        reverse(a+1,a+1+n);
        return Main();
    }
};



