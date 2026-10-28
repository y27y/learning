from d2l import torch as d2l
import torch
import torch.nn as nn
import used

def init_weight(m): # ????
    if type(m) == nn.Linear:
        nn.init.normal_(m.weight, std = 0.01)

def main():
    num_input, num_hidden, num_output = 786, 256, 10
    batch_size, lr, num_epochs = 256, 0.1, 10

    net = nn.Sequential(nn.Flatten(),
                        nn.Linear(num_input, num_hidden),
                        nn.Flatten(),
                        nn.Linear(num_hidden,num_output))

    net.apply(init_weight)
    loss = nn.CrossEntropyLoss(reduction='none')
    trainer = torch.optim.SGD(net.parameters(), lr=lr)
    train_iter, test_iter = d2l.load_data_fashion_mnist(batch_size)
    # train
    used.train_ch3(net = net, train_iter = train_iter, test_iter = test_iter, loss = loss,  num_epochs = num_epochs, updater = trainer)

    torch.save(net.state_dict(), '1.pkl')

if __name__ == 'main':
    main()