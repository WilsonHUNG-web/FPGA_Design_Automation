import matplotlib.pyplot as plt
import numpy as np
from math import sqrt
import sys


def fp_plot(blocks, floorplan, out, arrange, FL):
    fp = open(blocks, "r")
    block = {}
    line = fp.readline()
    line = line.split()
    num = int(line[2])
    line = fp.readline()
    line = fp.readline()
    line = fp.readline()
    while line != '\n':
        line = line.split()
        name = line[0]
        w = int(line[7][1:-1])
        h = int(line[8][:-1])
        block[name] = (w, h)
        line = fp.readline()
    fp.close()

    # # total block area
    # total_block_area = 0
    # for item in block:
    #     total_block_area += block[str(item)][0]*block[str(item)][1]

    fp = open(floorplan, "r")
    line = fp.readline()
    line = fp.readline()
    line = fp.readline()
    fig = plt.figure(figsize=(50, 50))
    ax = fig.add_subplot(111)
    while line != '':
        pos = line.split()

        rotate = int(pos[3])
        name = pos[0]
        x = int(pos[1])
        y = int(pos[2])
        w = block[name][0]
        h = block[name][1]
        if rotate == 1:
            w, h = h, w
        name = "["+pos[0]+"]"

        rect = plt.Rectangle((x, y), w, h, edgecolor='black',
                             facecolor='green', fill=True, linewidth=2)
        ax.add_patch(rect)

        #plt.text(x=x+int(w/2)-6, y=y+int(h/2)-2, s=name, fontsize=30, fontstyle='oblique')
        plt.text(x=x+int(w/5), y=y+int(h/2), s=name,
                 fontsize=20, fontstyle='oblique')  # 寫上sb
        line = fp.readline()
    fixedline = plt.Rectangle((0, 0), FL, FL, edgecolor='red',
                              facecolor='green', fill=False, linewidth=3, linestyle='dashed')

    ax.add_patch(fixedline)
    plt.yticks(np.arange(0, arrange, 100))
    plt.xticks(np.arange(0, arrange, 100))
    plt.savefig(out)
    plt.show()


def fpga_plot(casename):
    filename_arch = '../benchmarks/' + casename + '.arch'
    filename_fp = '../benchmarks/' + casename + '.floorplan'
    fa = open(filename_arch, 'r')
    line = fa.readline()
    line = line.split()
    w, h, s, d = int(line[0]), int(line[1]), int(line[2]), int(line[3])
    fig = plt.figure(figsize=(20, 20))
    ax = fig.add_subplot(111)

    for i in range(w+1):
        for j in range(h+1):
            clb = plt.Rectangle((i, j), 1, 1, edgecolor='white',
                                facecolor='grey', fill=True, linewidth=2)
            ax.add_patch(clb)
    for i in range(s, w+1, d):
        for j in range(0, h+1, 3):
            mux = plt.Rectangle((i, j), 1, 3, edgecolor='white',
                                facecolor='lightblue', fill=True, linewidth=2)
            ax.add_patch(mux)
    fixedline = plt.Rectangle((0, 0), w + 1, h + 1, edgecolor='red',
                              facecolor='green', fill=False, linewidth=2, linestyle='dashed')
    ax.add_patch(fixedline)
    plt.yticks(np.arange(0, h+15, 5))
    plt.xticks(np.arange(0, w+15, 5))
    plt.savefig(casename + '.png')
    plt.show()


if __name__ == '__main__':
    casename = sys.argv[1]
    ## filename_arch = '../benchmarks/' + casename + '.arch'
    ## filename_fp = '../benchmarks/' + casename + '.floorplan'
    print(casename)

    fpga_plot(casename)

    ##b1 = '../testcase/n100.hardblocks'
    ##fp1 = '../output/n100.floorplan'
    # out1 = '../n100.png'
    # arr1 = 550
    # FL1 = 444
    # fp_plot(blocks=b1, floorplan=fp1, out=out1, arrange=arr1, FL=FL1)
