#include<bits/stdc++.h>
using namespace std;
int t[15],n,i,j,x[15],y[15],f[1600000],ans;
bool a[15],b[15];
int work(int N,int A,int B)//记忆化搜索 
{
    if(~f[N])return f[N];
    int i;
    if(!A)//硬币放完了 
    {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(i=0;i<n;i++)if(N/t[i]%3!=2)
        {
            a[x[i]]^=1;
            b[y[i]]^=1;
        }
        for(i=0;i<13;i++)if(a[i]||b[i])return f[N]=100;//判断是否每行每列都是偶数个 
        return f[N]=0;
    }
    if(!B)//不能再猜了 
    {
        for(i=0;i<n;i++)if(!(N/t[i]%3)&&!work(N+2*t[i],A-1,0))return f[N]=0;//判断能不能导出一组合法解 
        return f[N]=100;
    }
    for(i=0;i<n;i++)if(!(N/t[i]%3))f[N]=max(f[N],min(work(N+t[i],A,B-1),work(N+2*t[i],A-1,B-1)+1));//枚举每一个没有猜过的帽子，枚举放不放硬币 
    return f[N];
}
class MagicalHats
{
    public:
        int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses)
        {
            sort(coins.begin(),coins.end());
            for(i=t[0]=1;i<13;i++)t[i]=t[i-1]*3;
            for(i=0;i<board.size();i++)for(j=0;j<board[i].size();j++)if(board[i][j]=='H')//求出帽子的坐标 
            {
                x[n]=i;
                y[n++]=j;
            }
            memset(f,-1,sizeof(f));
            ans=work(0,coins.size(),numGuesses);//求出最多获得多少枚硬币 
            if(ans>99)return -1;
            for(i=ans-1,ans=0;i>=0;i--)ans+=coins[i];//计算答案 
            return ans;
        }
};