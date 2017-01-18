#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,s,G,f[4096][131],ans;
class KeyDungeonDiv1
{
    public:
        int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys)
        {
            n=doorR.size();
            memset(f,-1,sizeof(f));
            f[0][keys[0]]=keys[2];
            for(i=0;i<1<<n;i++)
            {
                for(j=0,s=keys[0]+keys[1]+keys[2];j<n;j++)if(i>>j&1)s+=roomR[j]+roomG[j]+roomW[j]-doorR[j]-doorG[j];
                for(j=0;j<131;j++)if(~f[i][j])
                {
                    G=s-j-f[i][j];
                    if(G<0)continue;
                    ans=max(ans,s);
                    for(k=0;k<n;k++)if(!(i>>k&1)&&s>=doorR[k]+doorG[k]&&G+f[i][j]>=doorG[k]&&j+f[i][j]>=doorR[k])f[i|1<<k][max(0,j-doorR[k])+roomR[k]]=max(f[i|1<<k][max(0,j-doorR[k])+roomR[k]],f[i][j]+roomW[k]-max(doorR[k]-j,0)-max(doorG[k]-G,0));
                }
            }
            return ans;
        }
};
