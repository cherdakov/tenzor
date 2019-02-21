def get_openning(br):
    if br == '}':
        return '{'
    elif br == ']':
        return '['
    elif br == ')':
        return '('
    else:
        return ''

def check(seq):
    good = {'{','[','(',')',']','}'}
    stack = []
    for i in seq:
        if not i in good:
            return False
        if i=='}' or i==']' or i==')':
            if len(stack)==0 or stack[-1]!=get_openning(i):
                return False
            else:
                stack.pop()
        else:
            stack.append(i)
    return len(stack)==0

assert True == check("[{()}]")
assert False == check("[")
assert False == check("[[}}")
assert False == check("]")
assert False == check("][")
assert False == check("abc")
assert False == check("[[(]]")
assert True == check("[{(){()}}]")
assert True == check("()()(){}{}{}((())){{{}}}{{{}}}(()(()(())))")

s = input()
print(check(s))
