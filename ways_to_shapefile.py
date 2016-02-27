

import shapefile, sys

class Way:

	def __init__(self, lines):
		self.type = lines[0]
		self.speed_limit = lines[1]
		self.oneway = lines[2]
		self.access = lines[3]
		self.nodes = self.lines_to_nodes(lines[4:])

	def lines_to_nodes(self, lines):
		nodes = []
		for line in lines:
			#print line
			nodes.append([float(line.split(",")[0]), float(line.split(",")[1])])
		return nodes

def get_ways(fich, filename):
	res = shapefile.Writer(shapefile.POLYLINE)
	res.field("type")
	res.field("speed_limit")
	res.field("oneway")
	res.field("access")
	stop = False
	x = 0
	while not stop:
		lines = []
		for i in range(1000):
			line = fich.readline()
			lines.append(line)
			if line == "":
				print "LA"
				stop = True
				break
		if not stop:
			line = fich.readline()
			lines.append(line)
		while line != "" and line != "\n":
			line = fich.readline()
			lines.append(line)
		if line == "":
			stop = True
		start = 0
		if lines[-1] == "\n":
			pass
		else:
			break
		for i,line in enumerate(lines):
			if line == "\n":
				way = Way(lines[start:i])
				res.line(parts=[way.nodes])
				res.record(way.type, way.speed_limit, way.oneway, way.access)
				x += 1
				if x % 1000:
					print x
				start = i + 1
			if x == 3500000:
				break
	res.save(filename.replace(".ways", ""))

def ways_to_shapefile(filename):
	"""res = shapefile.Writer(shapefile.POLYLINE)
	res.field("type")
	res.field("speed_limit")
	res.field("oneway")
	res.field("access")"""
	fich = open(filename)
	ways = get_ways(fich, filename)
	"""print len(ways)
	print "got_ways"
	i = 0
	for way in ways:
		i += 1
		if i % 1000 == 0:
			print i
		res.line(parts=[way.nodes])
		res.record(way.type, way.speed_limit, way.oneway, way.access)
	res.save(filename.replace(".ways", ""))"""

if sys.argv[1]:
	ways_to_shapefile(sys.argv[1])