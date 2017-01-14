#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define ll long long
#define pil pair<int,ll>
int n,m,i,j;
ll ans,s;
vector<pil> a;
class SpaceWarDiv1
{
    public:
        long long minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<long long> enemyCount)
        {
            n=magicalGirlStrength.size();
            m=enemyStrength.size();
            for(i=0;i<m;i++)a.pb(mp(enemyStrength[i],enemyCount[i]));
            sort(magicalGirlStrength.begin(),magicalGirlStrength.end());
            sort(a.begin(),a.end());
            if(magicalGirlStrength[n-1]<a[m-1].first)return -1;
            for(i=m-1,j=n-1;~i;ans=max(ans,(s+n-2-j)/(n-1-j)),i--)for(s+=a[i].second;~j&&magicalGirlStrength[j]>=a[i].first;j--);
            return ans;
        }
};
