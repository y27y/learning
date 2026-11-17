# ============ 0. 环境与数据 ============
import math
import torch
from torch import nn
from torch.nn import functional as F
from d2l import torch as d2l

batch_size, num_steps = 32, 35                    # 每批 32 条序列，每条长 35 个词元
train_iter, vocab = d2l.load_data_time_machine(batch_size, num_steps)
                                                  # 8.3 的 (X, Y)：X=(32,35) 索引, Y=X 右移一位
                                                  # 时光机器按字符分词，词表大小 len(vocab)=28


# ============ 1. 把整数索引变成 one-hot 向量 ============
# 输入是索引，模型要的是向量，所以先 one-hot 成 (词表大小) 维的 0/1 向量
F.one_hot(torch.tensor([0, 2]), len(vocab))       # 形状 (2, 28)：第 0 行第 0 位是 1，第 1 行第 2 位是 1

X = torch.arange(10).reshape((2, 5))              # 造一个 (batch=2, num_steps=5) 的假输入
F.one_hot(X.T, 28).shape                          # 先转置成 (5, 2) 再 one-hot → (5, 2, 28)
                                                  # ★ 必须转置：RNN 要按"时间步"循环，
                                                  #   第一维变成时间步，每次取出的 X 是 (batch, vocab)


# ============ 2. 初始化参数 ============
def get_params(vocab_size, num_hiddens, device):
    num_inputs = num_outputs = vocab_size         # 输入/输出都是词表大小（one-hot 维度）

    def normal(shape):
        return torch.randn(size=shape, device=device) * 0.01
                                                  # 小方差随机初始化，避免一开始 tanh 就饱和

    W_xh = normal((num_inputs, num_hiddens))      # (28, 512)  输入 → 隐藏
    W_hh = normal((num_hiddens, num_hiddens))     # (512, 512) 隐藏 → 隐藏（循环权重）
    b_h = torch.zeros(num_hiddens, device=device) # (512,)     隐藏层偏置，初始置 0
    W_hq = normal((num_hiddens, num_outputs))     # (512, 28)  隐藏 → 输出
    b_q = torch.zeros(num_outputs, device=device) # (28,)      输出层偏置

    params = [W_xh, W_hh, b_h, W_hq, b_q]
    for param in params:
        param.requires_grad_(True)                # 手动开启梯度（因为不是 nn.Parameter）
    return params                                 # 总参数量 = 28*512 + 512*512 + 512 + 512*28 + 28


# ============ 3. 初始化隐藏状态 ============
def init_rnn_state(batch_size, num_hiddens, device):
    return (torch.zeros((batch_size, num_hiddens), device=device), )
                                                  # 返回"元组"，而不是单个张量
                                                  # ★ 为了接口通用：LSTM 需要 (H, C) 两个状态
                                                  # 形状 (32, 512)：每条序列一个隐藏向量


# ============ 4. 核心：一个时间步的 RNN 计算 ============
def rnn(inputs, state, params):
    W_xh, W_hh, b_h, W_hq, b_q = params           # 拆出 5 组参数
    H, = state                                    # 解包出隐藏状态，(batch, 512)
    outputs = []                                  # 收集每个时间步的输出
    for X in inputs:                              # inputs: (num_steps, batch, vocab)
                                                  # 循环一次就是一个时间步，X 是 (batch, vocab)
        H = torch.tanh(torch.mm(X, W_xh) + torch.mm(H, W_hh) + b_h)
                                                  # H_t = tanh(X_t·W_xh + H_{t-1}·W_hh + b_h)
                                                  # 两项都是 (batch, 512)，相加后还是 (batch, 512)
        Y = torch.mm(H, W_hq) + b_q               # Y_t = H_t·W_hq + b_q → (batch, 28) 未归一化分数
        outputs.append(Y)                         # 存下这个时间步的输出
    return torch.cat(outputs, dim=0), (H,)
                                                  # ★ 沿时间维拼起来 → (num_steps*batch, 28)
                                                  #   行序是"时间优先"：t0_b0, t0_b1, t1_b0, ...
                                                  # 返回值也必须是元组，和 init_rnn_state 对齐


# ============ 5. 把上面拼成一个"模型" ============
class RNNModelScratch:
    def __init__(self, vocab_size, num_hiddens, device, get_params, init_state, forward_fn):
        self.vocab_size, self.num_hiddens = vocab_size, num_hiddens
        self.params = get_params(vocab_size, num_hiddens, device)
                                                  # 参数存在 self.params 这个 list 里
        self.init_state, self.forward_fn = init_state, forward_fn
                                                  # 把三个函数当"策略"传进来，方便换实现

    def __call__(self, X, state):                 # ★ 实现了 __call__，所以 net(X, state) 可用
        X = F.one_hot(X.T, self.vocab_size).type(torch.float32)
                                                  # X: (batch, num_steps) → 转置 (num_steps, batch)
                                                  # → one-hot (num_steps, batch, vocab) → 转 float32
        return self.forward_fn(X, state, self.params)   # 调 rnn()，返回 (y_hat, new_state)

    def begin_state(self, batch_size, device):
        return self.init_state(batch_size, self.num_hiddens, device)
                                                  # 统一入口：新序列/新 batch 从这里拿初始状态


num_hiddens = 512
net = RNNModelScratch(len(vocab), num_hiddens, d2l.try_gpu(),
                      get_params, init_rnn_state, rnn)

state = net.begin_state(X.shape[0], d2l.try_gpu())    # X 是上面那个 (2,5) 的假输入 → state 是 (2,512)
Y, new_state = net(X.to(d2l.try_gpu()), state)
Y.shape, len(new_state), new_state[0].shape           # (10, 28) / 1 / (2, 512)
                                                  # 10 = num_steps(5) × batch(2)：每个 (t, b) 一个 28 维输出


