# TheBrickTowerEasyDivOne

作者：徐懿

关键词：数学

## 题目简述

现在有$$redCount$$个高度为$$redHeight$$红色砖块，和$$blueCount$$个高度为$$blueHeight$$的蓝色砖块。你需要用其中的一部分砖块造一个塔。每个砖块只能放在地上，或者一个不同颜色的砖块上。一个砖块不能放在同样颜色的砖块上。地上和每个砖块上只能有至多一个砖块，每个砖块至多在一个砖块上，或在地上。一个塔至少要有一个砖块。一个塔的高度为所有组成它的砖块的高度和。两个塔被认为是相同的当且仅当两个塔的高度相同。

给定$$redCount,redHeight,blueCount,blueHeight$$，球有多少种不同的塔。

题目中给定的数均为$$[1,474747474]$$之间的整数。

## 解法

经过观察可以发现，一个塔中蓝色砖块的数量$$a$$，与其中红色砖块的数量$$b$$，满足$$|a-b|\leq1$$。

显然，塔的高度有

$$1.\quad i\times redHeight+i\times blueHeight$$

$$2.\quad i\times redHeight+(i-1)\times blueHeight$$

$$3.\quad (i-1)\times redHeight+i\times blueHeight$$

这三种。

当$$redHeight=blueHeight$$时，$$2.$$与$$3.$$计算会重复，反之亦然。

具体细节参见代码。

```C++
#include<bits/stdc++.h>

class TheBrickTowerEasyDivOne 
{
    public:
        int find(int rc, int rh, int bc, int bh) 
        {
            if(rc==bc)
            {
                if(rh==bh)return rc*2;//去除二式等于三式的情况
                else return rc*3;
            }
            else//a!=b的情况会多出一种
            {
                if(rh==bh)return std::min(rc,bc)*2+1;//去除二式等于三式的情况
                else return std::min(rc,bc)*3+1;
            }
        }
};
```



