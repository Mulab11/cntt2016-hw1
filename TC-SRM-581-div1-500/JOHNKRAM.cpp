#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,f1[305],f2[305],a1[305],a2[305],d1[305][305],d2[305][305];
double ans;
class TreeUnion
{
    public:
        void get(vector<string> x,int &n,int *a)
        {
            string s="";
            int i=0;
            for(;i<x.size();i++)s+=x[i];
            for(n=i=0;i<s.size();)
            {
                for(;(s[i]<'0'||s[i]>'9')&&i<s.size();i++);
                if(i==s.size())break;
                for(a[++n]=0;i<s.size()&&s[i]>='0'&&s[i]<='9';i++)a[n]=(a[n]<<3)+(a[n]<<1)+(s[i]^'0');
            }
        }
        double expectedCycles(vector <string> tree1, vector <string> tree2, int K)
        {
            K-=2;
            get(tree1,n,f1);
            get(tree2,n,f2);
            memset(d1,63,sizeof(d1));
            memset(d2,63,sizeof(d2));
            for(i=0;i<=n;i++)d1[i][i]=d2[i][i]=0;
            for(i=1;i<=n;i++)d1[f1[i]][i]=d1[i][f1[i]]=d2[f2[i]][i]=d2[i][f2[i]]=1;
            for(k=0;k<=n;k++)for(i=0;i<=n;i++)for(j=0;j<=n;j++)
            {
                d1[i][j]=min(d1[i][j],d1[i][k]+d1[k][j]);
                d2[i][j]=min(d2[i][j],d2[i][k]+d2[k][j]);
            }
            for(i=0;i<=n;i++)for(j=0;j<=n;j++)
            {
                a1[d1[i][j]]++;
                a2[d2[i][j]]++;
            }
            for(i=1;i<K;i++)ans+=0.5*a1[i]*a2[K-i];
            return ans/n/(n+1);
        }
};

