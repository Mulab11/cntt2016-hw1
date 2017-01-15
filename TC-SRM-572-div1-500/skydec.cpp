#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int a[N][11],b[N];
int n,k;
string mp[10]={"0","1","2","3","4","5","6","7","8","9"};
map<vector<int>,int>ret;
//用map记录方案
int c[N];
int Main(){
    int ans=-1;
    int d=k/2;
    int pw=1;
    //用mim算法，考虑枚举前m/2个数字
    rep(i,1,d)pw*=10;
    rep(i,0,pw-1){
        vector<int>ha;ha.clear();
        int xx=i;
        //分解出数组
        per(j,d,1){
            c[j]=xx%10;
            xx/=10;
        }
        rep(j,1,n){
            //对于每个串计算出贡献，存到vector里
            int arc=0;
            rep(g,1,d)if(a[j][g]==c[g])arc++;
            ha.push_back(arc);
        }
        //存到map里
        if(ret.find(ha)!=ret.end()){
            ret[ha]=-1;
        }
        else{
            ret[ha]=i;
        }
    }
    //枚举另一半
    d=k-k/2;
    pw=1;
    rep(i,1,d)pw*=10;
    rep(i,0,pw-1){
        vector<int>ha;ha.clear();
        int xx=i;
        //把数分解成数组
        per(j,d,1){
            c[j]=xx%10;
            xx/=10;
        }
        rep(j,1,n){
            int arc=0;
            rep(g,1,d)if(a[j][g+k/2]==c[g])arc++;
            //把另一半所需要的答案存到一个vector里
            ha.push_back(b[j]-arc);
        }
        //在map中寻找，找到了的话就返回答案
        if(ret.find(ha)!=ret.end()){
            if(ret[ha]==-1)return -2;
            if(ans>=0)return -2;
            ans=ret[ha]*pw+i;
        }
    }
    return ans;
}
class EllysBulls{
public:
    string getNumber(vector <string> gue, vector <int> bulls){
        //预处理
        k=gue[0].size();
        n=gue.size();
        rep(i,1,n){
            rep(j,1,k)a[i][j]=gue[i-1][j-1]-'0';
            b[i]=bulls[i-1];
        }
        int ans=Main();
        if(ans==-1)return "Liar";
        if(ans==-2)return "Ambiguity";
        string ret="";
        rep(i,1,k){
            ret=mp[(ans%10)]+ret;
            ans/=10;
        }
        return ret;
    }
}gt;




