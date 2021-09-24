#!/usr/bin/env python3

import numpy as np
from matplotlib import pyplot as plt
import re

def main():
    with open('3.data.out', 'r') as f:
        X, evs, evecs = [], [], []
        arrs = [X, evs, evecs]
        I = 0
        for line in f.readlines():
            if len(line) < 3:
                I += 1
                continue
            line = re.sub(' +', ' ', line.strip())
            line = [float(x) for x in line.split()]
            arrs[I].append(line)
        X = np.array(X)
        evs = np.array(evs)
        evecs = np.array(evecs)
    with open('3.data.in', 'r') as f:
        f.readline()
        lines  = f.readlines()
        lines = [[float(x) for x in line.strip().split()] for line in lines]
        lines = np.array(lines)

    plt.subplot(1,2,1)
    plt.scatter(lines[:,0], lines[:,1])
    plt.arrow(lines.mean(axis=0)[0], lines.mean(axis=0)[1],
            evecs[0,0]*evs[0,0], evecs[1,0]*evs[0,0], width=0.1, color='red')
    plt.arrow(lines.mean(axis=0)[0], lines.mean(axis=0)[1],
            evecs[0,1]*evs[1,0], evecs[1,1]*evs[1,0], width=0.1,
            color='green')
    plt.title('Original data')
    plt.subplot(1,2,2)
    plt.scatter(X[:,0], X[:,1])
    plt.title('After PCA')
    plt.show()

if __name__ == '__main__':
    main()
