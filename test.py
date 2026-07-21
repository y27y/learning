import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms
from torch.utils.data import DataLoader
import matplotlib.pyplot as plt

#步骤1

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))  # 标准化到 [-1, 1]
])

trainset = torchvision.datasets.CIFAR10(root='./data', train=True, download=True, transform=transform)
testset = torchvision.datasets.CIFAR10(root='./data', train=False, download=True, transform=transform)

trainloader = DataLoader(trainset, batch_size=64, shuffle=True)
testloader = DataLoader(testset, batch_size=64, shuffle=False)

classes = ('plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

#步骤2
class CNNModel(nn.Module):
    def __init__(self):
        super(CNNModel, self).__init__()
        self.conv1 = nn.Conv2d(in_channels=3, out_channels=16, kernel_size=3, padding=1)   # 输出: [16, 32, 32]
        self.pool1 = nn.MaxPool2d(kernel_size=2, stride=2)                                # 输出: [16, 16, 16]
        self.conv2 = nn.Conv2d(in_channels=16, out_channels=32, kernel_size=3, padding=1)  # 输出: [32, 16, 16]
        self.pool2 = nn.MaxPool2d(kernel_size=2, stride=2)                                # 输出: [32, 8, 8]
        self.conv3 = nn.Conv2d(in_channels=32, out_channels=64, kernel_size=3, padding=1)  # 输出: [64, 8, 8]
        self.pool3 = nn.MaxPool2d(kernel_size=2, stride=2)                                # 输出: [64, 4, 4]
        self.fc1 = nn.Linear(64 * 4 * 4, 512)   # 输入维度 = 64*4*4 = 1024
        self.fc2 = nn.Linear(512, 10)           # CIFAR-10 有 10 类
        self.relu = nn.ReLU()
        self.dropout = nn.Dropout(0.5)

    def forward(self, x):
        x = self.relu(self.conv1(x))
        x = self.pool1(x) 
        x = self.relu(self.conv2(x))
        x = self.pool2(x)  
        x = self.relu(self.conv3(x))
        x = self.pool3(x)
        x = x.view(x.size(0), -1)  # 展平: [batch, 6444]
        x = self.relu(self.fc1(x))
        x = self.dropout(x)
        x = self.fc2(x)
        return x

#步骤3
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = CNNModel().to(device)

#步骤4
criterion = nn.CrossEntropyLoss()  # 用于多分类任务
optimizer = optim.Adam(model.parameters(), lr=0.001)

#步骤5
num_epochs = 5
train_losses = []
train_accuracies = []
for epoch in range(num_epochs):
    model.train()  # 设置为训练模式（启用 Dropout/BatchNorm）
    running_loss = 0.0
    correct = 0
    total = 0
    for i, (inputs, labels) in enumerate(trainloader):
        inputs, labels = inputs.to(device), labels.to(device)
        # >>> 前向传播 <<<
        outputs = model(inputs)
        # >>> 损失计算（使用步骤4定义的 criterion）<<<
        loss = criterion(outputs, labels)
        # >>> 反向传播与优化（训练核心）<<<
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        
        running_loss += loss.item()
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()
    epoch_loss = running_loss / len(trainloader)
    epoch_acc = 100 *correct / total
    train_losses.append(epoch_loss)
    train_accuracies.append(epoch_acc)
    print(f'Epoch [{epoch+1}/{num_epochs}], Loss: {epoch_loss:.4f}, Accuracy: {epoch_acc:.2f}%')

#步骤6
model.eval()  # 设置为评估模式（禁用 Dropout/BatchNorm）
test_correct = 0
test_total = 0
test_loss = 0.0


with torch.no_grad(): 
    for inputs, labels in testloader:
        inputs, labels = inputs.to(device), labels.to(device)
        outputs = model(inputs)
        test_loss += criterion(outputs, labels).item()
        _, predicted = torch.max(outputs, 1)
        test_total += labels.size(0)
        test_correct += (predicted == labels).sum().item()

test_accuracy = 100 * test_correct / test_total
avg_test_loss = test_loss / len(testloader)
print(f'Test Loss: {avg_test_loss:.4f}, Test Accuracy: {test_accuracy:.2f}%')