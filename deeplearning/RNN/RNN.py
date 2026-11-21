import math
import torch
from torch import nn
from torch.nn import functional as F
from d2l import torch as d2l
import re
import random

d2l.DATA_HUB['time_machine'] = (d2l.DATA_URL + 'timemachine.txt',
                                '090b5e7e70c295757f55df93cb0a180b9691891a')


def read_time_machine():
    with open(d2l.download('time_machine'), 'r') as f:
        lines = f.readlines()
    return [re.sub('[^A-Za-z]+', ' ', line).strip().lower() for line in lines]

def load_corpus_time_machine(max_tokens=-1):  #@save
    """返回时光机器数据集的词元索引列表和词表"""
    lines = read_time_machine()
    tokens = d2l.tokenize(lines, 'char')
    vocab = d2l.Vocab(tokens)
    # 因为时光机器数据集中的每个文本行不一定是一个句子或一个段落，
    # 所以将所有文本行展平到一个列表中
    corpus = [vocab[token] for line in tokens for token in line]
    if max_tokens > 0:
        corpus = corpus[:max_tokens]
    return corpus, vocab

def seq_data_iter_random(corpus, batch_size, num_steps):
    corpus = corpus[random.randint(0, num_steps - 1) : ]
    num_subseqs = (len(corpus) - 1) // num_steps
    initial_indices = list(range(0, num_subseqs * num_steps, num_steps))
    random.shuffle(initial_indices)

    def data(pos):
        return corpus[pos : pos + num_steps]

    num_batches = num_subseqs // batch_size
    for i in range(0, num_batches * batch_size, batch_size):
        initial_indices_per_batch = initial_indices[i : i + batch_size]
        X = [data(j) for j in initial_indices_per_batch]
        Y = [data(j + 1) for j in initial_indices_per_batch]
        yield torch.tensor(X), torch.tensor(Y)


def seq_data_iter_sequential(corpus, batch_size, num_steps):
    offset = random.randint(0, num_steps)
    num_tokens = (len(corpus) - offset - 1) // batch_size * batch_size
    Xs = torch.tensor(corpus[offset: offset + num_tokens])
    Ys = torch.tensor(corpus[offset + 1: offset + 1 + num_tokens])
    Xs, Ys = Xs.reshape(batch_size, -1), Ys.reshape(batch_size, -1)

    num_batches = Xs.shape[1] // num_steps
    for i in range(0, num_steps * num_batches, num_steps):
        X = Xs[:, i: i + num_steps]
        Y = Ys[:, i: i + num_steps]
        yield X, Y

class SeqDataLoader:
    """加载序列数据的迭代器"""
    def __init__(self, batch_size, num_steps, use_random_iter, max_tokens):
        if use_random_iter:
            self.data_iter_fn = seq_data_iter_random
        else:
            self.data_iter_fn = seq_data_iter_sequential
        self.corpus, self.vocab = load_corpus_time_machine(max_tokens)
        self.batch_size, self.num_steps = batch_size, num_steps

    def __iter__(self):
        return self.data_iter_fn(self.corpus, self.batch_size, self.num_steps)


def load_data_time_machine(batch_size, num_steps,  #@save
                           use_random_iter=False, max_tokens=10000):
    """返回时光机器数据集的迭代器和词表"""
    data_iter = SeqDataLoader(
        batch_size, num_steps, use_random_iter, max_tokens)
    return data_iter, data_iter.vocab


#====================================================================================
#====================================================================================
#====================================================================================

num_hiddens = 512
device = d2l.try_gpu()
batch_size, num_steps = 32, 35
train_iter, vocab = load_data_time_machine(batch_size, num_steps)

# ============ 2. 初始化参数 ============
def get_params(vocab_size, num_hiddens, device):
    num_input = num_output = vocab_size

    def normal(shape):
        return torch.randn(size=shape, device=device) * 0.01

    W_xh = normal((num_input, num_hiddens))
    W_hh = normal((num_hiddens, num_hiddens))
    b_h = torch.zeros(num_hiddens, device = device)
    W_hq = normal((num_hiddens, num_output))
    b_q = torch.zeros(num_output, device = device)

    params = [W_xh, W_hh, b_h, W_hq, b_q]
    for param in params:
        param.requires_grad_(True)
    return params


