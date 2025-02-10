from functools import cache
@cache
def solve(n):
  if n < 10:
    return 1 
  s = str(n)
  res = 0 
  for c in s:
    if c == '0':
      continue
    if solve(n - int(c)) == 0:
      res = 1
  return res

N = 5000
for i in range(1, N + 1):
  if solve(i) == 0:
    print(i)
