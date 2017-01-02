#include<bits/stdc++.h>
using namespace std;
string f[50][50][3];
int n,i,j,k,l;
int cmp(char a,char b)//比较大小 
{
    if(a<b)return 0;
    if(a==b)return 1;
    return 2;
}
void fix(string& a,const string& b)//将a修改为两者的最小值 
{
    if(b.size()>1&&(a.empty()||a>b))a=b;
}
class LeftRightDigitsGame2
{
    public:
        string minNumber(string digits, string lowerBound)
        {
            n=digits.size();
            for(i=0;i<n;i++)f[i][i][cmp(digits[0],lowerBound[i])]=digits[0];//枚举第0个放的位置 
            for(l=1;l<n;l++)for(i=0;i+l<n;i++)
            {
                j=i+l;
                fix(f[i][j][0],f[i][j-1][0]+digits[l]);//第l个放在后面 
                fix(f[i][j][cmp(digits[l],lowerBound[j])],f[i][j-1][1]+digits[l]);
                fix(f[i][j][2],f[i][j-1][2]+digits[l]);
                k=cmp(digits[l],lowerBound[i]);
                fix(f[i][j][k>>1<<1],digits[l]+f[i+1][j][0]);//第l个放在前面 
                fix(f[i][j][k],digits[l]+f[i+1][j][1]);
                fix(f[i][j][k+1>>1<<1],digits[l]+f[i+1][j][2]);
            }
            fix(f[0][n-1][1],f[0][n-1][2]);//大于和等于两种情况取最小值 
            return f[0][n-1][1];
        }
};