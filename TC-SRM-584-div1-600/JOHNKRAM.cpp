#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll f[55][55],c[55][55],ans;
int n,m,N,i,j,k,l;
bool b[55];
vector<int> d[55];
class Excavations
{
    public:
        long long count(vector <int> kind, vector <int> depth, vector <int> found, int K)
        {
            n=kind.size();
            m=found.size();
            if(K<m)return 0;
            for(i=c[0][0]=1;i<=n;i++)for(j=c[i][0]=1;j<=i;j++)c[i][j]=c[i-1][j]+c[i-1][j-1];
            for(i=0;i<m;i++)
            {
                b[found[i]]=1;
                for(j=0;j<n;j++)if(kind[j]==found[i])d[found[i]].pb(depth[j]);
                sort(d[found[i]].begin(),d[found[i]].end());
            }
            for(i=0;i<n;i++)if(!b[kind[i]])d[0].pb(depth[i]);
            sort(d[0].begin(),d[0].end());
            N=d[0].size();
            d[0].pb(1000000000);
            for(i=0;i<=N;i++)
            {
                memset(f,0,sizeof(f));
                for(f[j=0][max(N-1-i,0)]=1;j<m;j++)for(k=0;k<=n;k++)for(l=0;l<d[found[j]].size();l++)if(d[found[j]][l]<d[0][i])f[j+1][k+d[found[j]].size()-1-l]+=f[j][k];
                for(j=0;j<=n;j++)ans+=f[m][j]*c[j][K-m-(i!=N)];
            }
            return ans;
        }
};
