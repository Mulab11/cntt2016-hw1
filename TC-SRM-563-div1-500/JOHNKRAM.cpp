#include<bits/stdc++.h>
using namespace std;
int n,i,j,f[55];
class SpellCards
{
    public:
        int maxDamage(vector <int> level, vector <int> damage)
        {
            n=level.size();
            for(i=0;i<n;i++)for(j=n;j>=level[i];j--)f[j]=max(f[j],f[j-level[i]]+damage[i]);//01背包计算答案 
            return f[n];
        }
};