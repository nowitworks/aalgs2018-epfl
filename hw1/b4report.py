# Team name: algo@epfl
#
# - Rodrigo André Moreira Bernardo
# - Joao Pinto Silveira
# - Marin Gabriel Thiercelin
#

def read_input_file(testcase):

	with open("tests/"+testcase) as f:
		_in = f.readline()

		_,m = map(int, _in.split(" "))

		_in = f.readline()
		costs = list(map(int, _in.split(" ")))
		remaining_costs = list(map(int, _in.split(" ")))

		trails = []
		for i in range(m):
			_in = f.readline()

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

	return C, totalcost, budgets, trails



def print_output(C, budgets, trails):
	# 1st line
	print(len(C))

	# 2nd line
	print(" ".join(map(str, C)))

	# 3rd line
	print(" ".join(map(str, [budgets[trail] for trail in trails])))
	
def do_line(testcase, f):
	costs, remaining_costs, trails = read_input_file(testcase)

	_, totalcost, budgets, _ = vertex_cover(costs, remaining_costs, trails)

	#own_ratio = sum([b for b in budgets.values()]) / totalcost
	own_ratio = totalcost / sum([b for b in budgets.values()])

	lp_cost  = 0
	opt_cost = 0

	with open("tests/"+testcase+".opt") as opt:
		lp_cost += float(opt.readline())
		opt_cost += int(opt.readline())

	#lp_ratio  = lp_cost / totalcost
	lp_ratio  = totalcost / lp_cost
	#opt_ratio = opt_cost / totalcost
	opt_ratio = totalcost / opt_cost

	line = "\t".join([testcase] + list(map(str, [own_ratio, lp_ratio, opt_ratio]))) + "\n"

	f.write(line)

def main():

	with open("results.out", "w+") as f:

		for i in range(1,10):

			testcase = "0"+str(i)			
			do_line(testcase, f)

		for i in range(10,21):

			testcase = str(i)
			do_line(testcase, f)


if __name__ == "__main__":
	main()	

