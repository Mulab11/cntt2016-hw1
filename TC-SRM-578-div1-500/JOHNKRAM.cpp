#include<bits/stdc++.h>
using namespace std;
#define P 1000000007
int n,m,i,j,k,o,l[305],r[305],f[305][305],ans;
class WolfInZooDivOne
{
    public:
        void get(vector<string> x,int &n,int *a)//字符串转数组 
        {
            string s="";
            int i=0;
            for(;i<x.size();i++)s+=x[i];
            for(n=i=0;i<s.size();n++)
            {
                for(;(s[i]<'0'||s[i]>'9')&&i<s.size();i++);
                if(i==s.size())break;
                for(a[n]=0;i<s.size()&&s[i]>='0'&&s[i]<='9';i++)a[n]=(a[n]<<3)+(a[n]<<1)+(s[i]^'0');
            }
        }
        int count(int N, vector <string> L, vector <string> R)
        {
            get(L,m,l);
            get(R,m,r);
            for(f[i=0][0]=1;i<=N;i++)for(j=i;j<=N;j++)//倒数第二个、倒数第一个1的位置 
            {
                ans+=f[i][j];
                if(ans>=P)ans-=P;
                for(k=0,o=j+1;k<m;k++)if(l[k]<i)o=max(o,r[k]+2);//求下一个1位置的下界 
                for(k=o;k<=N;k++)
                {
                    f[j][k]+=f[i][j];//状态转移 
                    if(f[j][k]>=P)f[j][k]-=P;
                }
            }
            return ans;
        }
};