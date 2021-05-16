import sys
import argparse
import random
import curses

def calcRowsAndColumns(grid):
    rows = len(grid)
    if rows != 0:
        columns = len(grid[0])
    else:
        columns = 0
    return rows, columns


def printGrid (grid, stdoutOrStdScr = False, stdscr = 0, x_coordinate = 0, y_coordinate = 0):
    for row in range(len(grid)):
        row_str = ""
        for column in range(len(grid[row])):
            row_str += grid[row][column]
        if (stdoutOrStdScr):
            stdscr.addstr(y_coordinate + row, x_coordinate, row_str)
        else:
            print(row_str)

def getAliveNeighborCount(i,j):
    rows, columns = calcRowsAndColumns(grid)
    count = 0
    for row_delta in [-1,0,1]:
        for column_delta in [-1,0,1]:
            if (row_delta, column_delta) != (0, 0):
                neighbor_r = (i + row_delta) % rows
                neighbor_c = (j + column_delta) % columns
                if grid[neighbor_r][neighbor_c] == 'X':
                    count += 1
    return count

def cellNextState(i, j):
    nextState = ' '
    count = getAliveNeighborCount(i,j)
    if grid[i][j] == 'X':
        if 2 <= count <= 3:
            nextState = 'X'
    elif count == 3:
            nextState = 'X'

    return nextState

def createNextStateGrid():
    rows, columns = calcRowsAndColumns(grid)
    nextStateGrid = [ [ cellNextState(r,c) for c in range(columns) ] for r in range(rows)]
    return nextStateGrid

def draw_menu(stdscr):
    global grid
    rows, columns = calcRowsAndColumns(grid)
    k = 0
    height, width = stdscr.getmaxyx()
    if rows > (height - 1) or columns > width:
        stdscr.clear()
        stdscr.refresh()
        sys.stdout.write("max number of rows:columns allowed are: " + str(height - 1) + ":" + str(width))
        sys.stdout.write("")
        return
    # Clear and refresh the screen for a blank canvas
    stdscr.clear()
    stdscr.refresh()
    # Start colors in curses
    curses.start_color()
    curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_BLACK, curses.COLOR_WHITE)
    # Loop where k is the last character pressed
    while (k != ord('q')):
        # Initialization
        stdscr.clear()
        height, width = stdscr.getmaxyx()
        x_coordinate = int((width // 2) - (columns // 2) - (columns % 2))
        y_coordinate = int((height // 2) - (rows // 2) - (rows % 2))
        stdscr.attron(curses.color_pair(1))
        printGrid(grid, True, stdscr, x_coordinate, y_coordinate)
        stdscr.attron(curses.color_pair(1))
        grid = createNextStateGrid()
        # Declaration of strings
        statusbarstr = "Press 'q' to exit | Press any other key to progress the game"
        # Render status bar
        stdscr.attron(curses.color_pair(2))
        if len(statusbarstr) >= width:
            statusbarstr = statusbarstr[:width-1]
        stdscr.addstr(height-1, 0, statusbarstr)
        stdscr.addstr(height-1, len(statusbarstr), " " * (width - len(statusbarstr) - 1))
        stdscr.attroff(curses.color_pair(2))
        # Refresh the screen
        stdscr.refresh()
        # Wait for next input
        k = stdscr.getch()

def main():
    global grid
    parser = argparse.ArgumentParser(description='Grid dimensions in the conways game of life.')
    parser.add_argument("-r","--rows", help="number of rows in the grid", type=int, default = 20)
    parser.add_argument("-c","--columns", help="number of columns in the grid", type=int, default = 60)
    args = parser.parse_args()
    rows = args.rows
    columns = args.columns
    grid = [ [ ' ' for _ in range(columns) ] for _ in range(rows)]
    num_of_cells = rows * columns
    cells_alive_initially = random.randint(0, num_of_cells // 3)
    if cells_alive_initially == 0 :
        cells_alive_initially = 1 
    # print(str(cells_alive_initially) + " out of " + str(num_of_cells) + " cells alive initially")
    for _ in range(cells_alive_initially):
        cell_num = random.randint(0, num_of_cells - 1)
        r = cell_num // columns
        c = cell_num % columns
        grid[r][c] = 'X'
    curses.wrapper(draw_menu)
    # printGrid(grid)

if __name__ == "__main__":
    main()
