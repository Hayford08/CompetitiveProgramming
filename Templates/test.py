from itertools import permutations
from bisect import bisect_left

def good(arr):
  def lis(values):
    dp = []
    for x in values:
      if not dp or x > dp[-1]:
        dp.append(x)
      else:
        dp[bisect_left(dp, x)] = x
    return len(dp)
  
  res1 = lis(arr)
  res2 = lis(arr[::-1])
#   print(f"{arr=}, {res1=}, {res2=}")
  return res1 == res2, res1

n = 7
for i in range(1, n + 1):
  arr = list(range(1, i + 1))
  mx = 0
  valid = []
  for perm in permutations(arr):
    res, size = good(perm)
    if not res:
      continue
    if size > mx:
      mx = size
      valid = [perm]
    elif size == mx:
      valid.append(perm)
    
  print(f"{i=}, {mx=}")
  for v in valid:
    print(v)