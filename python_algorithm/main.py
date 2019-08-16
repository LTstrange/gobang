import numpy as np
import functions


board = np.zeros((15, 15), dtype=int)

location = [3, 3]

print(functions.nextStep(board, 1, location))