# ============ 3. 初始化隐藏状态 ============
def init_rnn_state(batch_size, num_hiddens, device):
    return (torch.zeros((batch_size, num_hiddens), device = device), )


# ============ 4. 核心：一个时间步的 RNN 计算 ============
def rnn(inputs, state, params):
    W_xh, W_hh, b_h, W_hq, b_q = params
    H, = state
    outputs = []

    for X in inputs:
        H = torch.tanh(torch.mm(X, W_xh) + torch.mm(H, W_hh) + b_h)
        Y = torch.mm(H, W_hq) + b_q
        outputs.append(Y)

    return torch.cat(outputs, dim = 0), (H, )


# ============ 5. 把上面拼成一个"模型" ============
class RNN_model:
    def __init__(self, vocab_size, num_hiddens, device, get_params, init_state, forward_fn):
        self.vocab_size = vocab_size
        self.num_hiddens = num_hiddens
        self.params = get_params(vocab_size, num_hiddens, device)
        self.init_state = init_state
        self.forward_fn = forward_fn

    def __call__(self, X, state):
        X = F.one_hot(X.T, self.vocab_size).type(torch.float32)
        return self.forward_fn(X, state, self.params)

    def begin_state(self, batch_size, device):
        return self.init_state(batch_size, self.num_hiddens, device)

 
# ============ 6. 预测：给定前缀，续写 ============ 
def predict_ch8(prefix, num_preds, net, vocab, device):
    state = net.begin_state(batch_size = 1, device = device)
    outputs = [vocab[prefix[0]]]
    get_input = lambda : torch.tensor([outputs[-1]], device = device).reshape((1, 1))

    for y in prefix[1 : ]:
        _, state = net(get_input(), state) 
        outputs.append(vocab[y])

    for _ in range(num_preds):
        y, state = net(get_input(), state)
        outputs.append(int(y.argmax(dim = 1).reshape(1)))

    return ''.join([vocab.idx_to_token[i] for i in outputs])


net = RNN_model(len(vocab), num_hiddens, device, get_params, init_rnn_state, rnn)
print(predict_ch8('time traveller ', 10, net, vocab, device))

# ============ 7. 梯度裁剪：防 RNN 梯度爆炸 ============
def grad_clipping(net, theta):
    if isinstance(net, nn.Module):
        params = [p for p in net.parameters() if p.requires_grad]
    else:
        params = net.params
    norm = torch.sqrt(torch.sum(torch.sum((p.grad ** 2)) for p in params))
    if norm > theta:
        for param in params:
            param.grad[ : ] *= theta / norm

# ============ 8. 训练一个 epoch ============
def train_epoch_ch8(net, trainer_iter, loss, optimizer, device, use_random_iter):
    state, timer = None, d2l.Timer()
    metric = d2l.Accumulator(2)

    for X, Y in train_iter:
        if state is None or use_random_iter:
            state = net.begin_state(batch_size = X.shape[0], device = device)
        else:
            if isinstance(state, nn.Module) and not isinstance(state, tuple):
                state.detach()
            else:
                for s in state:
                    s.detach()

        y = Y.T.reshape(-1)
        X, y = X.to(device), y.to(device)

        y_hat, state = net(X, state)
        l =  loss(y_hat, y).mean()

        optimizer.zero_grad()
        l.backward()
        grad_clipping(net, 1)
        optimizer.step()

        metric.add(l * y.numel(), y.numel())
        return math.exp(metric[0] / metric[1]), metric[1] / timer.stop() # 返回了困惑度


# ============ 9. 完整训练循环 ============
def train_ch8(net, train_iter, vocab, lr, num_epochs, device, use_random_iter=False):
    loss = nn.CrossEntropyLoss()
    optmizer = torch.optim.SGD(net.parameters(), lr = lr)
    

# 10. ruuuunn！
