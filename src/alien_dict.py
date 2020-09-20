#!/usr/bin/env python3
"""
Reconstruct alien alphabet from given ordered list of words.
"""

from sys import stdin


def reconstruct_alphabet(words):
    """Business Logic"""

    result = []

    # Put your code here

    alphabet = dict()

    for word in words:
        for char in word:
            dict.

    # Return the result, do not change the structure

    return result


def main():
    """Entry Point"""

    words = []
    all_lines = stdin.readlines()

    for line in all_lines:
        if not line or not line.strip():
            continue

        words.append(line.strip())

    result = reconstruct_alphabet(words)
    print("".join([str(elem) for elem in result]))


if __name__ == "__main__":
    main()
