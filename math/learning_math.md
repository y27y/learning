# 深度学习数学全景手册
---

## 目录

**第一部分 基础回顾**
1. 线性代数
2. 微积分与矩阵微积分
3. 概率论
4. 数理统计
5. 数值计算基础

**第二部分 核心工具**
6. 信息论
7. 最优化
8. 概率图模型与推断
9. 蒙特卡洛与采样
10. 学习理论（选学）

**第三部分 进阶与专项**
11. 泛函分析、核方法与函数空间
12. 图论与谱方法
13. 微分方程与连续动力系统
14. 张量代数
15. 群论与对称性
16. 最优传输与概率度量
17. 测度论与严格概率基础（选学）
18. 博弈论与多智能体（简要）

**第四部分 应用与路线**
19. 模型—数学对照表
20. 学习路线、教材与自测清单

---

# 第一部分 基础回顾

## 1. 线性代数【核心】

### 1.1 向量空间与线性映射
- 线性组合、张成（span）、线性无关、基、维数。
- 子空间：列空间 $C(A)$、零空间 $N(A)$；**秩-零化度定理**：$\mathrm{rank}(A)+\dim N(A)=n$（$A\in\mathbb{R}^{m\times n}$）。
- 线性映射就是矩阵；基变换、相似矩阵 $B=P^{-1}AP$。
- 仿射空间、凸组合、单纯形（softmax 的输出就在单纯形上）。

### 1.2 内积、范数与投影
- 内积、Cauchy–Schwarz、夹角、正交、正交补。
- 投影：$P=A(A^\top A)^{-1}A^\top$；正交基与 Gram–Schmidt、QR 分解。
- 向量范数：$\ell_1,\ell_2,\ell_\infty,\ell_p$。
- 矩阵范数：Frobenius $\|A\|_F$、谱范数 $\|A\|_2=\sigma_{\max}$、核范数 $\|A\|_*=\sum\sigma_i$。
- 对偶范数（【选学】）：$\|x\|_*=\sup_{\|y\|\le1}x^\top y$。

### 1.3 矩阵运算与分解
- 逆、伪逆（Moore–Penrose）$A^+=V\Sigma^+U^\top$；行列式＝体积缩放；迹。
- 分解：LU、QR、Cholesky（正定）、特征分解、SVD。
- 秩、条件数 $\kappa(A)=\|A\|\|A^+\|=\sigma_{\max}/\sigma_{\min}$。

### 1.4 特征值分解
- $Av=\lambda v$，谱、谱半径、对角化 $A=Q\Lambda Q^{-1}$。
- 实对称矩阵：$A=Q\Lambda Q^\top$，特征向量正交；正定/半正定 $\Leftrightarrow$ 特征值全正/非负。
- Rayleigh 商 $R(x)=\dfrac{x^\top Ax}{x^\top x}$，极值即 $\lambda_{\min},\lambda_{\max}$。
- 谱定理、Perron–Frobenius（【选学】，用于 Markov 链/PageRank）。

### 1.5 SVD 与低秩近似
- $A=U\Sigma V^\top$；奇异值、左右奇异向量。
- **Eckart–Young**：$A_k=\sum_{i\le k}\sigma_i u_iv_i^\top$ 是秩 $k$ 下的最优 Frobenius 近似。
- PCA＝对中心化数据协方差矩阵做特征分解，也等于对数据矩阵做 SVD。
- 低秩分解：LoRA、矩阵补全、推荐系统。

### 1.6 张量（详见第 14 章）
- 多维数组、广播、`einsum`、mode-$n$ 乘积、CP/Tucker 分解。

### 1.7 数值线性代数
- 复杂度：矩阵乘 $O(n^3)$、求逆 $O(n^3)$、SVD $O(n^3)$；稀疏矩阵、迭代法（共轭梯度、Lanczos）。
- 病态矩阵、条件数与误差放大。

### 1.8 在 DL 中怎么用
- 全连接层 $y=Wx+b$；卷积可写成 Toeplitz/循环矩阵乘法（卷积定理）。
- 注意力 $\mathrm{softmax}(QK^\top/\sqrt{d})V$ 本质是相似度矩阵＋加权平均。
- Embedding 低秩假设、权重衰减、谱归一化、BatchNorm 的白化思想、LoRA 的低秩更新。

