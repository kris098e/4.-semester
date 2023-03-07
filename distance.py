import math

q = (1.0,8.0,7.0, 'q')
a = (1.0,4.0,4.0, 'a')
b = (8.0,1.0,7.0, 'b')
c = (2.0,4.0,9.0, 'c')
d = (1.0,2.0,13.0, 'd')

sets = [a,b,c,d]

def euclidanDistance(histo1, histo2):
    return math.pow(((histo1[0]-histo2[0]**2)+(histo1[1]-histo2[1])**2 + (histo1[2]-histo2[2])**2),0.5)


for x in sets:
    print("distance from " +x[3]+ " to q is: " + str(euclidanDistance(x, q))) 