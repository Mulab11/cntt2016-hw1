#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=51;
double f[N][N][N][N];
class RockPaperScissors{
    public:
    double bestScore(vector<int>A,vector<int>B,vector<int>C){
        int n=A.size();
        //f[i][A][B][C]表示有A个石头，B个布，C个剪刀，第i个骰子还没用过的概率
        rep(i,1,n){
            //0个的概率是1
            f[i][0][0][0]=1;
            //用t枚举骰子，进行背包
            rep(t,1,n)per(m,t,0)rep(a,0,m)rep(b,0,m-a){
                int c=m-a-b;
                //q表示第t个骰子在m个里的概率
                double q=(m*1.)/(t*1.);
                double sum=0;
                //计算概率和
                if(a)sum+=f[i][a-1][b][c]*A[t-1]/300.;
                if(b)sum+=f[i][a][b-1][c]*B[t-1]/300.;
                if(c)sum+=f[i][a][b][c-1]*C[t-1]/300.;
                f[i][a][b][c]*=(1-q);
                //如果i!=t，则t可以选，否则不能，因为会违反假设
                if(i^t)f[i][a][b][c]+=sum*q;
            }
        }
        double ans=0;
        rep(a,0,n)rep(b,0,n-a)rep(c,0,n-a-b){
            int rest=n-a-b-c;
            if(rest==0)continue;
            double SA,SB,SC;SA=SB=SC=0;
            //枚举每一步的局面
            //根据期望的线性性，局面X变换到局面Y的贡献E(X->Y)可以表示成P(X)P(X->Y)*W(X->Y)
            rep(i,1,n){
                //统计下下一波的出骰子i的方案
                //并计算出现每个面的概率
                double bb=f[i][a][b][c]/rest;
                SA+=bb*A[i-1]/300.;
                SB+=bb*B[i-1]/300.;
                SC+=bb*C[i-1]/300.;
            }
            //通过概率进行决策
            ans+=max(SA*3+SB,max(SB*3+SC,SC*3+SA));
        }
        return ans;
    }
};



