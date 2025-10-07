#coding:utf-8
'''
    Lab 2
    井字棋(Tic tac toe)Python语言实现, 带有Alpha-Beta剪枝的Minimax算法.
'''
import random

# 棋盘位置表示（0-8）:
# 0  1  2
# 3  4  5
# 6  7  8

# 设定获胜的组合方式(横、竖、斜)
WINNING_TRIADS = ((0, 1, 2), (3, 4, 5), (6, 7, 8),
                  (0, 3, 6), (1, 4, 7),(2, 5, 8),
                  (0, 4, 8), (2, 4, 6))
# 设定棋盘按一行三个打印
PRINTING_TRIADS = ((0, 1, 2), (3, 4, 5), (6, 7, 8))
# 用一维列表表示棋盘:
SLOTS = (0, 1, 2, 3, 4, 5, 6, 7, 8)
# -1表示X玩家 0表示空位 1表示O玩家.
X_token = -1
Open_token = 0
O_token = 1

MARKERS = ['_', 'O', 'X']
END_PHRASE = ('平局', '胜利', '失败')


def print_board(board):
    """打印当前棋盘"""
    for row in PRINTING_TRIADS:
        r = ' '
        for hole in row:
            r += MARKERS[board[hole]] + ' '
        print(r)


def legal_move_left(board):
    """ 判断棋盘上是否还有空位 """
    for slot in SLOTS:
        if board[slot] == Open_token:
            return True
    return False


def winner(board):
    """ 判断局面的胜者,返回值-1表示X获胜,1表示O获胜,0表示平局或者未结束"""
    for triad in WINNING_TRIADS:
        triad_sum = board[triad[0]] + board[triad[1]] + board[triad[2]]
        if triad_sum == 3 or triad_sum == -3:
            return board[triad[0]]  # 表示棋子的数值恰好也是-1:X,1:O
    return 0

def minimax(board, depth, alpha, beta, is_max):
    """is_max表示当前是否是极大值节点"""
    res = winner(board)

    if res == O_token:
        return 10-depth
    elif res == X_token:
        return depth-10
    elif not legal_move_left(board): return 0

    if is_max:
        maxScore = -float('inf')
        for i in SLOTS:
            if board[i] == Open_token:
                board[i] = O_token
                score = minimax(board, depth+1, alpha, beta, False)
                board[i] = Open_token
                maxScore = max(maxScore, score)

                alpha = max(alpha, score)
                if beta <= alpha: break

        return maxScore
    else:
        minScore = float('inf')
        for i in SLOTS:
            if board[i] == Open_token:
                board[i] = X_token
                score = minimax(board, depth+1, alpha, beta, True)
                board[i] = Open_token
                minScore = min(minScore, score)

                beta = min(beta, score)
                if beta <= alpha: break

        return minScore
        

def determine_move(board):
    """
        决定电脑(玩家O)的下一步棋(使用Alpha-beta 剪枝优化搜索效率)
        Args:
            board (list):井字棋盘

        Returns:
            next_move(int): 电脑(玩家O) 下一步棋的位置
    
    """

    bestScore = -float('inf')

    for i in SLOTS:
        if board[i] == Open_token:
            board[i] = O_token
            score = minimax(board, 0, -float('inf'), float('inf'), False)
            board[i] = Open_token
            if score > bestScore:
                bestScore = score
                next_move = i

    return next_move


HUMAN = 1
COMPUTER = 0


def main():
    """主函数,先决定谁是X(先手方),再开始下棋"""
    next_move = HUMAN
    opt = input("请选择先手方，输入X表示玩家先手，输入O表示电脑先手：")
    if opt in ("X", "x"):
        next_move = HUMAN
    elif opt in ("O", "o"):
        next_move = COMPUTER
    else:
        print("输入有误，默认玩家先手")

    # 初始化空棋盘
    board = [Open_token for i in range(9)]

    flag = True
    # 开始下棋
    while legal_move_left(board) and winner(board) == Open_token:
        if not flag:
            print()
            print_board(board)
        flag = False
        if next_move == HUMAN and legal_move_left(board):
            try:
                print("\n")
                humanmv = int(input("请输入你要落子的位置(0-8)："))
                if board[humanmv] != Open_token:
                    continue
                board[humanmv] = X_token
                next_move = COMPUTER
            except:
                print("输入有误，请重试")
                continue
        if next_move == COMPUTER and legal_move_left(board):
            mymv = determine_move(board)
            print("Computer最终决定下在", mymv)
            board[mymv] = O_token
            next_move = HUMAN

    # 输出结果
    print_board(board)
    print(["平局", "Computer赢了", "你赢了"][winner(board)])


if __name__ == '__main__':
    main()
