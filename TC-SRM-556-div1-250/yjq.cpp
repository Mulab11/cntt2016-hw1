#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<ctime>
#include<iostream>
#include<string>
#include<cctype>
#include<queue>
#include<stack>
#include<list>

using namespace std;

int n;

struct rec
{
    int num,v;
    rec(){}
    rec(int a,int b)
    {
        num=a;v=b;
    }
};

queue<rec> que;

bool use[1000][2000];

class XorTravelingSalesman
{
    public:
        int maxProfit(vector <int> v, vector <string> roads)
        {
            n=roads[0].size();
            que.push(rec(0,v[0]));
            int ans=v[0];
            use[0][v[0]]=true;
            while (que.size())
            {
                rec now=que.front();
                que.pop();
                for (int a=0;a<n;a++)
                    if (roads[now.num][a]=='Y')
                    {
                        int vv=now.v ^ v[a];
                        if (!use[a][vv])
                        {
                            que.push(rec(a,vv));
                            use[a][vv]=true;
                            ans=max(ans,vv);
                        }
                    }
            }
            return ans;
        }        
};

