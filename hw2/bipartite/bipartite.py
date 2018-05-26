# Advanced Algorithms - Homework 2 - Problem 4
#
# Team name: algo@epfl
#
# - Rodrigo Andre Moreira Bernardo
# - Joao Pinto Silveira
# - Marin Gabriel Thiercelin
#

from random import randrange

prime = 1000000009


def read_input():
	# n vertices, m edges
	n, m = map(int, input().split())
	
	edges = []
	for __ in range(m):
		edges.append(tuple(map(int, input().split())))

	return n, m, edges


def mod_inv(x, p=prime):
	return pow(x, p-2, p)


def mod_mul(x, y, p=prime):
	x = x % p
	y = y % p
	return (x*y) % p


def mod_mul_s(*numbers, p=prime):
	result = 1 % p
	
	for n in numbers:
		result = mod_mul(result, n, p)

	return result


def mod_div(x ,y, p=prime):
	return mod_mul(x, mod_inv(y, p), p)


def mod_add(x, y, p=prime):
	return (x + y) % p


def print_matrix(m):
	for l in m:
		print(l)


def build_matrix(n, edges, field_size=prime):

	M = [[0 for i in range(n)] for j in range(n)]

	for e in edges:
		x = randrange(field_size)
		i, j = min(e)-1, max(e)-1

		M[i][j] = x
		M[j][i] = -x

	return M


def gauss_el(matrix, p=prime):
	M = matrix
	n = len(matrix)
	
	for i in range(n):

		# print(i,".1")
		# print_matrix(M)

		# Find max in column
		# TODO: replace abs with mod
		max_el = abs(M[i][i])
		max_row = i
		for k in range(i+1,n):
			if abs(M[k][i]) > max_el:
				max_el = abs(M[k][i])
				max_row = k
		
		
		# Swap max with current row
		M[max_row], M[i] = M[i], M[max_row]
		
		# Zero all below current row in column
		for k in range(i+1,n):
			c = - mod_div(M[k][i], M[i][i], p)
			for j in range(i, n):
				M[k][j] = 0 if i == j else mod_add(M[k][j], mod_mul(M[i][j], c, p), p)

	return M


def det_is_not_0(g_matrix):
	n = len(g_matrix)

	for i in range(n):
		if g_matrix[i][i] == 0:
			return False

	return True



def main():
	n, m, edges = read_input()

	repetitions = 1

	for __ in range(repetitions):
		M = build_matrix(n, edges, prime)
		
		M = gauss_el(M, prime)

		if det_is_not_0(M):
			print("YES")
			return

	print("NO")



if __name__ == "__main__":
	main()
