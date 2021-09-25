import typing

T = typing.Dict[str, int]

def decorator(func):
	def decor(a):
		print("SQUEAK")
		return func(a)
	return decor

@decorator
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

@decorator
def get_ingot(pur: T) -> T:
	for key in pur.keys():
		a = key
	for value in pur.values():
		value -= 1
		cop = {key : value}
		return(cop)
	return(pur)

@decorator
def empty(pur: T) -> T:
	pur.clear()
	return(pur)

def main():
	purse = {"gold_ingots": 3}

	print(add_ingot(get_ingot(add_ingot(empty(purse)))))
	print(add_ingot(add_ingot(empty(purse))))

if __name__ == "__main__":
    main()