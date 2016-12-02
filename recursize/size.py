#!/usr/bin/env python3.6
def main ():
    a = [-1, 3, -5, 7, -9, 11]
    print(f"Recursive size of a: {get_recursize(a)}")
    b = []
    for i in range(10):
        b.append(a)
    print(f"Recursive size of b: {get_recursize(b)}")
    c = []
    for i in range(100):
        c.append(b)
    print(f"Recursive size of c: {get_recursize(c)}")
    d = []
    for i in range(5000):
        d.append(c)
    print(f"Recursive size of c: {get_recursize(d)}")


def get_recursize (lst):
    out = 0
    for i in lst:
        out += get_recursize(i) if isinstance(i, list) else 1

    return out

main()
