def clear_lines(grid, grid_width):
    """
    Clear completed lines from the grid and return the indices of cleared lines.

    This improved version ensures all eligible lines are properly identified and cleared.

    Args:
        grid: 2D list representing the game grid
        grid_width: Width of the grid

    Returns:
        list of indices of cleared lines
    """
    lines_to_clear = []

    # Check each row from bottom to top
    for i in range(len(grid) - 1, -1, -1):
        # Ensure we're checking each cell in the row properly
        if all(cell != 0 for cell in grid[i]):
            lines_to_clear.append(i)

    # Remove completed lines from the grid
    for line in sorted(lines_to_clear, reverse=True):
        # Remove the completed line
        del grid[line]
        # Add a new empty line at the top
        grid.insert(0, [0 for _ in range(grid_width)])

    return lines_to_clear
