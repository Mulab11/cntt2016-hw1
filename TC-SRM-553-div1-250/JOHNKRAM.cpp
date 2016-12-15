#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n,i,k,l;
ll j;
class Suminator
{
    public:
        int findMissing(vector <int> program, int wantedResult)
        {
            n=program.size();
            reverse(program.begin(),program.end());//反转后便于处理 
            for(i=j=0,k=1;i<n;i++)if(!program[i]||!~program[i])k++; 
            else if(--k>=0)j+=program[i];
            if(j==wantedResult)return 0;//判断未知数是否等于0 
            for(i=j=l=0,k=1;i<n;i++)if(!program[i])k++;
            else if(--k>=0)if(~program[i])j+=program[i];
            else l=1;
            j=wantedResult-j;
            if(l)return j>0&&j<1000000001?j:-1;//未知数对答案有影响 
            else return j?-1:1;//未知数对答案没有影响 
        }
};