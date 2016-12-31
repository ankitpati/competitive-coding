#!/usr/bin/env python3

def merge_the_tools(string, k):
    divs = len(string) // k
    for i in range(divs):
        lookback = []
        for i in string[i*k : i*k + k]:
            if i not in lookback:
                print(i, end='')
                lookback.append(i)
        print()

if __name__ == '__main__':
    string, k = input(), int(input())
    merge_the_tools(string, k)
