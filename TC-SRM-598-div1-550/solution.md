# FoxAndFencing2

作者: 徐海珂  
关键词: 博弈,分类讨论

- - -

## 题目简述
* Fox Ciel在和Squirrel Liss玩一个游戏. 游戏在一个无限长的一维坐标轴上。 每个玩家有一枚棋子. 一开始Ciel的棋子在$$x=0$$的位置，Liss的棋子在$$x=d$$的位置。每个棋子有两个属性: 最大移动距离,攻击范围。 Ciel的棋子的最大移动距离是$$mov1$$,攻击范围是$$rng1$$。Liss的棋子的最大移动距离是$$mov2$$,攻击范围是$$rng2$$。两人轮流操作，Ciel先走。每轮当前玩家移动己方棋子，但移动距离不可超过该棋子最大移动距离限制(移动距离必须是整数，可以不动) 。然后,当前玩家检查对方棋子是否在己方棋子攻击范围内，如果是，当前选手获胜，否则游戏继续。已知正整数$$mov1$$,$$mov2$$,$$rng1$$,$$rng2$$,$$d$$。求出双方都使用最优策略下谁能获胜，或者平局。

### 约定与限制
* $$mov1,mov2,rng1,rng2,d \in [1,10^9]$$
* 时间限制: $$2$$s
* 空间限制: $$64$$MB

- - -

## 算法
* 首先判断ciel能否第一轮击败liss。能的话直接结束,ciel获胜。下面讨论均假设ciel第一轮不能击败liss
* 以下用$$dis$$表示当前两人棋子的距离。
* 考虑一个结论 : **ciel能击败liss的必要条件是$$mov1+rng1\gt mov2+rng2$$。(liss击败ciel同理)**
> 证明：
> 假设$$mov1+rng1 \le mov2+rng2$$而ciel赢了（第一局除外），说明ciel最后一次移动之前$$dis\le mov1+rng1$$，在考虑上一轮less移动之前的$$dis'$$,如果$$dis'\gt dis$$那么liss不可能这样移动，因为这样直接输掉了比赛。如果$$dis'\le dis$$那么因为$$mov2+rng2\ge mov1+rng1$$，liss移动之后就已经能干掉ciel了，比赛结束。所以这种情况下ciel不可能获胜。
* 所以$$mov1+rng1=mov2+rng2$$的时候一定是平局。下面讨论均假设$$mov1+rng1\neq mov2+rng2$$。
* 如果$$mov1+rng1\gt mov2+rng2$$，这时只要判断答案是ciel胜还是平局。这时由于ciel第一轮不能打败liss,而liss已知自己赢不了ciel,他会争取能平局，所以liss之后一直朝远离ciel的方向走，ciel会追赶liss,所以ciel胜的一个条件是$$mov1\gt mov2$$,ciel在追的时候还要保证自己不能被liss下一次干掉，也就是ciel要满足移动完之后$$dis\gt mov2+rng2$$。所以还有一个条件是$$rng2+mov2+1+mov2\le rng1+mov1$$。
* 以下是这种情况的伪代码
```
    if(mov1+rng1>mov2+rng2)
    {   if(mov1>mov2 && rng2+mov2+1+mov2<=rng1+mov1)
            ciel获胜
        else
            平局
    }
```
* 如果$$mov2+rng2\gt mov1+rng2$$，情况类似，但是要判断liss是否能在liss的第一次中(也就是第二轮）击败ciel。如果不行的话再套用上一种情况的判断策略。
* 以下是这种情况的伪代码
```
    if(mov2+rng2>mov1+rng1)
    {   if(mov1+d<=mov2+rng2)
            liss获胜
        else if(mov2>mov1 && mov1+rng1+1+mov1<=rng2+mov2)
            liss获胜
        else
            平局
    }
```
* 这样这道题就做完了。

* 时间复杂度: $$O(1)$$
  空间复杂度: $$O(1)$$

### 总结
* 这是一道分类讨论的题，先判断特殊情况ciel第一轮击败liss，然后证明一个结论，最后分成三类各自讨论游戏胜负。

- - -

## 参考资料
* [SRM598 - TopCoder Wiki](https://apps.topcoder.com/wiki/display/tc/SRM+598)
