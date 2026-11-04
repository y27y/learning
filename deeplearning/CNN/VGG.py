#VGG-11 && VGG_Block
import torch
import torch.nn as nn
from d2l import torch as d2l

conv_arch = ((1, 64), (1, 128), (2, 256), (2, 512), (2, 512))

def VGG_Block(num_convs, in_channels, out_channels):
    layers = []
    for _ in range(num_convs):
        layers.append(nn.Conv2d(in_channels, out_channels, kernel_size = 3, padding = 1))
        layers.append(nn.ReLU())
        in_channels = out_channels

    layers.append(nn.MaxPool2d(kernel_size = 2, stride = 2))
    return nn.Sequential(*layers)

def VGG_Net(conv_arch):
    conv_blocks = []
    in_channels = 1

    for num_conv, out_channels in conv_arch:
        conv_blocks.append(VGG_Block(num_conv, in_channels, out_channels))
        in_channels = out_channels

    return nn.Sequential(*conv_blocks, nn.Flatten(),
                        nn.Linear(out_channels * 7 * 7, 4096), nn.ReLU(), nn.Dropout(0.5),
                        nn.Linear(4096, 4096), nn.ReLU(), nn.Dropout(0.5),
                        nn.Linear(4096, 10)
                        )

