import ctypes
import numpy as np

lib = ctypes.cdll.LoadLibrary("./libgobang.so")


def nextStep(board, whichPerson, location):
    """
    Enter the current chessboard, player and drop position, return the output status and new chessboard.
    status: -1 : error input
             0 : the game is not over
             1 : win
             2 : it ends in a draw
    :param board: ndarray(15 * 15)
    :param whichPerson: int
    :param location: ndarray(2)
    :return: int, ndarray(15 * 15)
    """
    next_step = lib.next_step
    next_step.restype = ctypes.c_int
    board_C = b_py2b_c(board)
    location = (ctypes.c_int * 2)(*location)
    res = next_step(board_C, whichPerson, location)
    return res, np.array(board_C).reshape(15, 15)


def showBoard(board):
    """
    Chess board showing input
    :param board: ndarray(15 * 15)
    :return: int
    """
    show_board = lib.show_board
    show_board.restype = ctypes.c_int
    board_C = b_py2b_c(board)
    res = show_board(board_C)
    return res


def b_py2b_c(board):
    """
    Converting python-type chessboard to C-type chessboard
    :param board: ndarray(15 * 15)
    :return: ctypes.c_int(225)
    """
    board_PY = board.reshape(-1).tolist()
    board_C = (ctypes.c_int * (15 * 15))(*board_PY)
    return board_C




