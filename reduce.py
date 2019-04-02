def my_reduce(fn, acc, collection):
    if len(collection)==0: return acc
    else: return my_reduce(fn, fn(acc, collection[0]), collection[1:])
    
b = [1,2,3,4]
start = 10
result = my_reduce((lambda x, y: x + y), start, b)
print(result)
