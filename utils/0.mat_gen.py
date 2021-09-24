#!/usr/bin/env python3

import numpy as np
np.set_printoptions(suppress = True)
import re
import sys

def gen_mat(rows, cols, clusters=1):
    rows = rows // clusters
    X = []
    for c in range(clusters):
        mean = np.random.uniform(-5, 5, cols)
        std = np.random.uniform(0.1, 5, cols)
        X.append(np.random.normal(mean, std, size=(rows,cols)))
    X = np.concatenate(X)
    return X

def format_mat(X):
    X = str(X)
    X = X.replace('[','').replace(']','')
    X = re.sub(' +', ' ', X)
    X = re.sub('\n ', '\n', X)
    if X[0] == ' ':
        X = X[1:]
    return X

if __name__ == '__main__':
    if len(sys.argv) not in [3, 4]:
        print('Usage: ./gen_mat.py rows cols [clusters]')
    else:
        args = [int(x) for x in sys.argv[1:]]
        X = format_mat(gen_mat(*args))
        print(args[0], args[1])
        print(X)

