from itertools import permutations

def good(arr):
  mp = {}
  for i, x in enumerate(arr):
    if x not in mp:
      mp[x] = i
    else:
      d = i - mp[x]
      if d != x:
        return False
  return True

for n in range(2, 8):
  arr = [1] +  [x for x in range(2, n + 1) for _ in range(2)]
  mx = tuple([1 for _ in range(2 * n - 1)])
  for perm in permutations(arr):
    if good(perm):
      mx = max(mx, perm)
  print(n, mx)
