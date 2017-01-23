#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,ans;
bool b[55];
class BinPacking
{
    public:
        int minBins(vector <int> item)
        {
            n=m=item.size();
            sort(item.begin(),item.end());
            for(i=n-1;~i;i--)if(!b[i]&&item[i]>100)
            {
                b[i]=1;
                m--;
                ans++;
                for(j=i-1;~j;j--)if(!b[j]&&item[i]+item[j]<301)
                {
                    b[j]=1;
                    m--;
                    break;
                }
            }
            return ans+(m+2)/3;
        }
};
