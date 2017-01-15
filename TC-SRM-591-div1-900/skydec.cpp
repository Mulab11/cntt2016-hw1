#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<string>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int P=1000000009;
int f[9][9][1<<16];
int bit(int x,int y){
    return (x&(1<<(y-1)))>0;
}
void add(int &x,int y){
    x+=y;if(x>=P)x-=P;
}
class StringPath{
    public:
    int countBoards(int n, int m, string A, string B){
        if(A[0]!=B[0])return 0;
        f[1][1][1+(1<<m)]=1;
        rep(i,1,n)rep(j,1,m)
        if(!(i==n&&j==m))
        rep(st,0,(1<<(2*m))-1)if(f[i][j][st]){
            int val=f[i][j][st];
            int ny=j%m+1;
            int nx=i;if(j==m)nx++;
            if(A[nx+ny-2]==B[nx+ny-2]){
                int ppst=st;
                if(bit(ppst,ny))ppst^=(1<<(ny-1));
                if(bit(ppst,ny+m))ppst^=(1<<(m+ny-1));
                
                add(f[nx][ny][ppst],val*25ll%P);
                
                if(bit(st,ny))ppst|=(1<<(ny-1));
                if(ny>1&&bit(st,ny-1))ppst|=(1<<(ny-1));
                if(bit(st,ny+m))ppst|=(1<<(m+ny-1));
                if(ny>1&&bit(st,m+ny-1))ppst|=(1<<(m+ny-1));
                
                add(f[nx][ny][ppst],val);
            }
            else{
                int ppst=st;
                if(bit(ppst,ny))ppst^=(1<<(ny-1));
                if(bit(ppst,ny+m))ppst^=(1<<(m+ny-1));
                
                add(f[nx][ny][ppst],val*24ll%P);
                
                if(bit(st,ny))ppst|=(1<<(ny-1));
                if(ny>1&&bit(st,ny-1))ppst|=(1<<(ny-1));
                
                add(f[nx][ny][ppst],val);
                
                ppst=st;
                if(bit(ppst,ny))ppst^=(1<<(ny-1));
                if(bit(ppst,ny+m))ppst^=(1<<(m+ny-1));
                
                if(bit(st,ny+m))ppst|=(1<<(m+ny-1));
                if(ny>1&&bit(st,m+ny-1))ppst|=(1<<(m+ny-1));
                
                add(f[nx][ny][ppst],val);
            }
        }
        int ans=0;
        rep(i,0,(1<<(2*m))-1)if(bit(i,m)&&bit(i,2*m))
        add(ans,f[n][m][i]);
        return ans;
    }
};