import typing


def add_ingot(purse: typing.Dict[str, int]) -> typing.Dict[str, int]:
    """ @brief Add new "gold_ingot" to purse.

        @param purse    purse (dict) to use

        @return New purse with increased "gold_ingots" amount.
    """
    key_name = "gold_ingots"

    purse = purse.copy()
    if purse.get(key_name) is None:
        purse[key_name] = 1
    else:
        purse[key_name] += 1

    return purse


def get_ingot(purse: typing.Dict[str, int]) -> typing.Dict[str, int]:
    """ @brief Get "gold_ingot" from the purse.

        @param purse    purse (dict) to use

        @return New purse with decreased "gold_ingots" amount.
    """
    key_name = "gold_ingots"

    purse = purse.copy()
    if (purse.get(key_name) is not None) and (purse[key_name] > 0):
        purse[key_name] -= 1

    return purse


def empty(purse: typing.Dict[str, int]) -> typing.Dict[str, int]:
    """ @brief Returns an empty purse.

        @param purse    purse (dict) to use

        @return New empty purse.
    """
    purse = purse.copy()
    purse.clear()
    return purse


def main():
    purse = {"gold_ingots" : 5}

    purse_new = empty(purse)
    print("empty:", purse.get("gold_ingots"))
    print("empty:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new

    purse_new = get_ingot(purse)
    print("Get ingot:")
    print("prev:", purse.get("gold_ingots"))
    print("new:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new

    purse_new = add_ingot(purse)
    print("Add ingot:")
    print("prev:", purse.get("gold_ingots"))
    print("new:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new

    purse_new = get_ingot(purse)
    print("Get ingot:")
    print("prev:", purse.get("gold_ingots"))
    print("new:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new

    purse_new = add_ingot(purse)
    print("Add ingot:")
    print("prev:", purse.get("gold_ingots"))
    print("new:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new

    purse_new = add_ingot(purse)
    print("Add ingot:")
    print("prev:", purse.get("gold_ingots"))
    print("new:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new

    purse_new = get_ingot(purse)
    print("Get ingot:")
    print("prev:", purse.get("gold_ingots"))
    print("new:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new

    purse_new = get_ingot(purse)
    print("Get ingot:")
    print("prev:", purse.get("gold_ingots"))
    print("new:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new

    purse_new = get_ingot(purse)
    print("Get ingot:")
    print("prev:", purse.get("gold_ingots"))
    print("new:", purse_new.get("gold_ingots"), '\n')
    purse = purse_new


if __name__ == "__main__":
    main()
