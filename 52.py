from math import ceil, floor
N1 = 3
N2 = 3
N3 = 3
N4 = 3

original = []
for i in range(0, N4):
  for j in range(0, N3):
    for k in range(0, N2):
      for h in range(0, N1):
        original.append((i, j, k, h))

merged = []
for l in range(1, N4*N2+1):
  for j in range(0, N3):
    for h in range(0, N1):
      i = ceil(l/N2) - N4 * floor((l-1)/(N2*N4)) - 1
      k = l - N2 * floor((l-1)/N2) - 1
      merged.append((i, j, k, h))

print(set.difference(set(original), set(merged)))
