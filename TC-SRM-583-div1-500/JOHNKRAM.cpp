#include<bits/stdc++.h>
using namespace std;
int n,i,ans;
bool b[55],x;
class TurnOnLamps
{
    public:
        int minimize(vector <int> roads, string initState, string isImportant)
        {
            n=roads.size();
            for(i=n;i;i--)if(isImportant[i-1]=='0')b[roads[i-1]]^=b[i];
            else
            {
                x=initState[i-1]=='0';
                if(x!=b[i])ans++;
                b[roads[i-1]]^=x;
            }
            return ans+1>>1;
        }
};
