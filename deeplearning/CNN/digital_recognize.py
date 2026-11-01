import torchvision
import torch
import torch.nn as nn
import torchvision.transforms as transform

transform = torchvision.transforms.Compose([
    transform.ToTensor(),
    transform.Normalize((0.1307, ), (0.3081, ))
])
train_set = torchvision.datasets.MNIST(root = './data', train = True, transform = transform, download = True)
test_set = torchvision.datasets.MNIST(root = './data', train = False, transform = transform, download = True)

class Net(nn.Module):
    def __init__(self):
        super().__init__()

        self.feature = nn.Sequential(
            
        )

        self.classifier = nn.Sequential(

        )

    def forward(self, X):
        return self.classifier(self.feature(X))
    
batch_size = 1
num_epochs = 10
lr = 0.01
train_iter = torch.utils.data.DataLoader(train_set, batch_size = batch_size, shuffle = True, drop_last = True)
test_iter = torch.utils.data.DataLoader(test_set, batch_size = batch_size, shuffle = False, drop_last = True)

print(next(iter(train_iter))[0])