# ============ 6. 预测：给定前缀，续写 ============
def predict_ch8(prefix, num_preds, net, vocab, device):
    state = net.begin_state(batch_size=1, device=device)   # 只有 1 条序列
    outputs = [vocab[prefix[0]]]                   # 先把前缀第一个字符转成索引，outputs 存索引
    get_input = lambda: torch.tensor([outputs[-1]], device=device).reshape((1, 1))
                                                  # 取"上一个输出"作为这一步输入，形状 (1,1)
    for y in prefix[1:]:                           # 前缀剩下的字符：只用来"喂"，不预测
        _, state = net(get_input(), state)         # ★ 跑一遍只为更新 state（预热/建立上下文）
        outputs.append(vocab[y])                   # ★ 强制把真实字符塞回去，不让模型猜
    for _ in range(num_preds):                     # 开始自由生成
        y, state = net(get_input(), state)         # y: (1, 28) 分数
        outputs.append(int(y.argmax(dim=1).reshape(1)))   # ★ 贪心：取分数最大的那个词的索引
    return ''.join([vocab.idx_to_token[i] for i in outputs])   # 索引 → 字符 → 拼成字符串


predict_ch8('time traveller ', 10, net, vocab, d2l.try_gpu())
                                                  # 此时参数是随机的，输出是乱码，属于正常现象


# ============ 7. 梯度裁剪：防 RNN 梯度爆炸 ============
def grad_clipping(net, theta):
    if isinstance(net, nn.Module):
        params = [p for p in net.parameters() if p.requires_grad]
    else:
        params = net.params                        # 我们的 scratch 模型走这条分支
    norm = torch.sqrt(sum(torch.sum((p.grad ** 2)) for p in params))
                                                  # 所有参数梯度拼成一个大向量，求 L2 范数
    if norm > theta:                               # 只有超阈值才动手
        for param in params:
            param.grad[:] *= theta / norm          # ★ 整体等比缩小，方向不变只改长度
                                                  # 原地乘，不用重新赋值，梯度仍然在


# ============ 8. 训练一个 epoch ============
def train_epoch_ch8(net, train_iter, loss, updater, device, use_random_iter):
    state, timer = None, d2l.Timer()               # state 在 batch 之间传递
    metric = d2l.Accumulator(2)                    # 累加器：metric[0] 累计 loss 总和，metric[1] 累计词元数
    for X, Y in train_iter:                        # X: (32,35)，Y: (32,35)
        if state is None or use_random_iter:
            state = net.begin_state(batch_size=X.shape[0], device=device)
                                                  # ★ 随机采样必须重置：batch 之间在原文上不连续
                                                  # ★ 顺序分区则只在第一个 batch 重置
        else:
            if isinstance(net, nn.Module) and not isinstance(state, tuple):
                state.detach_()
            else:
                for s in state:
                    s.detach_()                    # ★ 切断计算图：不把上一 batch 的 BPTT 带进来
                                                  #   只保留数值，不回传梯度，否则显存/图会爆炸

        y = Y.T.reshape(-1)                        # Y: (32,35) → 转置 (35,32) → 拉平 (1120,)
                                                  # ★ 必须转置：让它和 y_hat 的"时间优先"行序一致
        X, y = X.to(device), y.to(device)

        y_hat, state = net(X, state)               # y_hat: (1120, 28)，state 更新
        l = loss(y_hat, y.long()).mean()           # 交叉熵求平均 → 标量

        if isinstance(updater, torch.optim.Optimizer):
            updater.zero_grad()                    # 清空上一轮梯度
            l.backward()                           # 反向传播（BPTT）
            grad_clipping(net, 1)                  # ★ 裁剪必须在 step 之前
            updater.step()                         # 更新参数
        else:
            l.backward()
            grad_clipping(net, 1)
            updater(batch_size=1)                  # 手写 SGD：自己按 lr 和 batch_size 更新

        metric.add(l * y.numel(), y.numel())       # 累加"损失×词数"和"词数"，为了后面加权平均
    return math.exp(metric[0] / metric[1]), metric[1] / timer.stop()
                                                  # ★ 困惑度 = exp(平均交叉熵)：直观含义是"候选词数"


# ============ 9. 完整训练循环 ============
def train_ch8(net, train_iter, vocab, lr, num_epochs, device, use_random_iter=False):
    loss = nn.CrossEntropyLoss()                   # 8.4 里讲过：内部自带 log_softmax，要传原始分数
    animator = d2l.Animator(xlabel='epoch', ylabel='perplexity',
                            legend=['train'], xlim=[10, num_epochs])
    if isinstance(net, nn.Module):
        updater = torch.optim.SGD(net.parameters(), lr)
    else:
        updater = lambda batch_size: d2l.sgd(net.params, lr, batch_size)
                                                  # scratch 模型：调 d2l 手写的 SGD
    predict = lambda prefix: predict_ch8(prefix, 50, net, vocab, device)
                                                  # 每 10 轮打印一次续写效果
    for epoch in range(num_epochs):
        ppl, speed = train_epoch_ch8(net, train_iter, loss, updater, device, use_random_iter)
        if (epoch + 1) % 10 == 0:
            print(predict('time traveller'))       # 观察生成质量随训练提升
            animator.add(epoch + 1, [ppl])
    print(f'困惑度 {ppl:.1f}, {speed:.1f} 词元/秒 {str(device)}')
    print(predict('time traveller'))
    print(predict('traveller'))


# ============ 10. 开跑 ============
num_epochs, lr = 500, 1
train_ch8(net, train_iter, vocab, lr, num_epochs, d2l.try_gpu())