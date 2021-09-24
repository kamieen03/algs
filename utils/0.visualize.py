#!/usr/bin/env python3

import numpy as np
from matplotlib import pyplot as plt
import sys

def main(filename):
    dataset = []
    with open(filename, "r") as f:
        rows, cols = [int(x) for x in f.readline().split()]
        if cols > 3:
            return
        for line in f.readlines():
            line = [float(x) for x in line.strip().split(" ")]
            dataset.append(line)
    dataset = np.array(dataset)
    plt.scatter(dataset[:,0], dataset[:,1])
    plt.show()


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: ./0.visualize.py file_path')
    else:
        main(sys.argv[1])

