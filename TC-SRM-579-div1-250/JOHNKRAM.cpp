#include<bits/stdc++.h>
using namespace std;
int lcp(string x,string y)
{
    int i=0;
    for(;i<x.size()&&i<y.size()&&x[i]==y[i];i++);
    return i;
}
int i,j,k,ans;
class UndoHistory
{
    public:
        int minPresses(vector <string> lines)
        {
            for(ans=lines[0].size()+lines.size(),i=1;i<lines.size();i++)
            {
                if(lcp(lines[i],lines[i-1])==lines[i-1].size())k=lines[i-1].size()+2;
                else k=0;
                for(j=0;j<i;j++)k=max(k,lcp(lines[i],lines[j]));
                ans+=lines[i].size()-k+2;
            }
            return ans;
        }
};
