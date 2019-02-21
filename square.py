import math
n = int(input())
print(sum(n//x - x + 1 for x in range(1, 1 + int(math.sqrt(n)))))
