import subprocess
import time
import random
import os
import psutil
import matplotlib.pyplot as plt
import requests
import subprocess
import psutil
import time

def generate_random_words(count):
    """
    Generate a list of random words using an external API.
    The API used here is random-word-api.herokuapp.com, which returns a list of random words.
    """
    api_url = f"https://random-word-api.herokuapp.com/word?number={count}"
    try:
        response = requests.get(api_url)
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        print(f"Error fetching random words: {e}")
        return []

def generate_input(N, M, K):
    """
    Generate test input with N texts and M queries, each containing K random words.
    """
    words = generate_random_words(K)
    if not words:
        return "Error: Could not fetch random words."

    texts = '\n'.join(' '.join(random.sample(words, min(K, len(words)))) for _ in range(N))
    queries = '\n'.join(' '.join(random.sample(words, min(K, len(words)))) for _ in range(M))
    return f"{N}\n{texts}\n{M}\n{queries}"

def run_cpp_code(input_data):
    # Запуск процесса
    process = subprocess.Popen(['../src/a.out'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    start_time = time.time()

    # Отправка входных данных и ожидание завершения процесса
    stdout, stderr = process.communicate(input=input_data.encode())

    end_time = time.time()

    return stdout.decode(), end_time - start_time

def memory_usage(pid):
    process = psutil.Process(pid)
    mem_info = process.memory_info()
    return mem_info.rss

n_values = []
time_taken_values = []
memory_used_values = []
for n in [4**k1 for k1 in range(7)]:
    print("OK")
    input_data = generate_input(1000, n, 1000)
    output, time_taken = run_cpp_code(input_data)
    n_values.append(n)
    time_taken_values.append(time_taken)

plt.figure(figsize=(12, 6))

plt.plot(n_values, time_taken_values, marker='o')
plt.title('Время использования при константном количестве текстов и слов в запросе')
plt.xlabel('N Value')
plt.ylabel('Time (s)')
plt.grid(True)
plt.tight_layout()
plt.show()

# n_values = []
# time_taken_values = []
# memory_used_values = []
# for n in [4**k1 for k1 in range(7)]:
#     print("OK")
#     input_data = generate_input(1000, 1000, n)
#     output, time_taken = run_cpp_code(input_data)
#     n_values.append(n)
#     time_taken_values.append(time_taken)

# plt.figure(figsize=(12, 6))

# plt.plot(n_values, time_taken_values, marker='o')
# plt.title('Время использования при константном количестве запросов и текстов')
# plt.xlabel('N Value')
# plt.ylabel('Time (s)')
# plt.grid(True)
# plt.tight_layout()
# plt.show()
