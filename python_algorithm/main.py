import numpy as np
import functions


board = np.zeros((15, 15), dtype=int)

location = np.array([3, 3])

state_type, n_board = functions.nextStep(board, 1, location)

functions.showBoard(n_board)



