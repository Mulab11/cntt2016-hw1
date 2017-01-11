#include<bits/stdc++.h>
using namespace std;
int a[1005],n,m,i,j,k,x,y,z;
double ans;
class EllysRoomAssignmentsDiv1
{
    public:
        void get(vector<string> x,int &n,int *a)//求数组及长度 
        {
            string s="";
            int i=0;
            for(;i<x.size();i++)s+=x[i];
            for(n=i=0;i<s.size();n++)
            {
                for(;(s[i]<'0'||s[i]>'9')&&i<s.size();i++);
                if(i==s.size())break;
                for(a[n]=0;i<s.size()&&s[i]>='0'&&s[i]<='9';i++)a[n]=(a[n]<<3)+(a[n]<<1)+(s[i]^'0');
            }
        }
        double getAverage(vector <string> ratings)
        {
            get(ratings,n,a);
            m=a[0];
            sort(a,a+n,greater<int>());
            x=(n+19)/20;
            y=n/x;
            z=n-x*y;
            for(i=0;i<y;i++)if(m>=a[(i+1)*x-1]&&m<=a[i*x])ans+=m;//求不考虑剩余的人时期望的和 
            else
            {
                for(j=i*x,k=0;j<(i+1)*x;j++)k+=a[j];
                ans+=(double)k/x;
            }
            if(!z)return ans/y;//没有剩余的人 
            if(a[x*y]>=m)return (ans+m)/(y+1);//本身是剩余的人 
            for(i=x*y,j=0;i<n;i++)j+=a[i];
            return (ans+(double)j/z)*z/x/(y+1)+ans*(x-z)/x/y;//有没有剩余的人在同一组 
        }
};