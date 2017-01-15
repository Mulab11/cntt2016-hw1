#include<bits/stdc++.h>
#define pb push_back
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=55;
int n,m;
int a[N],b[N];
int kd[N];
vector<int>q[2];
int Main(){
    int ans=-1;
    int sum[2];sum[0]=sum[1]=0;
    rep(i,1,m)sum[kd[i]]+=b[i];
    rep(i,1,m)q[kd[i]].pb(b[i]);
    //q[0]表示大的气球的个数
    //q[1]表示小的气球的个数
    rep(i,0,1){
        sort(q[i].begin(),q[i].end());
        reverse(q[i].begin(),q[i].end());
    }

    //将题目按通过人数排序
    sort(a+1,a+1+n);
    reverse(a+1,a+1+n);

    rep(S,0,(1<<n)-1){
        //枚举每道题的气球的大小
        int all[2];all[0]=all[1]=0;
        rep(i,1,n)if(S&(1<<(i-1)))all[1]+=a[i];
        else all[0]+=a[i];

        //特判下如果总和溢出则停止
        if(all[1]>sum[1])continue;
        if(all[0]>sum[0])continue;

        int st0,st1;
        st0=st1=0;
        int cost=0;
        //贪心取气球，每次尽量用个数多的颜色，如果不够的话从剩下的拿
        //而考虑题目时也是从通过多的先考虑
        //可以证明这样子做答案一定最优
        rep(i,1,n)if(S&(1<<(i-1))){
            if(st1<q[1].size()){
                //st1表示已经取到哪里
                if(a[i]>q[1][st1])cost+=a[i]-q[1][st1];
                st1++;
            }
            else cost+=a[i];
            //因为已经check过总和了，所以不需要再记剩下的有多少了
        }
        else{
            if(st0<q[0].size()){
                if(a[i]>q[0][st0])cost+=a[i]-q[0][st0];
                st0++;
            }
            else cost+=a[i];
        }
        //更新答案
        //ans=-1表示还没有任何方案
        if((ans==-1)||(cost<ans))ans=cost;
    }
    return ans;
}
class ICPCBalloons{
public:
    int minRepaintings(vector<int>hav, string kd, vector<int>need){
        //预处理
        m=hav.size();
        n=need.size();
        rep(i,1,n){
            a[i]=need[i-1];
        }
        rep(i,1,m){
            b[i]=hav[i-1];
            ::kd[i]=(kd[i-1]=='M');
        }
        return Main();
    }
};

