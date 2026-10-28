import torch
from d2l import torch as d2l
import torch.nn as nn

def relu(X):
    a = torch.zeros_like(X)
    return torch.max(X, a)

def net(X): # 直接算了两层网络
    X = X.reshape((-1, num_inputs))
    H = relu(X@W1 + b1)
    return (H@W2 + b2)

def train_epoch_ch3(net, train_iter, loss, updater):
    if isinstance(net, nn.Module):
        net.train()
    for X, y in train_iter:
        y_hat = net(X)
        l : torch.Tensor = loss(y_hat, y)
        if isinstance(updater, torch.optim.Optimizer):
            updater.zero_grad()
            l.mean().backward()
            updater.step()
        else:
            l.sum().backward()
            updater(X.shape[0])

def train_ch3(net, train_iter, loss, updater, num_epochs):
    for epoch in range(num_epochs):
        train_epoch_ch3(net, train_iter, loss, updater)


def main():
    global num_inputs, W1, b1, W2, b2

    num_inputs, num_outputs, num_hiddens = 784, 10, 256
    num_epochs, lr = 10, 0.01
    batch_size = 256

    train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size)

    W1 = nn.Parameter(torch.randn(num_inputs, num_hiddens) * 0.01)
    b1 = nn.Parameter(torch.zeros(num_hiddens))
    W2 = nn.Parameter(torch.randn(num_hiddens, num_outputs) * 0.01)
    b2 = nn.Parameter(torch.zeros(num_outputs))

    params = [W1, b1, W2, b2]
    loss = nn.CrossEntropyLoss(reduction='none')
    updater = torch.optim.SGD(params=params, lr=lr)

    train_ch3(net=net, train_iter=train_iter, loss=loss, updater=updater, num_epochs=num_epochs)


if __name__ == '__main__':
    main()  # 仅在主进程中执行训练入口

# 补一下test and train accuracy