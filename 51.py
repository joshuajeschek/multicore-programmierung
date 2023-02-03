from math import ceil, floor
original = []

for i in range(1, 2+1):
  for j in range(1, 3+1):
    for k in range(1, 2+1):
      for h in range(1, 3+1):
        original.append((i, j, k, h))
merged = []
for l in range(1, 36+1):
  i = ceil(l/18) - 2 * floor((l-1)/36)
  j = ceil(l/6) - 3 * floor((l-1)/18)
  k = ceil(l/3) - 2 * floor((l-1)/6)
  h = l - 3 * floor((l-1)/3)
  merged.append((i, j, k, h))

for i in range(1, 36):
  print(f'{original[i]} === {merged[i]} = {original[i]==merged[i]}')
