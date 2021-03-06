#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


class RobotHerb {
public:
    long long getdist(int T, vector <int> a) {
        long long x=0,y=0,dir=0;
        for (int c=0;c<4;c++) //考虑到机器人执行操作a 4次后,一定会回到原方向,不妨记录4次后移动的距离 
            for (int b=0;b<(int)a.size();b++)
            {
                if (dir==0) y+=a[b];
                else
                {
                    if (dir==1) x+=a[b];
                    else
                    {
                        if (dir==2) y-=a[b];
                        else x-=a[b];
                    }
                }
                dir+=a[b];
                dir%=4;
            }
        long long ans=(abs(x)+abs(y))*(T/4); //进行T/4个整操作 
        x=0,y=0,dir=0;
        for (int c=0;c<T%4;c++) //还有T%4次零散的操作 
            for (int b=0;b<(int)a.size();b++)
            {
                if (dir==0) y+=a[b];
                else
                {
                    if (dir==1) x+=a[b];
                    else
                    {
                        if (dir==2) y-=a[b];
                        else x-=a[b];
                    }
                }
                dir+=a[b];
                dir%=4;
            }
        return ans+abs(x)+abs(y);
    }
};
