#include<bits/stdc++.h>
using namespace std;
const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};
double ccc(int a,int b,int c)//C(a,c)/C(a+b,c)
{
    if(a<c)return 0;
    double x=1;
    for(int i=0;i<c;i++)x=x*(a-i)/(a+b-i);
    return x;
}
int n,m,N,i,j,k,l,d[55][55],f[2505],qx[2505],qy[2505],he,ta,x[305],y[305],D[305][305],s[2505];
double ans;
bool check(int s1,int t1,int s2,int t2)//比较(s1,t1)和(s2,t2)路径长度 
{
    if(D[s1][t1]!=D[s2][t2])return D[s1][t1]<D[s2][t2];
    if(s1>t1)swap(s1,t1);
    if(s1!=s2)return s1>s2;
    return t1>t2;
}
class Orienteering
{
    public:
        double expectedLength(vector <string> field, int K)
        {
            n=field.size();
            m=field[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)if(field[i][j]=='*')
            {
                memset(d,-1,sizeof(d));
                d[x[N]=qx[0]=i][y[N]=qy[0]=j]=he=0;
                ta=1;
                for(;he!=ta;he++)for(k=0;k<4;k++)if(qx[he]+dx[k]>=0&&qy[he]+dy[k]>=0&&qx[he]+dx[k]<n&&qy[he]+dy[k]<m&&field[qx[he]+dx[k]][qy[he]+dy[k]]!='#'&&!~d[qx[he]+dx[k]][qy[he]+dy[k]])//广搜求距离 
                {
                    d[qx[ta]=qx[he]+dx[k]][qy[ta]=qy[he]+dy[k]]=d[qx[he]][qy[he]]+1;
                    f[ta++]=he;//建树 
                }
                for(k=0;k<N;k++)D[N][k]=D[k][N]=d[x[k]][y[k]];
                if(!N)
                {
                    for(k=he-1;~k;k--)//求子树大小 
                    {
                        if(field[qx[k]][qy[k]]=='*')s[k]++;
                        if(k)s[f[k]]+=s[k];
                    }
                    for(k=1;k<he;k++)ans+=1-ccc(s[k],s[0]-s[k],K)-ccc(s[0]-s[k],s[k],K);//求虚树大小期望 
                }
                N++;
            }
            ans*=2;
            for(i=1;i<N;i++)for(j=0;j<i;j++)
            {
                for(k=l=0;k<N;k++)if(k!=i&&k!=j&&check(k,i,j,i)&&check(k,j,j,i))l++;//统计有多少个点可以选 
                ans-=ccc(l,N-2-l,K-2)*D[i][j]*K*(K-1)/N/(N-1);//计算最远点对期望 
            }
            return ans;
        }
};