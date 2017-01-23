#include<bits/stdc++.h>
using namespace std;
class FoxAndFencing
{
    public:
        string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)
        {
            if(mov1+rng1>=d||mov1>mov2&&mov1+rng1>(mov2<<1)+rng2)return "Ciel";
            if(mov2+rng2>=d+mov1||mov2>mov1&&mov2+rng2>(mov1<<1)+rng1)return "Liss";
            return "Draw";
        }
};
