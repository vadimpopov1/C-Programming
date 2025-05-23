import numpy as np
import matplotlib.pyplot as plt
import time
from concurrent.futures import ThreadPoolExecutor
from functools import partial

def matrix_multiply_part(args, size, A, B):
    start_row, end_row = args
    C_part = np.zeros((size, size))
    for i in range(start_row, end_row):
        C_part[i] = A[i] @ B 
    return C_part

def parallel_matrix_multiply(size, num_threads):
    A = np.random.rand(size, size)
    B = np.random.rand(size, size)
    
    chunk_size = max(size // num_threads, 1)
    ranges = [(i * chunk_size, min((i + 1) * chunk_size, size)) 
              for i in range(num_threads)]
    
    start_time = time.time()
    
    with ThreadPoolExecutor(max_workers=num_threads) as executor:
        func = partial(matrix_multiply_part, size=size, A=A, B=B)
        list(executor.map(func, ranges))
    
    return (time.time() - start_time) * 1000

def main():
    matrix_sizes = np.linspace(100, 2500, 6, dtype=int)
    thread_counts = [1, 2, 4, 8, 12, 16, 20, 24, 28, 32, 36]
    
    _ = parallel_matrix_multiply(100, 1)
    
    print("Замеры производительности...")
    results = {}
    for threads in thread_counts:
        times = []
        for size in matrix_sizes:
            run_times = []
            for _ in range(3):
                run_times.append(parallel_matrix_multiply(size, threads))
            time_ms = np.median(run_times)
            times.append(time_ms)
            print(f"Потоков: {threads:2d}, Размер: {size:4d}x{size:<4d}, Время: {time_ms:8.1f} ms")
        results[threads] = times

    # Построение графика
    plt.figure(figsize=(12, 8))
    colors = plt.cm.plasma(np.linspace(0, 1, len(thread_counts)))
    
    for i, (threads, times) in enumerate(results.items()):
        plt.plot(matrix_sizes, times, 'o-', linewidth=2, markersize=8, 
                 label=f'{threads} потоков', color=colors[i])
    
    plt.xlabel('Размер матрицы', fontsize=12)
    plt.ylabel('Время выполнения (мс)', fontsize=12)
    plt.title('Оптимизированная производительность умножения матриц\n', fontsize=14)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(title='Количество потоков', fontsize=10, bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.tight_layout()
    
    plt.savefig('optimized_matrix_performance.png', dpi=150, bbox_inches='tight')
    plt.show()

if __name__ == '__main__':
    main()