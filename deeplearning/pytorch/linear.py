#使用pytorch的api进行线性回归训练
import numpy as np
import torch
from torch.utils import data
from torch import nn

def data_generate(true_w, true_b, num_examples, num_inputs):
    features = torch.normal(mean = 0, std = 1,size = (num_examples,num_inputs))
    labels : torch.Tensor = true_w[0] * features[ : , 0] + true_w[1] * features[ : , 1] + true_b
    labels += torch.normal(mean = 0, std = 1, size = labels.shape)
    return features, labels.reshape(-1, 1)

num_inputs = 2
num_examples = 1000
true_w = torch.tensor([2.0, -3.4])
true_b = 4.2
batch_size = 10
num_epochs = 3

features, labels = data_generate(true_w, true_b, num_examples, num_inputs)

def load_array(data_array, batch_size, is_trained = True):
    dataset = data.TensorDataset(*data_array)
    return data.DataLoader(dataset = dataset, batch_size = batch_size, shuffle = is_trained)

data_iter = load_array((features, labels), batch_size)

net = nn.Sequential(nn.Linear(num_inputs, 1)) # 神经网络，这里是线性回归
net[0].weight.data.normal_(0, 0.01)
net[0].bias.data.fill_(0)

loss = nn.MSELoss() # 损失函数

trainer = torch.optim.SGD(params = net.parameters(), lr = 0.03) # 优化算法

for epoch in range(num_epochs):
    for X, y in data_iter:
        l = loss(net(X) ,y)
        trainer.zero_grad()
        l.backward()
        trainer.step()
    l = loss(net(features), labels)
    print(f'epoch {epoch + 1}, loss {l:f}')

w = net[0].weight.data
print('w的估计误差：', true_w - w.reshape(true_w.shape))
b = net[0].bias.data
print('b的估计误差：', true_b - b)