**常见坑**：把“特征值”和“奇异值”混用；忘记非方阵没有特征值只有奇异值；把 $\|A\|_2$ 当成元素平方和。

---

## 2. 微积分与矩阵微积分【核心】

### 2.1 一元回顾
- 导数、链式法则、乘积/商法则、Taylor 展开、积分、分部积分、换元。
- 常用极限与等价无穷小；$e^x$、$\log x$、$\sigma(x)$ 的导数。

### 2.2 多元微分
- 偏导、梯度 $\nabla f$、方向导数 $D_vf=\nabla f^\top v$。
- Jacobian $J_{ij}=\partial f_i/\partial x_j$；Hessian $H_{ij}=\partial^2 f/\partial x_i\partial x_j$。
- 二阶 Taylor：$f(x+\Delta)\approx f(x)+\nabla f^\top\Delta+\tfrac12\Delta^\top H\Delta$。
- 用 Hessian 特征值判断局部凸/凹/鞍点。

### 2.3 矩阵微积分（务必背熟几个）
- $\dfrac{\partial(a^\top x)}{\partial x}=a$，$\dfrac{\partial(x^\top Ax)}{\partial x}=(A+A^\top)x$
- $\dfrac{\partial\|Ax-b\|^2}{\partial x}=2A^\top(Ax-b)$
- $\dfrac{\partial\,\mathrm{Tr}(AB)}{\partial A}=B^\top$，$\dfrac{\partial\log\det A}{\partial A}=A^{-\top}$
- $\dfrac{\partial\|A\|_F^2}{\partial A}=2A$
- $\dfrac{\partial\sigma_{\max}(A)}{\partial A}=u_1v_1^\top$（次梯度）
- 注意**布局约定**（分母布局/分子布局），不同教材转置相反。

### 2.4 链式法则与反向传播
- 标量对向量、向量对向量的链式法则＝Jacobian 连乘。
- 反向传播：$\delta^l=(W^{l+1})^\top\delta^{l+1}\odot\sigma'(z^l)$，$\partial L/\partial W^l=\delta^l(a^{l-1})^\top$。
- 计算图、VJP（向量-雅可比积）与 JVP；反向模式复杂度约为前向的常数倍。

### 2.5 自动微分
- 前向模式 vs 反向模式；为什么 DL 用反向模式（输出是标量，参数多）。
- 计算图、伴随（adjoint）、 checkpointing（用时间换显存）。

### 2.6 积分与特殊函数
- 期望＝积分；卷积 $(f*g)(t)=\int f(\tau)g(t-\tau)d\tau$。
- 高斯积分、Gamma/Beta 函数、误差函数。
- 傅里叶变换与卷积定理（【进阶】，CNN/信号处理）。

### 2.7 凸性初步（详见第 7 章）
- 凸集、凸函数；一阶条件 $f(y)\ge f(x)+\nabla f(x)^\top(y-x)$；二阶条件 $H\succeq0$。
- Jensen 不等式：$f(\mathbb{E}X)\le\mathbb{E}f(X)$（凸函数）。

### 2.8 隐函数定理与可微编程
- $\dfrac{\partial y}{\partial x}=-\left(\dfrac{\partial F}{\partial y}\right)^{-1}\dfrac{\partial F}{\partial x}$。
- 隐式微分：Deep Equilibrium Model、优化层、可微渲染。

### 2.9 在 DL 中怎么用
- 所有 loss 的梯度推导、自定义算子、梯度检查、二阶优化（牛顿/自然梯度）、Neural ODE 的伴随法。

**常见坑**：矩阵求导转置错位；对 softmax 直接求导忘记减均值；把 $\log$ 的底数搞混（DL 默认自然对数）。

---

## 3. 概率论【核心】

### 3.1 概率空间
- 样本空间、事件、σ-代数（了解即可）、概率测度、条件概率、全概率公式、贝叶斯公式。
- 独立性、条件独立（概率图模型的基础）。

### 3.2 随机变量与分布
- 离散/连续、PMF/PDF/CDF、联合/边缘/条件分布。
- 变量替换：$p_Y(y)=p_X(x)\left|\det\dfrac{\partial x}{\partial y}\right|$（归一化流的核心）。
- 卷积：独立变量之和的分布。

