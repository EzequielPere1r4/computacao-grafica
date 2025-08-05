def alg(x0, y0, x1, y1):
    pontos = []
    dx = x1 - x0
    dy = y1 - y0
    d = 2 * dy - dx
    y = y0

    for x in range(x0, x1 + 1):
        pontos.append((x, y))
        if d > 0:
            y += 1
            d = d + (2 * dy - 2 * dx)
        else:
            d = d + 2 * dy

    return pontos
        
result = alg(1, 1, 8, 5)
print("pontos: ")
for ponto in result:
    print(ponto)
            