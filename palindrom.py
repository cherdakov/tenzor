def check(n):
    if(n<0):
        return False
    l=[]
    while(n>0):
        l.append(n%10)
        n//=10
    return l==l[::-1]
    
n = int(input())

assert(True == check(0))
assert(True == check(1))
assert(True == check(121))
assert(True == check(11))
assert(False == check(-1))
assert(False == check(12))
assert(False == check(123))
assert(False == check(123443210))

print(check(n))