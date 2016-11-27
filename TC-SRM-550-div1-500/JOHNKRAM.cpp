#include<bits/stdc++.h>
using namespace std;
vector<string> ans;
class CheckerExpansion
{
    public:
        vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h)
        {
            string s;
            int i,j;
            for(j=h-1;~j;j--,ans.push_back(s))for(i=0,s="";i<w;i++)if(x0+i+y0+j>=(t<<1)||((x0^i^y0^j)&1)||((x0+i+y0+j>>1)&y0+j)!=y0+j)s+='.';//判断有没有检验器 
            else if((x0+i+y0+j)&3)s+='B';//判断是不是B检验器 
            else s+='A';
            return ans;
        }
};
