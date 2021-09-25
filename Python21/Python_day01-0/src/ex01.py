import typing
import ex00


def split_booty(*purses: typing.Dict[str, int]) -> typing.Tuple[                        # ужос, но все же
                                                                typing.Dict[str, int],
                                                                typing.Dict[str, int], 
                                                                typing.Dict[str, int]
                                                            ]:
    """
        @brief  Splitting various number of purses with "gold_ingots" to 3 (!)
                new purses with splitted "gold_ingots".
                
        @param purses   any number of purses to split
        
        @return Tuple of 3 purses.
    """
    key_name = "gold_ingots"
    
    # count ingots
    ingots_amount: int = 0
    for purse in purses:
        if purse.get(key_name) is not None:
            ingots_amount += purse[key_name]
          
    # split to 3 purses
    out_purse_3 = {"gold_ingots" : ingots_amount // 3 }

    out_purse_2 = ex00.empty(out_purse_3)
    if ingots_amount % 3 >= 2:
        out_purse_2 = ex00.add_ingot(out_purse_3)
    else:
        out_purse_2 = out_purse_3.copy()

    out_purse_1 = ex00.empty(out_purse_3)
    if ingots_amount % 3 >= 1:
        out_purse_1 = ex00.add_ingot(out_purse_3)
    else:
        out_purse_1 = out_purse_3.copy()

    return (out_purse_1, out_purse_2, out_purse_3)


def main():
    
    print("Subject's test:")
    purse1 = {"gold_ingots" : 3}
    purse2 = {"gold_ingots" : 2}
    purse3 = {"apples!" : 10}
    print(split_booty(purse1, purse2, purse3), '\n')
    
    print("Zero purses test:")
    print(split_booty(), '\n')
    
    print("Two purses test:")
    purse1 = {"gold_ingots" : 100}
    purse2 = {"gold_ingots" : 15}
    print(split_booty(purse1, purse2), '\n')
    
    print("Five purses test:")
    purse1 = {"gold_ingots" : 10}
    purse2 = {"gold_ingots" : 20}
    purse3 = {"gold_ingots" : 30}
    purse4 = {"gold_ingots" : 40}
    purse5 = {"gold_ingots" : 50}
    print(split_booty(purse1, purse2, purse3, purse4, purse5), '\n')
        

if __name__ == "__main__":
    main()
