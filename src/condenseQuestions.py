f_write = open('/Users/sparxmacmini/Desktop/condensedArrays.txt', "w")

text = "{"
with open('/Users/sparxmacmini/Desktop/arraysIntake.txt', 'r') as f:
	for line in f:
		int_list = [int(i) for i in line.split()]
		temp = (int_list[5] << 30) + (int_list[4] << 28) + (int_list[3] << 21) + (int_list[2] << 14) + (int_list[1] << 7) + int_list[0] 
		text += str(temp) + ","

text += "}"

f_write.write(text)
f_write.close()