### 3.3 数字特征
- 期望、方差、协方差、相关系数、协方差矩阵、矩、矩母函数/特征函数。
- $\mathrm{Var}(X)=\mathbb{E}[X^2]-\mathbb{E}[X]^2$；$\mathrm{Var}(aX+b)=a^2\mathrm{Var}(X)$。
- 协方差矩阵半正定；白化 $z=\Sigma^{-1/2}(x-\mu)$。

### 3.4 常见分布速查

| 分布                | 参数           | 均值                          | 方差                                                   | DL 中的用途         |
|---------------------|----------------|-------------------------------|--------------------------------------------------------|---------------------|
| Bernoulli           | $p$            | $p$                           | $p(1-p)$                                               | 二分类、Dropout      |
| Categorical         | $\pi$          | —                             | —                                                      | 多分类、语言模型     |
| Binomial            | $n,p$          | $np$                          | $np(1-p)$                                              | 计数                |
| Poisson             | $\lambda$      | $\lambda$                     | $\lambda$                                              | 计数数据、泊松回归   |
| Uniform             | $a,b$          | $(a+b)/2$                     | $(b-a)^2/12$                                           | 初始化、采样         |
| Normal              | $\mu,\sigma^2$ | $\mu$                         | $\sigma^2$                                             | 权重初始化、噪声、VAE |
| Multivariate Normal | $\mu,\Sigma$   | $\mu$                         | $\Sigma$                                               | 高斯过程、VAE、扩散   |
| Exponential         | $\lambda$      | $1/\lambda$                   | $1/\lambda^2$                                          | 生存分析、稀疏先验   |
| Gamma               | $\alpha,\beta$ | $\alpha/\beta$                | $\alpha/\beta^2$                                       | 精度先验            |
| Beta                | $\alpha,\beta$ | $\frac{\alpha}{\alpha+\beta}$ | $\frac{\alpha\beta}{(\alpha+\beta)^2(\alpha+\beta+1)}$ | 伯努利先验、比例     |
| Dirichlet           | $\alpha$       | $\alpha_i/\alpha_0$           | —                                                      | 主题模型、分类先验   |
| Laplace             | $\mu,b$        | $\mu$                         | $2b^2$                                                 | L1 正则的贝叶斯解释 |
| Student-t           | $\nu$          | $0$（$\nu>1$）                  | $\frac{\nu}{\nu-2}$（$\nu>2$）                           | 鲁棒建模、重尾       |
| Multinomial         | $n,\pi$        | $n\pi$                        | —                                                      | 词频、计数           |

### 3.5 多元高斯（重点）
- 密度：$\mathcal{N}(x|\mu,\Sigma)=(2\pi)^{-d/2}|\Sigma|^{-1/2}\exp\!\big(-\tfrac12(x-\mu)^\top\Sigma^{-1}(x-\mu)\big)$。
- 线性变换：$Ax+b\sim\mathcal{N}(A\mu+b,A\Sigma A^\top)$。
- 边缘：$x_1\sim\mathcal{N}(\mu_1,\Sigma_{11})$。
- 条件：$x_1|x_2\sim\mathcal{N}\big(\mu_1+\Sigma_{12}\Sigma_{22}^{-1}(x_2-\mu_2),\ \Sigma_{11}-\Sigma_{12}\Sigma_{22}^{-1}\Sigma_{21}\big)$。
- 高斯×高斯共轭、精度矩阵、Cholesky 采样。

### 3.6 极限定理
- 大数定律（弱/强）：样本均值收敛到期望。
- 中心极限定理：$\sqrt{n}(\bar X-\mu)/\sigma\Rightarrow\mathcal{N}(0,1)$。

### 3.7 集中不等式【进阶】
- Markov：$P(X\ge a)\le\mathbb{E}X/a$。
- Chebyshev：$P(|X-\mu|\ge k\sigma)\le1/k^2$。
- Hoeffding：$P(|\bar X-\mathbb{E}X|\ge t)\le2\exp\!\big(-2nt^2/(b-a)^2\big)$。
- Chernoff 界、McDiarmid 不等式、亚高斯/亚指数分布。
- 用途：泛化界、采样复杂度、随机算法分析。

