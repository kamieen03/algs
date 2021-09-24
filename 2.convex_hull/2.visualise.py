#!/usr/bin/env python3

import numpy as np
from matplotlib import pyplot as plt
import re

if __name__ == '__main__':
    dataset, c_hull = [], []
    with open("2.datapoints.in", "r") as f:
        for line in f.readlines():
            line = re.sub(' +', ' ', line)
            line = line.strip().split(" ")
            x = float(line[0])
            y = float(line[1])
            dataset.append([x,y])
    with open("2.datapoints.out", "r") as f:
        for line in f.readlines():
            line = re.sub(' +', ' ', line)
            line = line.strip().split(" ")
            print(line)
            x = float(line[0])
            y = float(line[1])
            c_hull.append([x,y])
    dataset = np.array(dataset)
    c_hull = np.array(c_hull)
    plt.scatter(dataset[:,0], dataset[:,1])
    plt.scatter(c_hull[:,0], c_hull[:,1])
    plt.show()


