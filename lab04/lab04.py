import numpy as np
import matplotlib.pyplot as plt
import os

plt.rcParams['font.sans-serif'] = ['SimSun']
plt.rcParams['axes.unicode_minus'] = False

output_dir = "interpolation_results"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

def f(x):
    return (7 * x + 3) / (x**2 - 2 * x + 7)

def lagrange_interpolation(x_nodes, y_nodes, x_eval):
    num_nodes = len(x_nodes)
    p_x = np.zeros_like(x_eval, dtype=np.float64)

    for k in range(num_nodes):
        l_k = np.ones_like(x_eval, dtype=np.float64)
        for j in range(num_nodes):
            if j != k:
                l_k *= (x_eval - x_nodes[j]) / (x_nodes[k] - x_nodes[j])
        p_x += y_nodes[k] * l_k
    return p_x


N_values = [4, 8, 16, 32]
x_min, x_max = -5.0, 5.0
results_data = []

dense_points = np.linspace(x_min, x_max, 501)
f_on_dense_points = f(dense_points)

for N in N_values:
    i = np.arange(N + 1)
    x_uniform = x_min + (x_max - x_min) * i / N
    y_uniform = f(x_uniform)
    x_chebyshev = -5 * np.cos((2 * i + 1) * np.pi / (2 * N + 2))
    x_chebyshev = np.sort(x_chebyshev)
    y_chebyshev = f(x_chebyshev)

    p_uniform_on_dense = lagrange_interpolation(x_uniform, y_uniform, dense_points)
    p_chebyshev_on_dense = lagrange_interpolation(x_chebyshev, y_chebyshev, dense_points)

    error_uniform = np.max(np.abs(f_on_dense_points - p_uniform_on_dense))
    error_chebyshev = np.max(np.abs(f_on_dense_points - p_chebyshev_on_dense))

    results_data.append({
        "N": N,
        "Uniform Error": error_uniform,
        "Chebyshev Error": error_chebyshev
    })

    plt.figure(figsize=(14, 8))
    plt.title(f'N = {N} 时的拉格朗日插值效果对比', fontsize=16)

    plt.plot(dense_points, f_on_dense_points, 'k-', label='原始函数 f(x)', linewidth=2)
    plt.plot(dense_points, p_uniform_on_dense, 'b--', label=f'均匀节点插值 p(x)')
    plt.plot(x_uniform, y_uniform, 'bo', markersize=8, label='均匀节点')
    plt.plot(dense_points, p_chebyshev_on_dense, 'r-.', label=f'Chebyshev节点插值 p(x)')
    plt.plot(x_chebyshev, y_chebyshev, 'rx', markersize=8, label='Chebyshev节点')

    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True)
    plt.legend(fontsize=12)

    image_filename = os.path.join(output_dir, f'N_{N}.png')
    plt.savefig(image_filename)
    plt.show()

table_string_builder = []
table_string_builder.append("\n" + "="*60)
table_string_builder.append("插值误差结果表".center(60))
table_string_builder.append("="*60)
table_string_builder.append(f"| {'N':^4} | {'均匀节点误差':^23} | {'Chebyshev节点误差':^23} |")
table_string_builder.append(f"|{'-'*6}|{'-'*25}|{'-'*25}|")
for res in results_data:
    table_string_builder.append(f"| {res['N']:<4} | {res['Uniform Error']:<23.12E} | {res['Chebyshev Error']:<23.12E} |")
table_string_builder.append("="*60)

final_table_string = "\n".join(table_string_builder)

print(final_table_string)

results_filename = os.path.join(output_dir, '插值误差结果.txt')
try:
    with open(results_filename, 'w', encoding='utf-8') as f:
        f.write(final_table_string)
    print(f"\n结果表格已成功保存至: {results_filename}")
except IOError as e:
    print(f"\n错误：无法将结果写入文件。{e}")