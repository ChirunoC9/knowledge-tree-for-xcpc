def exgcd(a : int, b : int):
    if b == 0:
        return a, 1, 0
    else:
        g, x1, y1 = exgcd(b, a % b)
        return g, y1, x1 - a // b * y1