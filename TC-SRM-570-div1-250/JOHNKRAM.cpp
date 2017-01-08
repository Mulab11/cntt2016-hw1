#include<bits/stdc++.h>
using namespace std;
const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
long long x,y,z,ax[5],ay[5],az[5],n,i,j;
long long A(long long x)//求绝对值 
{
    if(x<0)return -x;
    return x;
}
class RobotHerb
{
    public:
        long long getdist(int T, vector <int> a)
        {
            n=a.size();
            for(i=1;i<5;ax[i]=x,ay[i]=y,az[i++]=z)for(j=0;j<n;j++)//求出执行1~4次命令后的坐标 
            {
                x+=dx[z]*a[j];
                y+=dy[z]*a[j];
                z=z+a[j]&3;
            }
            return A((ax[4]*(T>>2))+ax[T&3])+A((ay[4]*(T>>2))+ay[T&3]);
        }
};