### 3.8 指数族与共轭先验【进阶】
- $p(x|\theta)=h(x)\exp(\eta(\theta)^\top T(x)-A(\theta))$；$T(x)$ 为充分统计量。
- 共轭先验：Beta–Bernoulli、Dirichlet–Categorical、Normal–Normal、Gamma–Poisson。
- 用途：广义线性模型、变分推断、主题模型。

### 3.9 贝叶斯推断
- 先验、似然、后验、后验预测分布。
- MLE、MAP、贝叶斯估计（后验均值/中位数）。
- 变分推断、MCMC（第 8、9 章）。

### 3.10 随机过程（简述）【进阶】
- Markov 链、平稳分布、混合时间；Poisson 过程；Brownian 运动；SDE。
- 用途：强化学习、扩散模型、MCMC 收敛。

**常见坑**：把“独立”与“不相关”等同（仅高斯下等价）；连续分布点概率为 0；KL 不对称。

---

## 4. 数理统计【核心】

### 4.1 估计量性质
- 无偏性、一致性、有效性、均方误差 $\mathrm{MSE}=\mathrm{Bias}^2+\mathrm{Var}$。
- 偏差-方差分解：$\mathbb{E}[(y-\hat y)^2]=\mathrm{Bias}^2+\mathrm{Var}+\sigma^2$。

### 4.2 经典估计
- 最大似然：$\hat\theta=\arg\max\sum_i\log p(x_i|\theta)$。
- 最小二乘＝高斯噪声下的 MLE。
- 岭回归闭式解：$\hat w=(X^\top X+\lambda I)^{-1}X^\top y$，等价于高斯先验的 MAP。
- Lasso＝Laplace 先验的 MAP，产生稀疏解。

### 4.3 Fisher 信息与下界【进阶】
- $I(\theta)=\mathbb{E}[(\nabla_\theta\log p)^2]=-\mathbb{E}[\nabla^2_\theta\log p]$。
- Cramér–Rao：$\mathrm{Var}(\hat\theta)\ge1/(nI(\theta))$。
- 用途：自然梯度、实验设计、置信区间。

### 4.4 模型选择与评估
- 交叉验证、留一法、bootstrap、置信区间、假设检验（t 检验、卡方检验）。
- AIC/BIC、Occam 剃刀、正则化路径。

### 4.5 经验风险最小化
- $\hat R(f)=\frac1n\sum_i\ell(f(x_i),y_i)$；泛化误差＝经验风险＋复杂度项。
- 与第 10 章学习理论衔接。

**常见坑**：把训练误差当泛化误差；数据泄漏；用测试集调参。

---

## 5. 数值计算基础【核心】

- IEEE 754：float16/bfloat16/float32/float64；机器精度、舍入误差、上溢/下溢。
- 灾难性抵消（大数相减）、数值稳定性、条件数。
- **log-sum-exp 技巧**：$\log\sum_i e^{x_i}=m+\log\sum_i e^{x_i-m}$，$m=\max x_i$；softmax、交叉熵、HMM 前向算法必用。
- 矩阵分解的稳定性（Cholesky vs 直接求逆）；避免显式求逆，用 solve。
- 迭代法：共轭梯度、幂迭代、Lanczos。
- 随机数生成、种子、可复现性；混合精度训练（loss scaling）。

**常见坑**：直接算 $\log(0)$、$\exp$ 溢出；用 float16 累加梯度；忘记 $-\infty$ 的处理。

---

# 第二部分 核心工具

## 6. 信息论【核心】

- 熵：$H(X)=-\sum p\log p$；微分熵 $h(X)=-\int p\log p$。
- 联合熵、条件熵、链式法则 $H(X,Y)=H(X)+H(Y|X)$。
- 互信息：$I(X;Y)=H(X)-H(X|Y)=H(X)+H(Y)-H(X,Y)=\mathrm{KL}(p(x,y)\|p(x)p(y))$。
- KL 散度：$\mathrm{KL}(p\|q)=\mathbb{E}_p\log\frac{p}{q}\ge0$，**不对称**，不满足三角不等式。
- 交叉熵：$H(p,q)=H(p)+\mathrm{KL}(p\|q)$；分类损失就是它。
- JS 散度、$f$-散度：$D_f(p\|q)=\int q\,f(p/q)$；GAN 与变分推断的理论来源。
- 数据处理不等式：若 $X\to Y\to Z$ 构成 Markov 链，则 $I(X;Z)\le I(X;Y)$。
- 最大熵原理：给定均值方差，高斯熵最大；给定支撑，均匀分布熵最大。
- 速率-失真理论、信息瓶颈（【进阶】）。

