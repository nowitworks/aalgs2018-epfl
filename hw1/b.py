# Team name: algo@epfl
#
# - Rodrigo André Moreira Bernardo
# - Joao Pinto Silveira
# - Marin Gabriel Thiercelin
#

def read_input():
	_in = input()

	_,m = map(int, _in.split(" "))

	_in = input()
	costs = list(map(int, _in.split(" ")))
	remaining_costs = list(map(int, _in.split(" ")))

	trails = []
	for i in range(m):
		_in = input()

		trail = tuple(map(int, _in.split(" ")))

		trails += [trail]

	return costs, remaining_costs, trails



def vertex_cover(costs, remaining_costs, trails):
	
	def init_budgets(trails):
		return dict([(trail, 0) for trail in trails])

	budgets = init_budgets(trails)

	
	def increase_budget(trail):

		u,v = trail
		rc_u, rc_v = remaining_costs[u-1], remaining_costs[v-1]

		# don't do anything if the dual constraint is already tight
		if rc_u == 0 or rc_v == 0:
			return
		
		# otherwise inrease as much as possible
		budget = min(rc_u, rc_v)
		budgets[trail] = budget

		remaining_costs[u-1] -= budget
		remaining_costs[v-1] -= budget



	for trail in trails:
		increase_budget(trail)

	C = []
	totalcost = 0

	for vx, rc in enumerate(remaining_costs):
		if rc == 0:
			C += [vx+1]
			totalcost += costs[vx]

	return C, budgets, trails



def print_output(C, budgets, trails):
	# 1st line
	print(len(C))

	# 2nd line
	print(" ".join(map(str, C)))

	# 3rd line
	print(" ".join(map(str, [budgets[trail] for trail in trails])))
	

def main():
	costs, remaining_costs, trails = read_input()

	C, budgets, trails = vertex_cover(costs, remaining_costs, trails)

	print_output(C, budgets, trails)


if __name__ == "__main__":
	main()	

