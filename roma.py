import re

coding = zip(
    [1000,900,500,400,100,90,50,40,10,9,5,4,1],
    ["M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"]
)

def decToRoman(num):
    if num < 1 or num > 3999 or int(num) != num:
        raise ValueError('Input should be an integer between 1 and 3999')
    result = []
    for d, r in coding:
        while num >= d:
            result.append(r)
            num -= d
    return ''.join(result)

def romanToDec(roman):
    if(len(roman)==0):
        raise ValueError('Empty Roman!') 
    values={'M': 1000, 'D': 500, 'C': 100, 'L': 50, 'X': 10, 'V': 5, 'I': 1}
    numbers = []
    for char in roman:
        if not(char in values):
            raise ValueError('No Roman digit!') 
        numbers.append(values[char])
    if len(numbers) == 1:
        return numbers[0]
    total = 0
    for num1, num2 in zip(numbers, numbers[1:]):
        if num1 >= num2:
            total += num1
        else:
            total -= num1
    return total + num2

s = input()
s = s.replace(" ","")
tokens = re.split("\\s*([+-/*])\\s*",s)
if len(tokens)!=3:
    raise ValueError('Bad Expr! pattern: ROMAN [+-/*] ROMAN')
left = romanToDec(tokens[0])
right = romanToDec(tokens[2])
operation = tokens[1]
if operation == '+':
    result = left + right  
elif operation == '-':
    result = left - right  
elif operation == '/':
    result = left // right  
elif operation == '*':
    result = left * right 
else:
    raise ValueError('Bad operation')
print(decToRoman(result))
