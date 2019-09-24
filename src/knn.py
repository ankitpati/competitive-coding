#!/usr/bin/env python3
'''K-Nearest Neighbors Problem'''

from math import sqrt
from collections import Counter


def main():
    '''Invoked if run as script.'''

    train_points = []
    train_cats = []
    with open('trainset.txt') as trainset_file:
        for line_read in trainset_file:
            splitted = line_read.split(',')
            train_points.append(tuple(map(int, splitted[:3])))
            train_cats.append(int(splitted[-1]))

    test_points = []
    K = []
    with open('testset.txt') as testset_file:
        for line_read in testset_file:
            splitted = line_read.split(',')
            test_points.append(tuple(map(int, splitted[:3])))
            K.append(int(splitted[-1]))

    result_categories = []
    for (t, k) in zip(test_points, K):
        distances = []

        for (p, train_cat) in zip(train_points, train_cats):
            d = sqrt(
                sum([(t_coord - p_coord)**2
                     for (t_coord, p_coord) in zip(t, p)]))
            distances.append((d, train_cat))

        distances.sort(key=lambda x: x[0])
        neighbors = distances[:k]

        category_counter = Counter(map(lambda x: x[1], neighbors))

        # First, sort ascending by category, then descending by count.
        sorted_counts = sorted(sorted(category_counter.items(),
                                      key=lambda x: x[0]),
                               key=lambda x: x[1],
                               reverse=True)
        result_categories.append(sorted_counts[0][0])

    with open('result.txt', 'w') as result_file:
        print(*result_categories, sep="\n", file=result_file)


if __name__ == '__main__':
    N = int(input())
    with open('trainset.txt', 'w') as tr:
        for _ in range(N):
            tr.write(f"{input()[1:-1]}\n")

    T = int(input())
    with open('testset.txt', 'w') as ts:
        for _ in range(T):
            ts.write(f"{input()[1:-1]}\n")

    main()

    with open('result.txt') as res:
        for line in res:
            print(line.strip())
