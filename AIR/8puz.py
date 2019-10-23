class Node:
	def __init__(self,data,level,fval):
		self.data = data
		self.level = level
		self.fval = fval

	def find(self,data,x):
		for i in range(len(self.data)):
			for j in range(len(self.data)):
				if data[i][j]==x:
					return i,j

	def shuffle(self,data,x1,y1,x2,y2):
		if x2>=0 and x2<len(self.data) and  y2>=0 and y2<len(self.data):
			temp_puz = self.copy(data)
			temp_puz[x1][y1],temp_puz[x2][y2] = temp_puz[x2][y2], temp_puz[x1][y1]
			return temp_puz

		else:
			return None


	def copy(self,data):
		temp = []
		for i in data:
			t = []
			for j in i:
				t.append(j)
			temp.append(t)

		return temp


	def gen_child(self):
		x, y = self.find(self.data,'_')
		valList = [[x,y-1],[x,y+1],[x-1,y],[x+1,y]]
		children = []
		for i in valList:
			child = self.shuffle(self.data,x,y,i[0],i[1])

			if child is not None:
				childNode = Node(child,self.level+1,0)
				children.append(childNode)

		return children


class Puzzle:
	def __init__(self,size):
		self.n = size
		self.open = []
		self.close = []

	def accept(self):
		puz = []
		for i in range(self.n):
			t = input().split()
			puz.append(t)

		return puz


	def f(self,start,goal):
		return start.level + self.h(start.data,goal)

	def h(self,start,goal):
		temp = 0
		for i in range(self.n):
			for j in range(self.n):
				if start[i][j]!=goal[i][j] and start[i][j]!='_':
					temp+=1

		return temp


	def process(self):
		print("enter start puz")
		start = self.accept()
		print("enter goal puz")
		goal = self.accept()

		start = Node(start,0,0)
		start.fval = self.f(start,goal)
		self.open.append(start)

		while True:
			cur = self.open[0]
			for i in cur.data:
				for j in i:
					print(j, end=" ")

				print("\n")

			if self.h(cur.data,goal)==0:
				print("solution found")
				break

			elif len(self.open)!=0:
				for i in cur.gen_child():
					i.fval = self.f(i,goal)
					self.open.append(i)

				self.close.append(cur)
				del self.open[0]
				self.open.sort(key=lambda x:x.fval,reverse = False)

			else:
				print("no solution")


puz = Puzzle(3)
puz.process()