**在 DL 中**：交叉熵损失、softmax 梯度 $\partial L/\partial z=p-y$、VAE 的 KL 项、互信息最大化（InfoNCE/对比学习）、决策树的信息增益。

**常见坑**：KL 方向写反（$D_{KL}(p\|q)$ vs $D_{KL}(q\|p)$ 行为完全不同）；连续熵可为负。

---

## 7. 最优化【核心】

### 7.1 凸优化基础
- 凸集、凸函数、强凸（$f(y)\ge f(x)+\nabla f^\top(y-x)+\frac{\mu}{2}\|y-x\|^2$）、$L$-光滑（$\|\nabla f(x)-\nabla f(y)\|\le L\|x-y\|$）。
- 一阶/二阶最优性条件；局部最优＝全局最优（凸）。
- 对偶理论、拉格朗日函数、KKT 条件、强对偶（Slater 条件）。
- 共轭函数、次梯度（不可导点，如 L1、ReLU、max）。

### 7.2 一阶方法
- 梯度下降：$x_{k+1}=x_k-\eta\nabla f(x_k)$。
- 收敛率：凸 $O(1/k)$；强凸＋光滑线性收敛 $O((1-\mu/L)^k)$；非凸收敛到驻点 $O(1/\sqrt{k})$。
- 步长选择：固定、衰减、线搜索（Armijo）、回溯。
- 动量、Nesterov 加速（凸下最优 $O(1/k^2)$）。
- 随机梯度：无偏但方差大；mini-batch、方差缩减（SVRG、SAGA）【进阶】。

### 7.3 自适应方法（背下更新式）
- AdaGrad：$x_{k+1}=x_k-\eta\,g_k/\sqrt{\sum_{i\le k}g_i^2+\epsilon}$。
- RMSProp：指数滑动平均二阶矩。
- Adam：$m_t=\beta_1m_{t-1}+(1-\beta_1)g_t$，$v_t=\beta_2v_{t-1}+(1-\beta_2)g_t^2$，偏差修正 $\hat m_t=m_t/(1-\beta_1^t)$，$\hat v_t=v_t/(1-\beta_2^t)$，$x_{k+1}=x_k-\eta\hat m_t/(\sqrt{\hat v_t}+\epsilon)$。
- AdamW：解耦权重衰减；LAMB（大 batch）。

### 7.4 二阶方法
- 牛顿法：$x_{k+1}=x_k-H^{-1}\nabla f$；二次收敛但 $O(n^3)$。
- 拟牛顿：BFGS/L-BFGS（低秩近似 Hessian）。
- Gauss–Newton、Levenberg–Marquardt（最小二乘）。
- 自然梯度：$\theta\leftarrow\theta-\eta F^{-1}\nabla L$，$F$ 为 Fisher 信息；K-FAC 近似。
- 信赖域方法【进阶】。

### 7.5 约束优化
- 等式约束：拉格朗日乘子；不等式：KKT。
- 投影梯度、罚函数、增广拉格朗日、ADMM【进阶】。
- 内点法【选学】。

### 7.6 正则化与近端方法
- L2（权重衰减）、L1（稀疏）、弹性网、dropout、early stopping、数据增强。
- 近端算子：$\mathrm{prox}_{\eta g}(x)=\arg\min_z\frac12\|z-x\|^2+\eta g(z)$。
- 软阈值：$S_\lambda(x)=\mathrm{sign}(x)\max(|x|-\lambda,0)$；ISTA/FISTA。
- 隐式正则：SGD 的噪声、平坦极小值、大 batch 泛化。

### 7.7 非凸优化现象
- 鞍点、平台、病态曲率；逃逸鞍点；批归一化/残差连接对优化的作用。
- 过参数化、彩票假说、grokking（了解）。

