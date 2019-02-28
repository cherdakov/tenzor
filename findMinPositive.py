def find_min_positive(l):
    s=set(l)
    i = 1
    while(i in s):
        i+=1
    return i
    
assert(1 == find_min_positive([-1,-2,2,3,4,5]))
assert(2 == find_min_positive([1]))
assert(3 == find_min_positive([1,2,4,5]))
assert(4 == find_min_positive([1,2,3]))
assert(5 == find_min_positive([4,3,2,1,0]))

l=list(map(int,input().split()))
print(find_min_positive(l))
