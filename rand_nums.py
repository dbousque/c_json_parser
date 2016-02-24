

import random

res = []
for i in range(1000):
	res.append(random.randint(1, 10000))
for elt in res:
	print str(elt) + " ",
