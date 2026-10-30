import torch
import torch.nn as nn
from d2l import torch as d2l

class LeNet(nn.Module):
    def __init__(self, num_classes = 10):
        super().__init__()
        
        self.feature = nn.Sequential(
            nn.Conv2d(1, 6, kernel_size=5, padding=2), nn.ReLU(),
            nn.AvgPool2d(kernel_size=2, stride=2),
            nn.Conv2d(6, 16, kernel_size=5), nn.ReLU(),
            nn.AvgPool2d(kernel_size=2, stride=2)
        )

        self.classifier = nn.Sequential(
            nn.Flatten(),
            nn.Linear(16 * 5 * 5, 120), nn.ReLU(),
            nn.Linear(120, 84), nn.ReLU(),
            nn.Linear(84, 10)
        )

    def forward(self, X):
        return self.classifier(self.feature(X))



batch_size = 256
train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size=batch_size)
net = LeNet()
lr = 0.9
num_epochs = 10

# def train_epoch(train_iter, batch_size, net):

print(sum(p.numel() for p in net.parameters()))   # 应为 61706

d2l.train_ch6(net = net, train_iter = train_iter, test_iter = test_iter, num_epochs = num_epochs, lr = lr, device = d2l.try_gpu())