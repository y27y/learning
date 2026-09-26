import numpy as np
import mxnet as mx
import random 
import time

# def use_svg_display():
#     display.set_matplotlib_formats('svg')

# def set_figsize(figsize = (3.5, 2.5)):
#     use_svg_display()
#     plt.rcParams['figure.figsize'] = figsize

mx.random.seed(int(time.time()))
num_inputs = 2
num_examples = 1000
true_w = [2, -3.4]
true_b = 4.2
batch_size = 10

def data_iter(batch_size, features, labels):
    num_examples = len(features)
    indices = list(range(num_examples))
    random.shuffle(indices) # 生成并打乱数组作为数据集分组的序号
    for i in range(0, num_examples, batch_size):
        batch_indices = np.array(indices[i : min(i + batch_size, num_examples)])
        yield features[batch_indices], labels[batch_indices]    # 这里generate的是两个numpy数组


def synthetic_data(true_w, true_b, num_examples):
    features = np.nd.random.normal(scale = 1, shape = (num_examples, num_inputs))   # 用random正态分布，生成features矩阵
    labels = true_w[0] * features[:, 0] + true_w[1] * features[:, 1] + true_b   # 用生成的矩阵X * W，生成labels的矩阵
    labels += mx.nd.random.normal(scale = 0.01, shape = labels.shape)   # 给labels矩阵添加噪声，更像自然生成
    return features, labels.reshape((-1,1))  # 把label从1行转换成1列

features, labels = synthetic_data(true_w, true_b, num_examples)

for X, y in data_iter(batch_size, features, labels):
    print(X, '\n', y)
# 打印所有的featrues * 10 and labels * 10  

w = np.random.normal(0, 0.01, (2, 1))
b = np.zeros(1)
w.attach_grad()
b.attach_grad()

def linreg(X, w, b):
    return np.dot(X, w) + b

   