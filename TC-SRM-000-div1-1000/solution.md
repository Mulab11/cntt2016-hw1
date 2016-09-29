# AB（用原题目的名称）
作者：陈许旻（这里注明一下你的名字，方便读者知道你是谁） 余林韵（所有有过修改的同学按照第一次修改的时间顺序列举名字）

关键词：一元二次方程 准多项式复杂度 排序 前缀和
## 题目简述
输入两个整数$$a, b$$，输出它们的和。保证$$\left|a\right|,\left|b\right|\le 10^{9}$$。:smile:

用简洁准确的语言描述题意，并写出数据范围。

## 算法一
这份作业我们采用markdown语法书写。markdown是一种脱离排版的语法，在书写的时候一般只用考虑文字本身的属性。例如我们可以**加粗**，*斜体*，~~删除~~，

> 引用

等，但不用考虑每一种语法具体应该怎么显示。

有时候我们需要用到字符串，则用一对反引号括起来，就像这样`I'm a string`。

如果需要插入链接，则用方括号把显示的文字括起来，在后面用圆括号把链接括起来。一般可以同时支持内部链接和外部链接。就像这样：[UOJ](http://uoj.ac/)，[返回标题页](/)。

有时候需要用到公式，用一对两个dollar号括起来，就像这样$$O\left(n^{\sqrt{\log{n}}}\right)$$，公式的语法和latex是一样的。（注意：有的markdown工具用一个dollar也能表示公式，因为gitbook只能用两个，所以大家统一使用两个吧）如果需要使用断行的公式，则让两个dollar单独占一行即可，例如

$$
x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}
$$

如果我们需要插入代码，我们用一对三个反引号括起来，还可以指定语言，例如：

```C++
#include <algorithm>
#include <vector>
class AB{
public:
  int solve(int a, int b){
    std::vector<int> vec;
    vec.push_back(a);
    vec.push_back(b);
    std::sort(vec, vec + 2);
    int sum = 0;
    for(auto i : vec)
      sum += i;
    return sum;
  }
}
```

如果用插入图片，可以使用下列语法：

![如果图片加载失败会显示这段文字](1.jpg)

其中圆括号内可以是相对路径如`1.jpg`，绝对路径如`/TC-SRM-000-div1-1000/1.jpg`，或是完整的URL如`http://uoj.ac/pictures/UOJ.png`。虽然有一些markdown的方言支持修改图片的大小，但是我们建议尽量少使用。

如果要画表格，markdown支持如下语法的表格：

| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
| col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |

很遗憾，目前这个表格没法合并单元格，设置对齐也只能每一列使用同样的方向。

markdown在很多情况下支持直接插入html标签，但是似乎不是很能用上，而且有些渲染工具不是很支持，所以建议大家尽量也不要使用。