**常见坑**：学习率与 batch size 的缩放关系；Adam 的 $\epsilon$ 位置；权重衰减与 L2 在自适应优化下不等价。

---

## 8. 概率图模型与推断【进阶】

- 有向图（贝叶斯网络）、无向图（马尔可夫随机场）、因子图。
- 条件独立、d-分离、Markov 毯。
- 推断：变量消元、信念传播、前向-后向算法（HMM）、维特比算法（MAP）。
- 精确推断的复杂度；树宽。
- 近似推断：变分推断（ELBO）、平均场、期望传播、MCMC。
- ELBO：$\log p(x)\ge\mathbb{E}_{q(z)}[\log p(x,z)-\log q(z)]=\mathbb{E}_q[\log p(x|z)]-\mathrm{KL}(q(z)\|p(z))$。
- 重参数化技巧：$z=\mu+\sigma\odot\epsilon$，$\epsilon\sim\mathcal{N}(0,I)$。
- 应用：HMM/CRF、VAE、扩散模型的变分视角、贝叶斯网络。

**常见坑**：ELBO 的 KL 方向；平均场假设过强；把后验当先验。

---

## 9. 蒙特卡洛与采样【进阶】

- 逆变换采样、拒绝采样、重要性采样（及其方差）。
- MCMC：Metropolis–Hastings、Gibbs 采样、混合时间、burn-in、收敛诊断（$\hat R$、ESS）。
- 哈密顿蒙特卡洛（HMC）、Langevin 动力学。
- 退火、并行回火、切片采样。
- 采样与优化的联系：Langevin 采样＝带噪声的梯度下降；扩散模型的采样。
- 方差缩减：控制变量、Rao–Blackwell、分层抽样。

**在 DL 中**：Dropout 的贝叶斯解释、MC Dropout 不确定性、VAE 采样、扩散模型、强化学习中的探索。

---

## 10. 学习理论【选学】

- PAC 学习、假设空间、VC 维、Rademacher 复杂度、覆盖数。
- 泛化界、均匀收敛、稳定性。
- 偏差-方差-复杂度权衡；双下降现象。
- 隐式正则、NTK（神经正切核）、无限宽网络。
- 用途：理解“为什么过参数化还能泛化”，但工程上优先级低。

---

# 第三部分 进阶与专项

## 11. 泛函分析、核方法与函数空间【进阶】

- 希尔伯特空间、$L^2$ 空间、内积、正交基、完备性。
- 算子、紧算子、谱定理（了解）。
- 核函数 $k(x,x')=\langle\phi(x),\phi(x')\rangle$；Mercer 定理；RKHS。
- 表示定理：最优解可写成 $\sum_i\alpha_i k(x_i,\cdot)$。
- 应用：SVM、核 PCA、高斯过程、核密度估计。
- 函数范数、TV 距离、Wasserstein（见第 16 章）。
- 变分法：泛函极值、Euler–Lagrange 方程（Neural ODE、能量模型）。

---

## 12. 图论与谱方法【进阶】

- 图、度矩阵 $D$、邻接矩阵 $A$、拉普拉斯 $L=D-A$。
- 归一化拉普拉斯 $L_{\mathrm{sym}}=I-D^{-1/2}AD^{-1/2}$，特征值 $\in[0,2]$。
- 连通分量数＝$L$ 的零特征值重数；Fiedler 向量（谱聚类）。
- 随机游走、PageRank、个性化 PageRank。
- 图卷积：$H'=\sigma(\tilde D^{-1/2}\tilde A\tilde D^{-1/2}HW)$。
- 消息传递框架、GAT、GraphSAGE、图池化。
- 组合计数、生成函数（【选学】）。

---

## 13. 微分方程与连续动力系统【进阶】

- ODE、初值问题、Euler 法、Runge–Kutta、稳定性、刚性方程。
- ResNet 作为离散 ODE：$h_{t+1}=h_t+f(h_t,\theta_t)$。
- Neural ODE：$\frac{dh}{dt}=f(h,t,\theta)$；伴随法反向传播。
- SDE：$dx=f(x,t)dt+g(t)dw$；Fokker–Planck 方程；Langevin 方程。
- 扩散模型：前向 $x_t=\sqrt{\bar\alpha_t}x_0+\sqrt{1-\bar\alpha_t}\epsilon$；反向去噪；score matching；概率流 ODE。
- PDE 与 PINN（物理信息神经网络）【选学】。

