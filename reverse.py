def reverse(n):
    if(n<0):
        return int('-'+str(n).replace('-','')[::-1])
    else:
        return int(str(n)[::-1])

assert(1 == reverse(1))
assert(22 == reverse(22))
assert(321 == reverse(123))
assert(-123 == reverse(-321))
assert(1234 == reverse(4321))

n = int(input())
print(reverse(n))
