import numpy as np

# ========== 数据 ==========
X = np.array([1, 2, 3])
Y = np.array([3, 5, 7])   # 真实关系：y = 2x + 1

# ========== 超参数 ==========
w, b = 0.0, 0.0            # 初始参数
lr = 0.1                   # 学习率
epochs = 100                # 训练轮数

# ========== 训练（BGD：每次用全部样本） ==========
print(f"{'Epoch':>5} | {'w':>8} | {'b':>8} | {'Loss':>10}")
print("-" * 42)

for epoch in range(epochs):
    # 1. 预测 & 误差
    pred = w * X + b
    error = pred - Y                    # shape: (3,)

    # 2. 计算梯度（套公式）
    grad_w = np.mean(error * X)         # (1/|B|) Σ (误差 × x)
    grad_b = np.mean(error)             # (1/|B|) Σ 误差

    # 3. 更新参数
    w = w - lr * grad_w
    b = b - lr * grad_b

    # 4. 算当前损失（MSE）
    loss = np.mean(error ** 2) / 2

    print(f"{epoch+1:>5} | {w:>8.4f} | {b:>8.4f} | {loss:>10.4f}")

print(f"\n✅ 训练结束。最终：w={w:.4f}, b={b:.4f}")
print(f"🎯 真实值：  w=2.0000, b=1.0000")
# import mxnet as mx
# import numpy as np
# import torch

# left = mx.nd.array([[1, 2], [3, 4]])
# right = mx.nd.array([[5, 6], [7, 8]])

# print("left + right:")
# print(left + right)

# print("left * right (element-wise):")
# print(left * right)

# print("left @ right (matrix multiplication):")
# print(mx.nd.dot(left, right))

# print("left.T:")
# print(left.T)

# print("matrix shape:", left.shape)


