table = {}
 
def weight(r): return 1
def too_small(i,j,k): return 2**k < j-i+1
 
def calculate(i,j,k):
	if too_small(i,j,k): return None, None
	if i == j: return 0, None
 
	if (i,j,k) in table: return table[(i,j,k)]
 
	result = sum([weight(r) for r in range(i,j+1)])
 
	value, breakpoint = None, None
	for b in range(i,j):
		v1 = calculate(i,b,k-1)[0]
		v2 = calculate(b+1,j,k-1)[0]
		s = None if (v1 == None or v2 == None) else v1+v2
		if s == None: continue
		if value == None or s < value:
			breakpoint, value = b, s
 
	result = None if value == None else result + value
	table[(i,j,k)] = (result, breakpoint)
 
	return (result, breakpoint)
 

def build_tree(i,j,k):
    res = calculate(i,j,k)
    
   # print(res)
    if res == (None, None):
        return None
    if res[1] == None:
        return (weight(i))
    return (build_tree(i, res[1], k -1), build_tree(res[1], j, k -1))

def print_tree(a, height):
    if (a == None):
        return None
    str = "::" * height
    if a.__class__() is int():
        print(str, a)
    else:
        print(str, 'Node')
        print_tree(a[0], height + 1)
        print_tree(a[1], height + 1)


print_tree(build_tree(1,10,4), 0)
