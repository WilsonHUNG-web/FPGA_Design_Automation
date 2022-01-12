import matplotlib.pyplot as plt
import numpy as np
from math import sqrt
import sys


def fpga_plot(casename):
    filename_arch = '../benchmarks/' + casename + '.arch'
    filename_fp = '../outputs/' + casename + '.floorplan'
    fa = open(filename_arch, 'r')
    line = fa.readline()
    line = line.split()
    r, c, s, d = int(line[0]), int(line[1]), int(line[2]), int(line[3])
    fig = plt.figure(figsize=(20, 20))
    ax = fig.add_subplot(111)

    for i in range(s, c, d):
        for j in range(0, r, 3):
            mux = plt.Rectangle((i, j), 1, 3, edgecolor='white',
                                facecolor='lightblue', fill=True, linewidth=2)
            ax.add_patch(mux)

    fp = open(filename_fp, 'r')
    for line in fp.readlines():
        line = line.split()
        if len(line) == 1:
            break
        name, x, y, w, h = int(line[0]), int(line[1]), int(
            line[2]), int(line[3]), int(line[4])
        module = plt.Rectangle((x, y), w, h, edgecolor='grey',
                               facecolor='pink', fill=True, linewidth=2, alpha=0.8)
        ax.add_patch(module)
        ax.text(x, y+1, "M"+line[0], fontsize=10)
    fp.close()

    fixedline = plt.Rectangle((0, 0), c, r, edgecolor='red',
                              facecolor='green', fill=False, linewidth=2, linestyle='dashed')
    ax.add_patch(fixedline)
    ax.text(0, -5, "Fixed-outline(W, H): (" +
            str(c)+", "+str(r)+")", fontsize=20)

    plt.plot(range(r), alpha=0)
    plt.axis('off')
    plt.savefig('../outputs/'+casename + '.png')
    print(casename + '.png '+'is saved.')
    plt.show()


if __name__ == '__main__':
    casename = sys.argv[1]
    fpga_plot(casename)
