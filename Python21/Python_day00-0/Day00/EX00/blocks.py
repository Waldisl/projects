import sys
var = sys.argv[1]

if len(sys.argv) > 2:
	print("ERROR: argv")
	exit(1)

var = int(var, 10)

i = 0
while var > i:
	i=i+1
	a = input()
	k = 0
	while a[k] == "0":
		k=k+1
		if (k == 4) & (a[5] != "0"):
			if len(a) == 32:
				print(a)
