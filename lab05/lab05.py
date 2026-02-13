import matplotlib.pyplot as plt
import numpy as np

k = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
simpson_errors = np.array([
    3.845896e-01, 1.286315e-02, 6.946970e-04, 4.125974e-05,
    2.543499e-06, 1.584126e-07, 9.892077e-09, 6.181186e-10,
    3.863043e-11, 2.414069e-12, 1.511014e-13
])
trapezoidal_errors = np.array([
    3.435696e-01, 9.553977e-02, 2.440597e-02, 6.132436e-03,
    1.535017e-03, 3.838730e-04, 9.597567e-05, 2.399438e-05,
    5.998624e-06, 1.499658e-06, 3.749146e-07
])

plt.rcParams['font.sans-serif'] = ['Microsoft YaHei', 'SimHei', 'Arial']
plt.rcParams['axes.unicode_minus'] = False

plt.figure(figsize=(10, 6), dpi=100)

plt.semilogy(k, trapezoidal_errors, 'b-o', label='复化梯形公式 (Order 2)', linewidth=2, markersize=6)
plt.semilogy(k, simpson_errors, 'r-s', label='复化 Simpson 公式 (Order 4)', linewidth=2, markersize=6)

plt.title('数值积分误差对比：复化梯形 vs 复化 Simpson', fontsize=14)
plt.xlabel('k (分段数 $N=2^k$)', fontsize=12)
plt.ylabel('绝对误差 ($|I_{num} - I_{exact}|$)', fontsize=12)

plt.xticks(k)
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend(fontsize=12)

plt.tight_layout()
plt.savefig('plot.png')
plt.show()