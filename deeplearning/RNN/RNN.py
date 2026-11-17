import math
import torch
from torch import nn
from torch.nn import functional as F
from d2l import torch as d2l

batch_size, num_steps = 32, 35
train_iter, vocab = d2l.load_data_time_machine(batch_size, num_steps)

# ============ 2. 初始化参数 ============
def get_param(vocab_size, num_hiddens, device):
    num_input = num_output = vocab_size

    def normal(shape):
        return torch.randn(size=shape, device=device) * 0.01

    W_xh = normal((num_input, num_hiddens))
    W_hh = normal((num_hiddens, num_hiddens))
    W_hq = normal((num_hiddens, num_output))
    b_h = torch.zeros(size = num_hiddens, device = device)
    b_q = torch.zeros(size = num_output, device = device)

    params = [W_xh, W_hh, b_h, W_hq, b_q]
    for param in params:
        param.requires_grad_(True)
    return params


# ============ 3. 初始化隐藏状态 ============
def init_rnn_state(batch_size, num_hiddens, device):
    W_hh = torch




# ============ 4. 核心：一个时间步的 RNN 计算 ============

# ============ 5. 把上面拼成一个"模型" ============

# ============ 6. 预测：给定前缀，续写 ============ 

# ============ 7. 梯度裁剪：防 RNN 梯度爆炸 ============

# ============ 8. 训练一个 epoch ============

# ============ 9. 完整训练循环 ============


# 10. ruuuunn！