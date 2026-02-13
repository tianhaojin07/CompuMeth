import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return np.arctan(x) + 0.4 * x * np.sin(x / 2) + 0.601958

plt.style.use('seaborn-v0_8-whitegrid')
fig, ax = plt.subplots(figsize=(12, 7))

x = np.linspace(-80, 80, 2000)
y = f(x)

ax.plot(x, y, lw=2, label=r'$f(x) = \arctan(x) + 0.4x\sin(\frac{x}{2}) + 0.601958$')
ax.axhline(0, color='black', ls='--', lw=1)

ax.set_title('Graph of the Function $f(x)$', fontsize=16)
ax.set_xlabel('$x$', fontsize=14)
ax.set_ylabel('$f(x)$', fontsize=14)
ax.set_xlim([-80, 80])
ax.legend(fontsize=12)

plt.savefig('f_x_graph.png', dpi=300, bbox_inches='tight')
plt.show()