# 线性回归 完整实现

import torch 
import numpy as np
import random

num_inputs = 2
num_examples = 1000
true_w = torch.tensor([2.0, -3.4])
true_b = 4.2
batch_size = 10


def data_generate(true_w, true_b, num_examples, num_inputs):
    features = torch.normal(mean = 0, std = 1,size = (num_examples,num_inputs))
    labels : torch.Tensor = true_w[0] * features[ : , 0] + true_w[1] * features[ : , 1] + true_b
    labels += torch.normal(mean = 0, std = 1, size = labels.shape)
    return features, labels.reshape(-1, 1)

def data_iter(batch_size, features, labels):
    num_examples = len(features)
    indices = list(range(num_examples))
    random.shuffle(indices)
    for i in range(0, num_examples, batch_size):
        batch_indices = torch.tensor(indices[i : min(num_examples, i + batch_size)])
        yield features[batch_indices], labels[batch_indices]
        
def linreg(X : torch.Tensor, w : torch.Tensor, b):
    return X @ w + b

def squared_loss(y_hat : torch.Tensor, y : torch.Tensor):
    return 0.5 * ((y_hat - y.reshape(y_hat.shape)) ** 2)

def sgd(params : torch.Tensor, lr, batch_size):
    with torch.no_grad():
        for param in params:
            param -= lr / batch_size * param.grad
            param.grad.zero_()


features, labels = data_generate(true_w, true_b, num_examples, num_inputs)

# for X, y in data_init(features, labels, batch_size):
#     print(X ,'\n', y)
#     break

w = torch.normal(mean = 0, std = 0.01, size = (num_inputs, 1), requires_grad = True)
b = torch.zeros(size = (1 , ), requires_grad = True)


lr = 0.01
num_epochs = 30
net = linreg
loss = squared_loss

for epoch in range(num_epochs):
    for X, y in data_iter(batch_size, features, labels):
        l = loss(net(X, w, b), y)  # X和y的小批量损失
        # 因为l形状是(batch_size,1)，而不是一个标量。l中的所有元素被加到一起，
        # 并以此计算关于[w,b]的梯度
        l.sum().backward()
        sgd([w, b], lr, batch_size)  # 使用参数的梯度更新参数
        print(w, '\n', b, '\n')
    with torch.no_grad():
        train_l = loss(net(features, w, b), labels)
        print(f'epoch {epoch + 1}, loss {float(train_l.mean()):f}')


print(f'w的估计误差: {true_w - w.reshape(true_w.shape)}')
print(f'b的估计误差: {true_b - b}')
print(w, '\n', b)