---

## 14. 张量代数【进阶】

- 张量 $X\in\mathbb{R}^{I_1\times\cdots\times I_N}$；纤维、切片。
- mode-$n$ 乘积、张量秩、CP 分解 $X\approx\sum_r a_r\circ b_r\circ c_r$、Tucker 分解。
- 张量网络、矩阵化（matricization）。
- `einsum` 表达：`ij,jk->ik` 等；广播规则。
- 应用：注意力、卷积、多维特征、张量分解压缩。

---

## 15. 群论与对称性【选学】

- 群、子群、同态、表示 $\rho:G\to GL(V)$。
- 不变性 $f(\rho(g)x)=f(x)$ 与等变性 $f(\rho(g)x)=\rho'(g)f(x)$。
- 卷积作为平移等变算子；$G$-卷积、可操控卷积（steerable CNN）。
- 应用：CNN 平移等变、旋转等变网络、图同构、分子建模。

---

## 16. 最优传输与概率度量【进阶】

- 传输计划、Wasserstein 距离 $W_p$；一维闭式解。
- Kantorovich 对偶：$W_1(p,q)=\sup_{\|f\|_L\le1}\mathbb{E}_p f-\mathbb{E}_q f$。
- Sinkhorn 算法、熵正则。
- 与 KL 的区别：Wasserstein 在支撑不重叠时仍有梯度。
- 应用：WGAN、分布匹配、域适应、生成模型评估（FID 的数学基础）。

---

## 17. 测度论与严格概率基础【选学】

- σ-代数、测度、可测函数、Lebesgue 积分、单调收敛/控制收敛。
- 绝对连续、Radon–Nikodym 导数、密度存在性。
- 乘积测度、Fubini 定理。
- 为什么需要：连续分布、KL 的严格定义、变分推断、随机过程。
- 工程上不必精通，但读到“dominated convergence”“absolutely continuous”时要知道在说什么。

---

## 18. 博弈论与多智能体（简要）【选学】

- 零和博弈、minimax 定理、Nash 均衡。
- GAN：$\min_G\max_D\mathbb{E}_{x\sim p_{\text{data}}}\log D(x)+\mathbb{E}_{z}\log(1-D(G(z)))$。
- 最优判别器与 JS 散度的关系；WGAN 与积分概率度量。
- 演化博弈、复制者动态（了解）。

---

# 第四部分 应用与路线

## 19. 模型—数学对照表

| 技术/模型    | 核心数学           | 关键概念/公式              |
|--------------|--------------------|----------------------------|
| 线性回归     | 线代＋统计          | 最小二乘、伪逆、高斯-MLE     |
| 逻辑回归     | 凸优化＋信息论      | sigmoid、交叉熵、凸性        |
| Softmax 分类 | 线代＋信息论        | softmax、CE 梯度 $p-y$      |
| PCA          | 线代               | SVD、协方差特征分解         |
| SVM          | 凸优化＋核方法      | 对偶、KKT、Mercer 核         |
| GMM/EM       | 概率＋优化          | 隐变量、ELBO、Jensen         |
| HMM/CRF      | 概率图             | 前向-后向、维特比           |
| VAE          | 变分推断           | ELBO、重参数化、KL           |
| GAN          | 博弈论＋散度        | minimax、JS/Wasserstein     |
| 扩散模型     | SDE＋score matching | 前向加噪、反向去噪、PF-ODE   |
| Transformer  | 线代＋概率          | 注意力、softmax、LayerNorm   |
| GNN          | 图论＋谱方法        | 拉普拉斯、消息传递          |
| BatchNorm    | 统计               | 批统计、白化、协变量偏移     |
| Dropout      | 概率＋贝叶斯        | 随机掩码、模型平均          |
| 权重衰减/L1  | 优化＋贝叶斯        | 高斯/Laplace 先验、近端算子 |
| 初始化       | 概率＋线代          | 方差保持、谱半径、正交初始化 |
| 强化学习     | 概率＋动态规划      | Bellman 方程、策略梯度、TD   |
| 对比学习     | 信息论             | InfoNCE、互信息下界         |
| LoRA         | 线代               | 低秩分解、SVD               |
| 量化/蒸馏    | 数值计算           | 浮点、误差、KL               |

