#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,l,r,x[300],y[300],z[300],a[10005],s1[10005],s2[10005];
double X;
long long ans;
class Ear
{
    public:
        void get(vector<string> x,int &n,int *a)//将字符串转成数组并统计个数 
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
        long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)
        {
            get(redX,n,z);
            get(blueX,m,x);
            get(blueY,m,y);
            for(i=0;i<n;i++)a[z[i]]++;
            for(i=1;i<10001;i++)s1[i]=s1[i-1]+a[i];
            for(i=10000;i;i--)s2[i]=s2[i+1]+a[i];
            for(i=0;i<m;i++)for(j=0;j<m;j++)if(y[i]>y[j])//枚举P、Q 
            {
                X=(double)(x[i]*y[j]-x[j]*y[i])/(y[j]-y[i]);//计算PQ与x轴的交点 
                l=max(min(x[i],(int)ceil(X))-1,0);//计算A的右界 
                r=min(max(x[i],(int)floor(X))+1,10001);//计算D的左界 
                ans+=(long long)(2*s1[x[j]-1]-s1[l]-1)*s1[l]/2*(2*s2[x[j]+1]-s2[r]-1)*s2[r]/2;//计算答案 
            }
            return ans;
        }
};