#include<bits/stdc++.h>
using namespace std;
class FoxAndMountainEasy
{
    public:
        string possible(int n, int h0, int hn, string history)
        {
            int m=history.size(),i,j=h0,k;
            for(i=0;i<m;i++)if(history[i]=='U')j++;
            else j--;
            k=j-hn;
            if(k<0)k=-k;
            if(n<k+m||((n^m^k)&1))return "NO";//判断是否有不考虑高度>=0的合法解 
            k=n-m-k>>1;
            if(hn>j)k+=hn-j;
            j=h0+k;//计算history开始时最大的初始高度 
            for(i=0;i<m;i++)
            {
                if(history[i]=='U')j++;
                else j--;
                if(j<0)return "NO";//判断中途高度是否<0 
            }
            return "YES";
        }
};