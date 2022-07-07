## 基于DCT的数字水印算法

### 算法原理

#### 数字水印嵌入

---

假设数字水印$W$为一个服从标准正态分布的随机实数序列，用数字序列表示为$W=\{W_{1},W_{2},\cdots ,W_{M}\}$。用$W$对$Y$序列中第$L+1$到$L+M$的中频系数部分的值进行修改，按以下公式进行：
$$
\left\{\begin{array}{lc}
Y_{i}^{\prime}=Y_{i} & i \leq L \text { 或 } i \geq L+M \\
Y_{i}^{\prime}=Y_{i}+\alpha Y_{i} W_{i} & L<i \leq L+M, \alpha>0
\end{array}\right.
$$
经过修改的系数序列$Y^{\prime}=\{Y_{1}^{\prime},Y_{2}^{\prime},\cdots,Y_{N\times N}^{\prime}\}$以$ZigZag$逆变换形式重组，再进行$N\times N DCT$逆变换，得到嵌有数字水印的图像$I^{\prime}$。

#### 数字水印提取

---

假设待检测的可能含有水印的图像为$I^{\prime \prime}$。假设$I^{\prime \prime}$并为损失大量信息，可以近似地认为$I^{\prime \prime}=I^{\prime}$。在此假设下可以运用统计的方法来检测水印。同样对$I^{\prime \prime}$进行$DCT$变换，以$ZigZag$方式将$DCT$系数排成一维向量$Y^{\prime \prime}=\{Y_{L+1}^{\prime \prime},Y_{L+2}^{\prime \prime},\cdots ,Y_{L+M}^{\prime \prime}\}$。由于假设$I^{\prime \prime}=I^{\prime}$，则$Y^{\prime \prime}=Y^{\prime}$。

取出$Y^{\prime \prime}$中第$L+1$到$L+M$的中频系数部分$Y^{\prime \prime}=\{Y_{L+1}^{\prime \prime},Y_{L+2}^{\prime \prime},\cdots,Y_{L+M}^{\prime \prime}\}$。假设待检测的数字水印$X=\{X_{1},X_{2},\cdots,X_{M}\}$为一个符合标准正态分布的实数伪随机序列。则可以通过检测待检水印与图像中频系数部分作相关运算来判断是否加入了水印，只有在待检水印为所加水印时，才能获得较大的相关值。否则相关值很小，接近于零。
$$
Z=\operatorname{cov}\left(Y_{L}^{\prime}, X\right)=\frac{1}{M} \sum_{i=1}^{M}\left(Y_{L+1} X_{t}\right)=\frac{1}{M} \sum\left(\left(Y_{L+1} X_{t}\right)+\alpha\left(Y_{L+1} W_{t} X i\right)\right)
$$
用符号$E$表示数学期望，得到：
$$
\left\{\begin{array}{lr}
E(z)=\alpha E\left(Y^{2}\right) & X=W \\
E(z)=0 & X \neq W \\
E(z)=0 & \text { 没有水印存在 }
\end{array}\right.
$$

### 实现步骤

#### 嵌入步骤

---

数字图像水印算法选择二值化灰度图像作为水印信息，根据水印图像的二值性选择不同的嵌入系数，并将载体图像进行$8\times8$的分块，将数字水印的灰度值直接植入到载体灰度图像的$DCT$变换域中，实现水印的嵌入。具体方法如下： 

设$I$是$M\times N$大小的原始图像，$J$是水印图像大小为$P\times Q$，$M$和$N$分别是$P$和$Q$的偶数倍，把水印$J$加载到图像$I$中，算法分以下几步进行： 

1. 将$I$分解为$(M/8)\times (N/8)$个$8\times 8$大小的方块$B$；同时，$J$也分解为$ (M/8)\times (N/8)$个$(8P/M)\times (8Q/N)$大小的方块$V$； 
2. 对每一个$B$进行$DCT$变换：$DB=DCT(B)$； 
3. 加载水印对每一个$DB$和$V$，$s(i)$为从$DB$的中频选出的加载的位置，$1\leq i\leq (8P/M)\times (8Q/N)$， $t(i)$为水印$V$的位置坐标 ，$1\leq i\leq (8P/M)\times (8Q/N)$，$DB^{\prime}(s)=\alpha \times V$，其中$\alpha$是加权系数,用$DB^{\prime}(s)$来代替$DB$，得到加载水印后的图像$DBC$；
4. 对以上得到的每一个$DBC$进行逆$DCT$变换：$IDBC=IDCT(DBC)$并将各方块$IDBC$合并为一个整图$I^{\prime}$，即加载了水印的新图像。 

#### 提取步骤

---

设图像$D$为已经加载了水印的载体图像，现要将所加载的水印从$D$中提取出来,其过程为上述加载水印算法的逆运算： 

1. 将$D$分解为$(M/8)\times (N/8)$个$8\times 8$大小的方块$BD$； 
2. 对每一个$BD$进行二维$DCT$变换:$DBD=DCT(BD)$； 
3. 对每一个$DBD$提取数据，按照式$V^{\prime}=1/A\times DBD$得到$V^{\times}$；
4.  将上面得到的所有$V^{\prime}$合并成一个水印整图$J^{\prime}$。 