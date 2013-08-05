import random

f = open('/Users/sparxmacmini/Desktop/arrays.txt', "w")
f_star = open('/Users/sparxmacmini/Desktop/arraysIntake.txt', "w")

count = 0

def noDuplicate(x,y,z):
	res1 = x + y + z
	res2 = x + y - z
	res3 = x * y + z
	res4 = x * y - z
	res5 = x / y + z
	res6 = x / y - z
   	res7 = x - y + z
   	res8 = x + y * z
   	res9 = x - y * z
   	res10 = x + y / z
   	res11 = x - y / z
   	res12 = x * y * z
	if(res1 == res2 or res1 == res3 or res1 == res4 or res1 == res5 or res1 == res6 or res1 == res7 or res1 == res8 or res1 == res9 or res1 == res10 or res1 == res11 or res1 == res12):
		return 0
	elif(res2 == res3 or res2 == res4 or res2 == res5 or res2 == res6 or res2 == res7 or res2 == res8 or res2 == res9 or res2 == res10 or res2 == res11 or res2 == res12):
		return 0
	elif(res3 == res4 or res3 == res5 or res3 == res6 or res3 == res7 or res3 == res8 or res3 == res9 or res3 == res10 or res3 == res11 or res3 == res12):
		return 0
	elif(res4 == res5 or res4 == res6 or res4 == res7 or res4 == res8 or res4 == res9 or res4 == res10 or res4 == res11 or res4 == res12):
		return 0
	elif(res5 == res6 or res5 == res7 or res5 == res8 or res5 == res9 or res5 == res10 or res5 == res11 or res5 == res12):
		return 0
	elif(res6 == res7 or res6 == res8 or res6 == res9 or res6 == res10 or res6 == res11 or res6 == res12):
		return 0
	elif(res7 == res8 or res7 == res9 or res7 == res10 or res7 == res11 or res7 == res12):
		return 0
	elif(res8 == res9 or res8 == res10 or res8 == res11 or res8 == res12):
		return 0
	elif(res9 == res10 or res9 == res11 or res9 == res12 or res10 == res11 or res10 == res12 or res11 == res12):
		return 0
	else:
		num = random.random()
		if(num < 0.009):
			return 1
		else:
			return 0

text = ""
text2 = ""
for x in range(1,100):
	for y in range(1,100):
		temp1 = x + y
		temp2 = x - y
		for z in range(1,12):
			if(temp2 >= 0 and temp2 < 100):
				temp3 = temp2 + z
				if(temp3 >= 0 and temp3 < 100 and noDuplicate(x,y,z)):
					text += "{" + str(x) + ",1," + str(y) + ",3," + str(z) + "," + str(temp3) + "},"
					text2 += str(x) + " " + str(y) + " " + str(z) + " " + str(temp3) + " 1 3\n"
					count += 1
			if(temp1 < 100):
				temp5 = temp1 + z
				if(temp5 >= 0 and temp5 < 100 and noDuplicate(x,y,z)):
					text += "{" + str(x) + ",3," + str(y) + ",3," + str(z) + "," + str(temp5) + "},"
					text2 += str(x) + " " + str(y) + " " + str(z) + " " + str(temp5) + " 3 3\n"
					count += 1
				temp6 = temp1 - z
				if(temp6 >= 0 and temp6 < 100 and noDuplicate(x,y,z)):
					text += "{" + str(x) + ",3," + str(y) + ",1," + str(z) + "," + str(temp6) + "},"
					text2 += str(x) + " " + str(y) + " " + str(z) + " " + str(temp6) + " 3 1\n"
					count += 1
					
for x in range(1,100):
	for y in range(1,12):
		temp1 = x / float(y)
		for z in range(1,100):
			if((temp1 <= 12) and (int(temp1) == temp1)):
				temp2 = temp1 + z
				if(temp2 >= 0 and temp2 < 100 and noDuplicate(x,y,z)):
					text += "{" + str(x) + ",2," + str(y) + ",3," + str(z) + "," + str(int(temp2)) + "},"
					text2 += str(x) + " " + str(y) + " " + str(z) + " " + str(int(temp2)) + " 2 3\n"
					count += 1
				temp3 = temp1 - z
				if(temp3 >= 0 and temp3 < 100 and noDuplicate(x,y,z)):
					text += "{" + str(x) + ",2," + str(y) + ",1," + str(z) + "," + str(int(temp3)) + "},"
					text2 += str(x) + " " + str(y) + " " + str(z) + " " + str(int(temp3))+ " 2 1\n"
					count += 1
					
for x in range(1,12):
	for y in range(1,12):
		temp1 = x * y
		for z in range(1,100):
			if(temp1 < 100):
				temp2 = temp1 + z
				if(temp2 >= 0 and temp2 < 100 and noDuplicate(x,y,z)):
					text += "{" + str(x) + ",0," + str(y) + ",3," + str(z) + "," + str(temp2) + "},"
					text2 += str(x) + " " + str(y) + " " + str(z) + " " + str(temp2) + " 0 3\n"
					count += 1
				temp3 = temp1 - z
				if(temp3 >= 0 and temp3 < 100 and noDuplicate(x,y,z)):
					text += "{" + str(x) + ",0," + str(y) + ",1," + str(z) + "," + str(temp3) + "},"
					text2 += str(x) + " " + str(y) + " " + str(z) + " " + str(temp3) + " 0 1\n"
					count += 1

text += " Count = " + str(count)

f.write(text)
f.close()
f_star.write(text2)
f_star.close()