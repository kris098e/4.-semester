props = [0.25, 0.35, 0.4]

h1 = [0.3, 0.25, 0.15]
h2 = [0.4, 0.55, 0.6]
h3 = [0.3, 0.2, 0.25]

sum1 = 0
sum2 = 0
sum3 = 0

for i in range(len(props)):
    sum1 += props[i] * h1[i]
    sum2 += props[i] * h2[i]
    sum3 += props[i] * h3[i]

print("class 1: ",sum1)
print("class 2: ",sum2)
print("class 3: ",sum3)
