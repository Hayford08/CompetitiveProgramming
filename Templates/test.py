cnt = 0
st = set()
for a in range(100, 1001):
  for b in range(100, 1001):
    if a == b or a + b != 1000:
      continue
    sa = str(a)
    sb = str(b)
    if sorted(sa) == sorted(sb):
      st.add((a, b))

print(st)
print(len(st))