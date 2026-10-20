# finding the longest common subsequence among two strings

def power_set_wrapper(x, subsequences, i, current_string):
	# x holds the current included characters
	# i holds the current character on which decision has to be made
	# current_string is the string included uptil i-th character
	if i>=len(x):
		subsequences.append(current_string)
	else:
		# current character taken
		power_set_wrapper(x, subsequences, i+1, current_string+x[i])	# x[i] as we are adding the current character and making the decision for next character on next call
		# current character not taken
		power_set_wrapper(x, subsequences, i+1, current_string)


def power_set(x):
	'''
	x is a string input
	the function will return the power set of the string x
	'''
	subsequences=[]
	power_set_wrapper(x=x, subsequences=subsequences, i=0, current_string='')
	return subsequences


def subsequence_exist(x, y):
	'''
	x is the string
	y is the subsequence that needs to be checked whether exist or not in x
	'''
	i=0
	j=0
	while i<len(x) and j<len(y):
		if y[j]==x[i]:
			i+=1
			j+=1
		else:
			i+=1
		if i==len(x) and j!=len(y):
			return False
	return True


def lcs_length(x, y):
	'''
	x and y are two string inputs
	the function will return the longest common subsequence length
	'''
	# one approach is to generate all the possible solutions of x and simply map them to y
	subsequences_y=power_set(y)
	maximum=0
	for i in range(len(subsequences_y)):
		if subsequence_exist(x, subsequences_y[i]):
			maximum=max(maximum, len(subsequences_y[i]))
	return maximum


def wrapper_dp_lcs_length(x: str, y: str, matrix, i: int, j: int):
	'''
	this function is really bad, need improvement, and understanding of the code
	the code is written on hit and trial basis
	'''
	print(f'i: {i}, j: {j}')
	if i==0 or j==0:
		return matrix[i][j]
	elif matrix[i][j]!=-1:
		# no need to calculate the current index
		return matrix[i][j]
	else:
		if x[j-1]==y[i-1]:
			return 1+wrapper_dp_lcs_length(x, y, matrix, i-1, j-1)
		else:
			return max(wrapper_dp_lcs_length(x, y, matrix, i-1, j), wrapper_dp_lcs_length(x, y, matrix, i, j-1))


def dp_lcs_length(x, y):
	matrix=[[-1 for _ in range(len(x)+1)] for _ in range(len(y)+1)]
	for _ in range(len(x)+1):
		matrix[0][_]=0
	for _ in range(len(y)+1):
		matrix[_][0]=0
	print(matrix)
	return wrapper_dp_lcs_length(x, y, matrix, len(y), len(x))


def main():
	x=input()
	y=input()
	print(dp_lcs_length(x, y))


if __name__=='__main__':
	main()
