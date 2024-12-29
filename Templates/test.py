from itertools import permutations

def good(s):
  cntA = 0
  for i in range(len(s) - 1):
    if s[i] == 'A':
      cntA += 1
    if cntA == 4:
      return False
  return True

a = "AAAABBB"
print(*set(p for p in permutations(a) if good(p)), sep='\n')