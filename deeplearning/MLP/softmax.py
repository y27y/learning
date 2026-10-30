from d2l import torch as d2l
import torchvision
from torch.utils import data
from torchvision import transforms
import torch.nn as nn
import torch

batch_size = 256
num_input = 784
num_output = 10
num_epochs = 10
lr = 0.1
W = torch.normal(0, 0.01, size = (num_input, num_output), requires_grad = True)
b = torch.zeros(size = (num_input, ), requires_grad = True)

train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size)

net = nn.Sequential(nn.Flatten(), nn.Linear(784, 10))

loss = nn.CrossEntropyLoss(reduction='none')

trainer = torch.optim.SGD(params = net.parameters(), lr = 0.01)

d2l.train_batch_ch3(net, train_iter, test_iter, loss, num_epochs, trainer)
# 根本没有这种函数

   
