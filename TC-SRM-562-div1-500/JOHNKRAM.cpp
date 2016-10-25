#include<bits/stdc++.h>
using namespace std;
#define ll long long
int wx[300],wy[300],bx[300],by[300],x[600],y[600];
class CheckerFreeness
{
    public:
        int check(int x1,int y1,int x2,int y2,int x3,int y3)
        {
            ll x=(ll)(x2-x1)*(y3-y1)-(ll)(x3-x1)*(y2-y1);
            if(x>0)return 1;
            if(x<0)return -1;
            return 0;
        }
        void get(vector<string> x,int &n,int *a)
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
        string isFree(vector<string> whiteX,vector<string> whiteY,vector<string> blackX,vector<string> blackY)
        {
            int n=0,m=0,N=0,i=0,j=0,k=0;
            get(whiteX,n,wx);
            get(whiteY,n,wy);
            get(blackX,m,bx);
            get(blackY,m,by);
            N=n+m;
            bitset<256> b[N][N];
            for(i=0;i<n;i++)
            {
                x[i]=wx[i];
                y[i]=wy[i];
            }
            for(i=0;i<m;i++)
            {
                x[i+n]=bx[i];
                y[i+n]=by[i];
            }
            for(i=0;i<n;i++)for(j=i+1;j<N;j++)for(k=0;k<m;k++)if(j!=k+n)if(check(bx[k],by[k],x[i],y[i],x[j],y[j])>0)b[i][j][k]=1;
            else b[j][i][k]=1;
            for(i=0;i<n;i++)for(j=i+1;j<n;j++)for(k=0;k<m;k++)if(((b[i][k+n]^b[j][k+n])&(b[i][j][k]?(~b[i][j]):b[i][j])).any())return "NO";
            return "YES";
        }
};