# the problem is 0/1 knapsack with no duplication
from lcs import power_set


def table_initialization():
	total_objects=int(input('number of objects: '))
	weights=[]
	prices=[]
	for _ in range(total_objects):
		print(f'\nitem: {_+1}')
		weights.append(int(input('weight: ')))
		prices.append(int(input('price: ')))
	return weights, prices


def print_table(weights, prices):
	print('\ntable:')
	print('item: ', end='\t\t')
	for _ in range(len(weights)):
		print(f'{_+1}', end='\t')
	print('\nweight: ', end='\t')
	for _ in range(len(weights)):
		print(f'{weights[_]}', end='\t')
	print('\nprice: ', end='\t\t')
	for _ in range(len(weights)):
		print(f'{prices[_]}', end='\t')
	print()


def main():
	weights, prices=table_initialization()
	possible_combinations=power_set(weights)
	print(possible_combinations)
	print_table(weights=weights, prices=prices)


if __name__=='__main__':
	main()
