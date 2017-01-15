#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
using namespace std;
typedef long long LL;
const int N=55;
int n,m;
bool a[N][N];
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
int id[N][N];
bool ok(int x,int y){
    if(x<1)return 0;
    if(x>n)return 0;
    if(y<1)return 0;
    if(y>m)return 0;
    return a[x][y];
}
int fa[N*N];
int tot;
int get(int x){
    if(x==fa[x])return x;
    return fa[x]=get(fa[x]);
}
int kd[N];
//1:左边往下或者右边往下
//2:左上右下或者左下右上
//4:左边必须往上
//8:左边可以往下
//16:右边必须往上
//32:右边可以往下
int f[N][N][N];
int dp(){
    rep(i,0,n)rep(j,0,n)rep(k,0,n)f[i][j][k]=-1000000;
    //进行dp
    //f[i][l][r]表示前i行，左边有l个，右边有r个
    //大力转移即可
    if(kd[1]==1){
        f[1][1][0]=0;
        f[1][0][1]=0;
    }
    else
    if(kd[1]==2){
        f[1][1][0]=f[1][0][1]=0;
    }
    else
    f[1][(kd[1]&8)>0][(kd[1]&32)>0]=0;
    rep(i,1,n)rep(j,0,n)rep(k,0,n)if(f[i][j][k]>=0){
        int ret=f[i][j][k];
        if(kd[i+1]==2){
            //左上右下
            rep(l,0,j){
                f[i+1][max(l-1,0)][k+1]=max(f[i+1][max(l-1,0)][k+1],ret+(l!=0));
            }
            //左下右上
            rep(l,0,k){
                f[i+1][j+1][max(l-1,0)]=max(f[i+1][j+1][max(l-1,0)],ret+(l!=0));
            }
        }
        else{
            if(kd[i+1]&4){
                rep(l,0,j){
                    if(kd[i+1]&16){
                        rep(d,0,k){
                            f[i+1][max(l-1,0)][max(d-1,0)]=max(f[i+1][max(l-1,0)][max(d-1,0)],ret+(l!=0)+(d!=0));
                        }
                    }
                    else
                    if(kd[i+1]&32){
                        f[i+1][max(l-1,0)][k+1]=max(f[i+1][max(l-1,0)][k+1],ret+(l!=0));
                    }
                    else{
                        f[i+1][max(l-1,0)][k]=max(f[i+1][max(l-1,0)][k],ret+(l!=0));
                    }
                }
            }
            else
            if(kd[i+1]&8){
                int l=j;
                if(kd[i+1]&16){
                    rep(d,0,k){
                        f[i+1][l+1][max(d-1,0)]=max(f[i+1][l+1][max(d-1,0)],ret+(d!=0));
                    }
                }
                else
                if(kd[i+1]&32){
                    f[i+1][l+1][k+1]=max(f[i+1][l+1][k+1],ret);
                }
                else{
                    f[i+1][l+1][k]=max(f[i+1][l+1][k],ret);
                }
            }
            else{
                int l=j;
                if(kd[i+1]&16){
                    rep(d,0,k){
                        f[i+1][l][max(d-1,0)]=max(f[i+1][l][max(d-1,0)],ret+(d!=0));
                    }
                }
                else
                if(kd[i+1]&32){
                    f[i+1][l][k+1]=max(f[i+1][l][k+1],ret);
                }
                else{
                    f[i+1][l][k]=max(f[i+1][l][k],ret);
                }
            }
        }
    }
    int ans=0;
    rep(i,0,n)rep(j,0,n)ans=max(ans,f[n][i][j]);
    return ans;
}
pii laob[N*N];
int t;
void dfs(int x,int y,int fx,int fy){
    //搜索联通块
    laob[++t]=pii(x,y);
    rep(k,0,3)if(ok(x+dx[k],y+dy[k])){
        dfs(x+dx[k],y+dy[k],x,y);
    }
}
int du(int x,int y){
    int ans=0;
    //统计一个点的度数
    rep(k,0,3)if(ok(x+dx[k],y+dy[k]))ans++;
    return ans;
}
int Main(){
    rep(i,1,n)rep(j,1,m)if(a[i][j])id[i][j]=++tot;
    rep(i,1,tot)fa[i]=i;
    //先将联通块全部用并查集连起来
    rep(i,1,n)rep(j,1,m)if(id[i][j])rep(k,0,3)if(ok(i+dx[k],j+dy[k])){
        fa[get(id[i][j])]=get(id[i+dx[k]][j+dy[k]]);
    }
    int num=0;
    rep(i,1,n)rep(j,1,m)if(a[i][j])if(get(id[i][j])==id[i][j]){
        //枚举一个联通块
        ++num;
        int ret=0;
        int lx=n+5;int rx=-1;
        int ly=m+5;int ry=-1;
        int ll=n+5;int lr=-1;
        int rl=n+5;int rr=-1;
        //计算这个联通块的信息
        //lx和rx分别是最小的x和最大的x
        //ly和ry分别是最小的y和最大的y
        int Sx,Sy;
        Sx=Sy=100;
        rep(l,1,n)rep(p,1,m)if(id[l][p])if(get(id[l][p])==id[i][j]){
            ret++;
            lx=min(lx,l);
            rx=max(rx,l);
            ly=min(ly,p);
            ry=max(ry,p);

            //ll是第一列里x最小的
            //lr是第一列里x最大的
            if(p==1){
                ll=min(ll,l);
                lr=max(lr,l);
            }
            else
            if(p==m){
            //rl是最后一列里x最小的
            //rr是最后一列里x最大的
                rl=min(rl,l);
                rr=max(rr,l);
            }
        }
        //kind 1
        if(((rx-lx+1)*m==ret)&&(ly==1&&ry==m)){
            //判断是由多行组成的x*m的矩形
            if(lx==1)kd[lx]=1;
            else kd[lx]=2;
            continue;
        }
        //特判若干种情况
        if(ly!=1&&ry!=m)continue;
        if(ret==1){
            //当只有一个点的情况，判断下是否在第一列即可
            //还要判断下是否在第一行
            if(ly==1){
                if(lx!=1)kd[lx]|=4;
                else kd[lx]|=8;
            }
            if(ry==m){
                if(lx!=1)kd[lx]|=16;
                else kd[lx]|=32;
            }
            continue;
        }
        if(ret==2){
            //只有2个点，要注意2*1的矩阵，那种矩阵十分特殊
            if(lx!=rx){
                if(ly==1){
                    if(lx==1)kd[rx]|=8;
                    else kd[lx]|=4;
                }
                else
                if(ry==m){
                    if(lx==1)kd[rx]|=32;
                    else kd[lx]|=16;
                }
                continue;
            }
        }

        if(lx==1){
            //判断是否在第一行
            if(lr==rx){
                if(du(rx,1)==1){
                    kd[rx]|=8;
                }
            }
            if(rr==rx){
                if(du(rx,m)==1){
                    kd[rx]|=32;
                }
            }
        }
        if(lx>1){
            //不在第一行的话再特判各种情况
            if(ll==lx){
                if(du(lx,1)==1){
                    kd[lx]|=4;
                }
            }
            if(lr==rx){
                if(du(rx,1)==1){
                    kd[rx]|=8;
                }
            }
            if(rl==lx){
                if(du(lx,m)==1){
                    kd[lx]|=16;
                }
            }
            if(rr==rx){
                if(du(rx,m)==1){
                    kd[rx]|=32;
                }
            }
        }
    }
    return num-dp();
}    
class Tunnels{
public:
    int minimumTunnels(vector <string> frame){
        //预处理
        n=frame.size();
        m=frame[0].size();
        rep(i,1,n)rep(j,1,m)a[i][j]=(frame[i-1][j-1]=='X');
        return Main();
    }
}gt;

