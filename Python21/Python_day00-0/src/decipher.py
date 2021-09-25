import sys
var = list(sys.argv[1])

i = 0
flag = 0
c = ""
for var[i] in sys.argv[1]:
	k = ord(var[i])
	if k >= 65 and k <= 90 and flag == 0:
		flag = 1
		c = c + var[i]
	elif k >= 97 and k <= 122 and flag == 0:
		c = c + var[i]
		flag = 1
	if k == 32:
		flag = 0
	i=i+1
print(c)
