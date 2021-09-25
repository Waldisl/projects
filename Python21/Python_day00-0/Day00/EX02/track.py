
flag = 0
i = 0
while i < 3:
	a = input()
	if len(a) != 5:
		print("error map")
		exit()
	if a[0] == "*" and a[1] != "*" and a[2] != "*" and a[3] != "*" and a[4] == "*" and flag == 0 and i == 0: 
		flag = 1
	if a[0] == "*" and a[1] == "*" and a[2] != "*" and a[3] == "*" and a[4] == "*" and flag == 1 and i == 1: 
		flag = 2
	if a[0] == "*" and a[1] != "*" and a[2] == "*" and a[3] != "*" and a[4] == "*" and flag == 2 and i == 2:
		flag = 3
	if flag == 3:
		print("True")
	i = i + 1
if flag != 3:
	print("False")