#include<bits/stdc++.h>
using namespace std;
#define P 1000000009
#define ll long long
#define I 440000004LL
int Pow(int x,int y)//快速幂 
{
    int s=1;
    for(;y;y>>=1,x=(ll)x*x%P)if(y&1)s=(ll)s*x%P;
    return s;
}
set<int> s;
set<int>::iterator it;
map<int,char> M;
int n,m,i,j,k,ans;
ll N;
class CharacterBoard
{
    public:
        int countGenerators(vector <string> fragment, int W, int i0, int j0)
        {
            n=fragment.size();
            m=fragment[0].size();
            for(i=0;i<n;i++)for(j=1-m;j<m;j++)for(N=(ll)W*i+j,k=1;k<=W&&(ll)k*k<=N;k++)if(N%k==0)//求所有出现重叠的L 
            {
                s.insert(k);
                if(N/k<=W)s.insert(N/k);
            }
            if(W>=n*m)ans=(Pow(26,W-n*m+1)-1)*I%P;//等比数列求和 
            for(it=s.begin();it!=s.end();it++)
            {
                M.clear();
                for(i=0;i<n;i++)for(j=0;j<m;j++)if(M.find(k=((ll)W*i+j)%(*it))==M.end())M[k]=fragment[i][j];//求有多少个位置被限制 
                else if(M[k]!=fragment[i][j])goto xxx;
                xxx:if(i==n)ans+=Pow(26,(*it)-M.size());//计算答案 
                if(*it>=n*m)ans-=Pow(26,(*it)-n*m);
                if(ans<0)ans+=P;
                if(ans>=P)ans-=P;
            }
            return ans;
        }
};