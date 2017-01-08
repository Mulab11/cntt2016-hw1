#include<bits/stdc++.h>
using namespace std;
int N,m=50;
vector<string> ans;
string s;
void dfs(string x)//搜索求解 
{
    if(stoll(x)>N||!m)return;//不合法情况或已有50个解 
    string s=x;
    s+=".mp3";
    ans.push_back(s);
    m--;
    for(int i=0;i<10;i++)dfs(x+(char)(i+'0'));//扩展 
}
class FoxAndMp3
{
    public:
        vector <string> playList(int n)
        {
            N=n;
            for(int i=1;i<10;i++)dfs(s+(char)(i+'0'));//枚举第一位 
            return ans;
        }
};