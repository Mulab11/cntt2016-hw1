#include<bits/stdc++.h>
using namespace std;
int n,i,a[55],b[55],x[55],y[55],u,v;
class FoxAndChess
{
    public:
        string ableToMove(string begin, string target)
        {
            n=begin.size();
            for(i=0;i<n;i++)
            {
                if(begin[i]!='.')
                {
                    b[u]=i;
                    a[u++]=begin[i]=='R';
                }
                if(target[i]!='.')
                {
                    y[v]=i;
                    x[v++]=target[i]=='R';
                }
            }
            if(u!=v)return "Impossible";
            for(i=0;i<u;i++)if(a[i]!=x[i]||!a[i]&&b[i]<y[i]||a[i]&&b[i]>y[i])return "Impossible";
            return "Possible";
        }
};
