#!/usr/bin/env python3.6
def main ():
    a = [-1, 3, -5, 7, -9, 11]
    rsize = get_recursize(a)
    print(f"Recursive size of a: {rsize}")
    b = []
    for i in range(10):
        b.append(a)
    rsize = get_recursize(b)
    print(f"Recursive size of b: {rsize}")
    c = []
    for i in range(100):
        c.append(b)
    rsize = get_recursize(c)
    print(f"Recursive size of c: {rsize}")


def get_recursize (lst):
    out = 0
    for i in lst:
        out += get_recursize(i) if isinstance(i, list) else 1

    return out

main()
