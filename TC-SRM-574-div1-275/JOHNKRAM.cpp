#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,a[100],b[100];
bool work()//判断b是不是a的子串 
{
    for(i=0;i+m<=n;i++)//枚举起点 
    {
        for(j=0;j<m;j++)if(a[i+j]!=b[j])break;//暴力比较 
        if(j==m)return 1;
    }
    return 0;
}
class TheNumberGame
{
    public:
        string determineOutcome(int A, int B)
        {
            for(;A;a[n++]=A%10,A/=10);//数字转字符串 
            for(;B;b[m++]=B%10,B/=10);
            if(work())return "Manao wins";
            reverse(b,b+m);
            if(work())return "Manao wins";
            return "Manao loses";
        }
};