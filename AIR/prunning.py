MAX = 1000
MIN = -1000

def minimax(degree,nodeIdx,maximizer,values,alpha,beta):
	if degree==3:
		return values[nodeIdx]

	if maximizer:
		best = MIN

		for i in range(0,2):
			val = minimax(degree+1,2*nodeIdx+i,False,values,alpha,beta)
			best = max(best,val)
			alpha = max(best,alpha)

			if alpha>=beta:
				break

		return best

	else:
		best = MAX

		for i in range(0,2):
			val = minimax(degree+1,2*nodeIdx+i,True,values,alpha,beta)
			best = min(best,val)
			beta = min(best,beta)

			if alpha>=beta:
				break

		return best


values = [3,5,6,9,1,2,0,-1]
print("best value: ",minimax(0,0,True,values,MIN,MAX))