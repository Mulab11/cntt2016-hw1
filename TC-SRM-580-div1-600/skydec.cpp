#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=2600;
int l[N],r[N];
int n;
int cant=0;
int gua[10005];
int calc(int S){
    int ma=-1;
    
    int qul=1e9;
    int qur=-1;
    //初始化当前的l和当前的r
    rep(i,1,n){
        qul=min(qul,r[i]);
        qur=max(qur,l[i]);
    }
    int ans=0;
    rep(i,0,qul)ma=max(ma,gua[i]);
    while(qul<qur){
        //一直扩展，直到qul和qur足够为止
        if(qul>=l[S]&&r[S]>qul){
            //每次扩展
            rep(i,qul,r[S])ma=max(ma,gua[i]);
            qul=r[S];
            continue;
        }
        if(ma<=qul){
            cant=1;
            return 0;
        }
        
        ans++;
        int d=ma;
        rep(i,qul,d){
            ma=max(ma,gua[i]);
        }
        qul=d;
    }
    return ans;
}
int Main(){
    //相当于区间覆盖
    rep(i,1,n)gua[l[i]]=max(gua[l[i]],r[i]);
    int ans=0;
    //计算答案
    rep(i,1,n)ans+=calc(i);
    if(cant)return -1;
    return ans;
}
class ShoutterDiv1{
public:
    int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1){
        //将他令人蛋疼的读入格式转化一下
        string _s1000="";
        rep(i,0,s1000.size()-1)_s1000=_s1000+s1000[i];
        string _s100="";
        rep(i,0,s100.size()-1)_s100=_s100+s100[i];
        string _s10="";
        rep(i,0,s10.size()-1)_s10=_s10+s10[i];
        string _s1="";
        rep(i,0,s1.size()-1)_s1=_s1+s1[i];
        n=_s1.size();
        rep(i,1,n){
            l[i]=(_s1000[i-1]-'0')*1000;
            l[i]+=(_s100[i-1]-'0')*100;
            l[i]+=(_s10[i-1]-'0')*10;
            l[i]+=(_s1[i-1]-'0');
        }


        string _t1000="";
        rep(i,0,t1000.size()-1)_t1000=_t1000+t1000[i];
        string _t100="";
        rep(i,0,t100.size()-1)_t100=_t100+t100[i];
        string _t10="";
        rep(i,0,t10.size()-1)_t10=_t10+t10[i];
        string _t1="";
        rep(i,0,t1.size()-1)_t1=_t1+t1[i];

        rep(i,1,n){
            r[i]=(_t1000[i-1]-'0')*1000;
            r[i]+=(_t100[i-1]-'0')*100;
            r[i]+=(_t10[i-1]-'0')*10;
            r[i]+=(_t1[i-1]-'0');
        }

        return Main();
    }
};



