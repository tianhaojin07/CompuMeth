import numpy as np

def f(x):
    x = np.float32(x)
    return np.sqrt(x**2 + 36) - 6

def g(x):
    x = np.float32(x)
    return x**2 / (np.sqrt(x**2 + 36) + 6)

print("x_val\t\tf(x)\t\t\tg(x)")
print("-" * 60)

for i in range(1, 12):
    x = 4**(-i)
    fx = f(x)
    gx = g(x)
    print(f"4**(-{i:<2})\t\t{fx:.12e}\t{gx:.12e}")
