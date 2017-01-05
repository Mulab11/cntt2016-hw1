#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000009
#define mp make_pair
#define pii pair<int,int>
#define vi vector<int>
#define mpv map<pii,vi>
int n,m,i,j,w,x,y,z,ans;
vi v;
mpv s;
mpv::iterator it;
int work(int *a,int *b,int *c,int A,int B,int C)//求出中间点到a、b、c距离分别为A、B、C的树的个数 
{
    if(A<=0||B<=0||C<0)return 0;
    s.clear();
    ans=1;
    for(i=0;i<n;i++)
    {
        if(a[i]+B==b[i]+A)//在c所在的支链上 
        {
            x=C+A+c[i]-a[i];
            y=c[i];
            z=C;
            w=0;
        }
        else if(b[i]+C==c[i]+B)//在a所在的支链上 
        {
            x=A+B+a[i]-b[i];
            y=a[i];
            z=A;
            w=1;
        }
        else if(a[i]+C==c[i]+A)//在b所在的支链上 
        {
            x=B+C+b[i]-c[i];
            y=b[i];
            z=B;
            w=2;
        }
        else return 0;
        if(x<0||x>(z<<1)||(x&1))return 0;//去除非法情况 
        y-=x>>=1;//去掉多余的部分 
        s[mp(x,w)].push_back(y);
    }
    for(it=s.begin();it!=s.end();it++)
    {
        v=it->second;
        sort(v.begin(),v.end());
        m=v.size();
        if(it->first.first&&(v[0]||m>1&&!v[1]))return 0;//有且仅有一个根节点 
        for(i=j=1;i<m;i++)
        {
            if(v[i]!=v[i-1])j=i+!!v[0];//求有多少个结点可以作为父亲 
            ans=(ll)ans*j%P;
        }
    }
    return ans;
}
int X(int *a,int *b,int *c)//abc在一条链上 
{
    for(i=j=0;i<n;i++)if(c[i]<c[j])j=i;
    swap(a[0],a[j]);
    swap(b[0],b[j]);
    swap(c[0],c[j]);
    return ((ll)work(a,b,c,a[0]-c[0],b[0]-c[0],0)+work(a,b,c,a[0]+c[0],b[0]-c[0],0)+work(a,b,c,a[0]-c[0],b[0]+c[0],0)+work(a,b,c,c[0]-a[0],b[0]-c[0],0)+work(a,b,c,a[0]-c[0],c[0]-b[0],0))%P;
}
int Y(int *a,int *b,int *c)//abc不在一条链上 
{
    for(i=j=0;i<n;i++)if(a[i]+b[i]+c[i]<a[j]+b[j]+c[j])j=i;
    swap(a[0],a[j]);
    swap(b[0],b[j]);
    swap(c[0],c[j]);
    return work(a,b,c,a[0],b[0],c[0]);
}
class UnknownTree
{
    public:
        int getCount(vector <int> distancesA, vector <int> distancesB, vector <int> distancesC)
        {
            n=distancesA.size();
            int *a=&distancesA[0],*b=&distancesB[0],*c=&distancesC[0];
            return ((ll)X(a,b,c)+X(a,c,b)+X(b,c,a)+Y(a,b,c))%P;//计算答案 
        }
};