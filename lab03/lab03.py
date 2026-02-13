import numpy as np
import time

def create_hilbert_system(n):
    """
    创建方程组 A = H + 2I 和向量 b。

    参数:
        n (int): 矩阵的阶数。

    返回:
        A (np.ndarray): 系数矩阵 A = H + 2I。
        b (np.ndarray): 右端向量 b。
        x_star (np.ndarray): 精确解 x*。
    """
    # 创建 n x n 的希尔伯特矩阵 H
    H = np.fromfunction(lambda i, j: 1.0 / (i + j + 1), (n, n), dtype=float)

    # 创建单位矩阵 I
    I = np.identity(n)

    # 定义系统矩阵 A
    A = H + 2 * I

    # 定义精确解 x* (所有分量为 1)
    x_star = np.ones(n)

    # 根据精确解计算右端向量 b
    b = A @ x_star

    return A, b, x_star

def jacobi_iteration(A, b, x_star, epsilon=1e-5, max_iter=500000):
    """
    使用雅可比迭代法求解线性方程组 Ax = b。
    """
    n = len(b)
    x = np.zeros(n)  # 初始猜测 x^(0) 为零向量

    D = np.diag(A)
    R = A - np.diag(D) # R = L + U

    for k in range(max_iter):
        x_new = (b - R @ x) / D

        # 计算 L1 范数误差
        error = np.linalg.norm(x_new - x_star, 1)

        if error < epsilon:
            return x_new, k + 1, error

        x = x_new

    # 在最大迭代次数内未收敛
    return None, max_iter, np.inf

def gauss_seidel_iteration(A, b, x_star, epsilon=1e-5, max_iter=500000):
    """
    使用高斯-赛德尔迭代法求解线性方程组 Ax = b。
    """
    n = len(b)
    x = np.zeros(n)  # 初始猜测 x^(0) 为零向量

    for k in range(max_iter):
        x_old = x.copy()
        for i in range(n):
            # 使用更新后的 x 分量进行计算
            sigma = np.dot(A[i, :i], x[:i]) + np.dot(A[i, i + 1:], x_old[i + 1:])
            x[i] = (b[i] - sigma) / A[i, i]

        # 计算 L1 范数误差
        error = np.linalg.norm(x - x_star, 1)

        if error < epsilon:
            return x, k + 1, error

    # 在最大迭代次数内未收敛
    return None, max_iter, np.inf

def run_experiment():
    """
    运行完整的实验并打印结果。
    """
    n_values = [10, 20, 80, 200, 500, 2000, 6000]
    # 根据要求，雅可比法只计算前几个会收敛的n值
    n_values_jacobi = [10, 20, 80, 200]

    results = []

    for n in n_values:
        print(f"正在处理 n={n}...")
        start_time = time.time()
        A, b, x_star = create_hilbert_system(n)

        # --- 雅可比法 ---
        if n in n_values_jacobi:
            x_j, k_j, err_j = jacobi_iteration(A, b, x_star)
            if x_j is not None:
                norm_j = np.linalg.norm(x_j, 1)
                results.append((n, "Jacobi", k_j, f"{err_j:.6f}", f"{norm_j:.6f}"))
            else:
                results.append((n, "Jacobi", "迭代失败", "-", "-"))
        else:
            # 对于更大的n，直接标记为失败，不进行计算
            results.append((n, "Jacobi", "迭代失败", "-", "-"))

        # --- 高斯-赛德尔法 ---
        x_gs, k_gs, err_gs = gauss_seidel_iteration(A, b, x_star)
        if x_gs is not None:
            norm_gs = np.linalg.norm(x_gs, 1)
            results.append((n, "Gauss-Seidel", k_gs, f"{err_gs:.6f}", f"{norm_gs:.6f}"))
        else:
            results.append((n, "Gauss-Seidel", "迭代失败", "-", "-"))

        end_time = time.time()
        print(f"n={n} 完成，耗时 {end_time - start_time:.2f} 秒。")

    # --- 打印格式化的结果表 ---
    print("\n" + "="*80)
    print(" " * 32 + "数值结果")
    print("="*80)
    header = f"{'n':<6} | {'迭代法':<15} | {'迭代步数':<12} | {'绝对误差 ||x(k) - x*||_1':<28} | {'||x(k)||_1'}"
    print(header)
    print("-" * 80)

    last_n = None
    for res in results:
        n_val, method, steps, error, norm = res
        if n_val != last_n:
            if last_n is not None:
                print("-" * 80)
            print(f"n={n_val:<4} | {method:<15} | {str(steps):<12} | {error:<28} | {norm}")
        else:
            print(f"{'':<6} | {method:<15} | {str(steps):<12} | {error:<28} | {norm}")
        last_n = n_val
    print("=" * 80)

if __name__ == '__main__':
    run_experiment()