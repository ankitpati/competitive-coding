#!/usr/bin/env python3
''' pascals-next-line.py
Given any one line of a Pascal's triangle, print the next line.

Command-Line Invocation:
    $ python3 pascals-next-line.py 1 3 3 1

Programmatic Invocation:
    pascals-next-line(1, 3, 3, 1)

Output:
    1 4 6 4 1
'''


from sys import argv, stderr, exit


def pascals_next_line(*this_line):
    '''Invoke with comma-separated numbers to get back a list.'''

    next_line = []

    previous_number = 0
    for current_number in this_line:
        next_line.append(previous_number + current_number)
        previous_number = current_number

    next_line.append(1) # the final 1 on every line

    return next_line


if __name__ == '__main__':
    del argv[0] # remove the program name from argument list
    print(*pascals_next_line(*list(map(int, argv))))
