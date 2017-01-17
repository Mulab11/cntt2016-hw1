#include<bits/stdc++.h>
using namespace std;
map<int,int> m;
map<int,int>::iterator it;
int n,i,j;
class PiecewiseLinearFunction
{
    public:
        int maximumSolutions(vector <int> Y)
        {
            n=Y.size();
            for(i=0;i<n;i++)
            {
                j=0;
                if(i)
                {
                    if(Y[i]==Y[i-1])return -1;
                    if(Y[i]<Y[i-1])j++;
                    else j--;
                }
                if(i+1<n)if(Y[i]<Y[i+1])j++;
                else j--;
                if(j>0)m[Y[i]<<1]++;
                if(j>1)m[(Y[i]<<1)+1]++;
                if(j<0)m[(Y[i]<<1)+1]--;
                if(j<-1)m[Y[i]<<1]--;
            }
            for(it=m.begin(),i=j=0;it!=m.end();it++)j=max(j,i+=it->second);
            return j;
        }
};
