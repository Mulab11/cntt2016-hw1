#include<bits/stdc++.h>
using namespace std;
int f[1<<16][16],n,m,T,i,j,k,s,d[50][50],t[3],l[16],r[16],w[16],ans,o[1<<16];
class TravellingPurchasingMan
{
    public:
        void get(string s,int &n,int *a)
        {
            int i;
            for(n=i=0;i<s.size();n++)
            {
                for(;(s[i]<'0'||s[i]>'9')&&i<s.size();i++);
                if(i==s.size())break;
                for(a[n]=0;i<s.size()&&s[i]>='0'&&s[i]<='9';i++)a[n]=(a[n]<<3)+(a[n]<<1)+(s[i]^'0');
            }
        }
        int maxStores(int N, vector <string> interestingStores, vector <string> roads)
        {
            n=interestingStores.size();
            m=roads.size();
            memset(d,63,sizeof(d));
            memset(f,63,sizeof(f));
            for(i=0;i<N;i++)d[i][i]=0;
            for(i=0;i<n;i++)
            {
                get(interestingStores[i],T,t);
                l[i]=t[0];
                r[i]=t[1];
                w[i]=t[2];
            }
            for(i=0;i<m;i++)
            {
                get(roads[i],T,t);
                d[t[0]][t[1]]=d[t[1]][t[0]]=min(d[t[0]][t[1]],t[2]);
            }
            for(k=0;k<N;k++)for(i=0;i<N;i++)for(j=0;j<N;j++)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            for(i=0;i<n;i++)f[0][i]=d[N-1][i];
            for(i=1;i<1<<n;i++)for(o[i]=o[i>>1]+(i&1),j=0;j<n;j++)
            {
                for(k=0;k<n;k++)if((i>>k&1)&&f[i^(1<<k)][k]<=r[k])f[i][j]=min(f[i][j],max(f[i^(1<<k)][k],l[k])+w[k]+d[k][j]);
                if(f[i][j]<1000000000)ans=max(ans,o[i]);
            }
            return ans;
        }
};
