import typing

T = typing.Dict[str, int]

def add_ingot(pur: T) -> T:
	if pur == {}:
		pur = {"gold_ingots": 0}
	for key in pur.keys():
		a = key
	for value in pur.values():
		value += 1
		cop = {key : value}
		return(cop)
	return(pur)

def split_booty(*data):
	i = 0
	flag = 0
	ar1 = ar2 = ar3 = 0
	for dic in data:
		for k, v in dic.items():
			if k == "gold_ingots" and v >= 0:
				i += v
	while i > 0:
		if flag == 0:
			if ar1 == 0: ar1 = {}
			ar1 = add_ingot(ar1)
			flag = 1
			i -= 1
			continue
		if flag == 1:
			if ar2 == 0: ar2 = {}
			ar2 = add_ingot(ar2)
			flag = 2
			i -= 1
			continue
		if flag == 2:
			if ar3 == 0: ar3 = {}
			ar3 = add_ingot(ar3)
			flag = 0
			i -= 1
			continue
	sp = (ar1, ar2, ar3)
	return(sp)
		
def main():
	print(split_booty({"gold_ingots": 7}, {"gold_ingots": -4}, {"gold_ingot": 5}, {"gold_ingots": 5}))

if __name__ == "__main__":
    main()