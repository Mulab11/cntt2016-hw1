#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
class FoxAndFencing{
public:
    string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d){
        if(d<=rng1+mov1)return "Ciel";

        if(rng1+mov1==rng2+mov2)return "Draw";

        if(rng1+mov1>rng2+mov2){
            if(mov1>mov2&&rng1+mov1>rng2+mov2+mov2)return "Ciel";
            else return "Draw";
        }
        else{
            if(mov1+d<=mov2+rng2)return "Liss";
            else if(mov1<mov2&&rng2+mov2>rng1+mov1+mov1)return "Liss";
            else return "Draw";
        }
    }
};