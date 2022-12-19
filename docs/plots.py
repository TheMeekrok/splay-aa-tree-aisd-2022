import matplotlib.pyplot as plt
import math

aa_input = open('aa_log.out', 'r', encoding="utf-8")
splay_input = open('splay_log.out', 'r', encoding="utf-8")

for i in range(4):
    x_list = []
    y_list = []
    log2_list = []
    aa_list = []
    splay_list = []

    for j in range(6):
        if j == 0: 
            title = aa_input.readline()
            splay_input.readline()

            plt.title(title)
            
        else:
            N, time_aa = aa_input.readline().split()
            time_splay = splay_input.readline().split()[1]

            aa_list.append(float(time_aa))
            splay_list.append(float(time_splay))

            y_list.append(int(N))
            log2_list.append(math.log2(int(N)))

    plt.ylabel('Количество операций (среднее)')
    plt.xlabel('Количество элементов')
    plt.xscale('log')

    plt.plot(y_list, log2_list, label='log₂(N)', color="black", marker="o")
    plt.plot(y_list, aa_list, label='AA Дерево', color="red")
    plt.plot(y_list, splay_list, label='Splay Дерево', color="blue")
    plt.legend()

    plt.grid(color='black', linestyle='-', linewidth=0.5)

    plt.show()