from pathlib import Path

import torch

file_path = Path(__file__).resolve().parents[2] / '1.pkl'
data = torch.load(file_path, map_location='cpu', weights_only=True)

if isinstance(data, torch.Tensor):
    print(data.detach().cpu().tolist())
else:
    print(data)
