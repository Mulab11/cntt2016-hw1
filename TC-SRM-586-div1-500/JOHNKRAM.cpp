#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,l,x,y,a[100][100],m[100],d[100][100];
string s,ans;
class History
{
    public:
        void get(string s,int &n,int *a)
        {
            int i=0;
            for(n=i=0;i<s.size();n++)
            {
                for(;(s[i]<'0'||s[i]>'9')&&i<s.size();i++);
                if(i==s.size())break;
                for(a[n]=0;i<s.size()&&s[i]>='0'&&s[i]<='9';i++)a[n]=(a[n]<<3)+(a[n]<<1)+(s[i]^'0');
            }
        }
        string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries)
        {
            n=dynasties.size();
            memset(d,193,sizeof(d));
            for(i=0;i<n;i++)d[i][i]=0;
            for(i=0;i<n;i++)get(dynasties[i],m[i],a[i]);
            for(i=0;i<battles.size();i++)s+=battles[i];
            for(i=0;i<s.size();i+=6)
            {
                x=s[i]-'A';
                j=s[i+1]-'0';
                if(s[i+2]>='0'&&s[i+2]<='9')j=j*10+s[(++i)+1]-'0';
                y=s[i+3]-'A';
                k=s[i+4]-'0';
                if(i+5<s.size()&&s[i+5]>='0'&&s[i+5]<='9')k=k*10+s[(++i)+4]-'0';
                d[x][y]=max(d[x][y],a[y][k]+1-a[x][j+1]);
                d[y][x]=max(d[y][x],a[x][j]+1-a[y][k+1]);
            }
            for(k=0;k<n;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)d[i][j]=max(d[i][j],d[i][k]+d[k][j]);
            for(i=0;i<queries.size();i++)
            {
                s=queries[i];
                l=0;
                x=s[l]-'A';
                j=s[l+1]-'0';
                if(s[l+2]>='0'&&s[l+2]<='9')j=j*10+s[(++l)+1]-'0';
                y=s[l+3]-'A';
                k=s[l+4]-'0';
                if(l+5<s.size()&&s[l+5]>='0'&&s[l+5]<='9')k=k*10+s[(++l)+4]-'0';
                if(d[x][y]>a[y][k+1]-a[x][j]-1||d[y][x]>a[x][j+1]-a[y][k]-1)ans+='N';
                else ans+='Y';
            }
            return ans;
        }
};
