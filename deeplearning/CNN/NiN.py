#NiN 
import torch
import torch.nn as nn
from d2l import torch as d2l


def NiN_Block(in_channels, out_channels, kernel_size, strides, padding):
    return nn.Sequential(
        nn.Conv2d(in_channels, out_channels, kernel_size = kernel_size, stride = strides, padding = padding),
        nn.ReLU(),
        nn.Conv2d(out_channels, out_channels, kernel_size = 1), nn.ReLU(),
        nn.Conv2d(out_channels, out_channels, kernel_size = 1), nn.ReLU())


class NiN_Net(nn.Module):
    def __init__(self):
        super().__init__()

        self.net = nn.Sequential( # 这里的很多数字来自于AlexNet
            NiN_Block(1, 96, kernel_size=11, strides=4, padding=0),
            nn.MaxPool2d(3, stride=2),
            NiN_Block(96, 256, kernel_size=5, strides=1, padding=2),
            nn.MaxPool2d(3, stride=2),
            NiN_Block(256, 384, kernel_size=3, strides=1, padding=1),
            nn.MaxPool2d(3, stride=2),
            nn.Dropout(0.5),
            # 标签类别数是10
            NiN_Block(384, 10, kernel_size=3, strides=1, padding=1),
            nn.AdaptiveAvgPool2d((1, 1)),
            # 将四维的输出转成二维的输出，其形状为(批量大小,10)
            nn.Flatten())

    def forward(self, X):
        return self.net(X)

net = NiN_Net