---

## 20. 学习路线、教材与自测清单

### 20.1 三阶段路线（约 8–12 周，按每天 1–2 小时）

**阶段一：补基础（2–3 周）**
- 线代：Strang《Linear Algebra and Its Applications》或 Axler《Linear Algebra Done Right》；重点：SVD、特征分解、投影。
- 微积分：多变量＋矩阵求导；配合《The Matrix Cookbook》查公式。
- 概率：Bertsekas《Introduction to Probability》或 Blitzstein 的 Stat 110；重点：多元高斯、条件期望、集中不等式。
- 统计：MLE/MAP、偏差-方差、Fisher 信息。

**阶段二：核心工具（3–4 周）**
- 优化：Boyd《Convex Optimization》前 5 章＋Nocedal & Wright 的 SGD/拟牛顿章节。
- 信息论：Cover & Thomas 前 2 章，或 MacKay 的 ITILT 前几章。
- 概率图/变分：Bishop《PRML》第 8、10 章；Murphy《ML: A Probabilistic Perspective》。
- 配套教材：Deisenroth《Mathematics for Machine Learning》（最贴合 DL 的数学书）、Goodfellow《Deep Learning》第二部分、《Dive into Deep Learning》数学附录。

**阶段三：专项（按方向选，2–4 周）**
- 生成模型：扩散模型 → SDE/score matching/最优传输。
- GNN：图论/谱方法。
- 理论：学习理论、NTK。
- 强化学习：动态规划、随机过程。

### 20.2 自测清单（能独立推导即过关）

1. 两层网络的反向传播，写出 $\partial L/\partial W$ 的完整推导。
2. softmax＋交叉熵的梯度为什么是 $p-y$。
3. 岭回归闭式解，并说明它对应什么先验的 MAP。
4. 用 SVD 解释 PCA 和 LoRA。
5. 写出多元高斯的条件分布公式，并说明在 Gaussian Process 中的作用。
6. 写出 ELBO，解释两项各自的含义，说明 KL 的方向为什么不能反。
7. Adam 的完整更新式与偏差修正的作用。
8. 牛顿法、自然梯度、Fisher 信息三者的关系。
9. 写出 GCN 的传播公式，并解释拉普拉斯矩阵特征值的含义。
10. 写出扩散模型前向过程与反向去噪的目标函数。
11. 解释 KL 与 Wasserstein 的区别，为什么 WGAN 更稳定。
12. 用 Hoeffding 不等式说明样本复杂度。

### 20.3 十个最该背下来的公式

1. $\nabla_x\|Ax-b\|^2=2A^\top(Ax-b)$
2. $\partial\,\mathrm{KL}(p\|q)/\partial q$ 与 CE 梯度 $p-y$
3. 高斯密度与条件高斯
4. 贝叶斯公式与 MLE/MAP
5. 偏差-方差分解
6. 熵/KL/互信息三者的关系
7. 凸性一阶/二阶条件与 Jensen
8. GD/SGD/Adam 更新式
9. KKT 条件
10. SVD 与 Eckart–Young

### 20.4 常见误区汇总
- “独立”≠“不相关”（仅高斯成立）。
- KL 不对称，不能当距离。
- 特征值只对方阵，奇异值对所有矩阵。
- 矩阵求导注意布局约定。
- 交叉熵损失里 $\log$ 是自然对数，别和 $\log_2$ 混。
- softmax 数值不稳定，必须减最大值。
- 正则化不是“让模型简单”，而是引入先验/约束。
- 泛化误差≠训练误差，测试集不能调参。

---

**一句话总结**：深度学习的数学主干是「线代（表示）＋微积分（求导）＋概率统计（建模不确定性）＋优化（求解）＋信息论（目标函数）」，其余（图论、微分方程、泛函、群论、最优传输）是按方向选修的“外挂”。把第 1–7 章吃透，再按第 19 章的对照表补专项，就足够覆盖绝大多数论文和工程需求。