import pygame
import random
import math
import tetris_utils  # Import our new utility module

# Add this enum definition for game states
class GameState:
    MENU = 0
    PLAYING = 1
    PAUSED = 2
    GAME_OVER = 3

# Constants for fall speeds
NORMAL_FALL_SPEED = 500  # Normal fall speed in milliseconds
FAST_FALL_SPEED = 50    # Fast fall speed in milliseconds

# Constants for horizontal movement
NORMAL_MOVE_DELAY = 150  # Initial delay before rapid movement
FAST_MOVE_DELAY = 50    # Speed of rapid movement

# Add these to the constants at the top
LEVEL_UP_LINES = 10  # Lines needed to level up
BASE_FALL_SPEED = 500  # Starting fall speed
LEVEL_SPEED_FACTOR = 0.75  # Speed multiplier per level

# Add these constants
PIECE_LOCK_DELAY = 500  # milliseconds
WALL_KICK_DATA = {
    'JLSTZ': [
        [(0, 0), (-1, 0), (-1, -1), (0, 2), (-1, 2)],  # 0->R
        [(0, 0), (1, 0), (1, 1), (0, -2), (1, -2)],    # R->0
        [(0, 0), (1, 0), (1, -1), (0, 2), (1, 2)],     # R->2
        [(0, 0), (-1, 0), (-1, 1), (0, -2), (-1, -2)], # 2->R
    ],
    'I': [
        [(0, 0), (-2, 0), (1, 0), (-2, 1), (1, -2)],   # 0->R
        [(0, 0), (2, 0), (-1, 0), (2, -1), (-1, 2)],   # R->0
        [(0, 0), (-1, 0), (2, 0), (-1, -2), (2, 1)],   # R->2
        [(0, 0), (1, 0), (-2, 0), (1, 2), (-2, -1)],   # 2->R
    ]
}

# Initialize Pygame
pygame.init()

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
CYAN = (0, 255, 255)
YELLOW = (255, 255, 0)
MAGENTA = (255, 0, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
ORANGE = (255, 165, 0)
GRID_COLOR = (50, 50, 50)  # Dark grey for grid lines
BORDER_COLOR = (128, 128, 128)  # Grey for border

# Game dimensions
BLOCK_SIZE = 30
GRID_WIDTH = 20
GRID_HEIGHT = 40
SCREEN_WIDTH = BLOCK_SIZE * (GRID_WIDTH + 6)
SCREEN_HEIGHT = BLOCK_SIZE * GRID_HEIGHT

# Tetromino shapes
SHAPES = [
    [[1, 1, 1, 1]], # I
    [[1, 1], [1, 1]], # O
    [[1, 1, 1], [0, 1, 0]], # T
    [[1, 1, 1], [1, 0, 0]], # L
    [[1, 1, 1], [0, 0, 1]], # J
    [[1, 1, 0], [0, 1, 1]], # S
    [[0, 1, 1], [1, 1, 0]]  # Z
]

COLORS = [CYAN, YELLOW, MAGENTA, ORANGE, BLUE, GREEN, RED]

class Tetris:
    def __init__(self):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption('Tetris')
        self.clock = pygame.time.Clock()
        self.reset_game()
        self.game_state = GameState.MENU
        self.lock_delay_start = None

    def reset_game(self):
        self.grid = [[0 for _ in range(GRID_WIDTH)] for _ in range(GRID_HEIGHT)]
        self.game_over = False
        self.score = 0
        self.fall_time = 0
        self.fall_speed = BASE_FALL_SPEED
        self.move_time = 0
        self.move_delay = NORMAL_MOVE_DELAY
        self.last_move_time = 0
        self.first_move = True
        # Initialize next_piece first
        self.next_piece = self.generate_piece()
        # Then get the current piece from it
        self.current_piece = self.new_piece()
        self.level = 1
        self.lines_cleared = 0
        self.combo = 0
        self.high_score = self.load_high_score()
        self.held_piece = None
        self.can_hold = True

    def generate_piece(self):
        """Generate a new random piece"""
        shape = random.randint(0, len(SHAPES) - 1)
        return {
            'shape': SHAPES[shape],
            'color': COLORS[shape],
            'x': GRID_WIDTH // 2 - len(SHAPES[shape][0]) // 2,
            'y': 0
        }

    def new_piece(self):
        """Get the next piece and generate a new next piece"""
        current = self.next_piece
        self.next_piece = self.generate_piece()
        return current

    def valid_move(self, piece, x, y):
        for i, row in enumerate(piece['shape']):
            for j, cell in enumerate(row):
                if cell:
                    if not (0 <= x + j < GRID_WIDTH and
                           0 <= y + i < GRID_HEIGHT and
                           self.grid[y + i][x + j] == 0):
                        return False
        return True

    def rotate_piece(self, piece):
        rotated = list(zip(*piece['shape'][::-1]))

        # Determine piece type
        if len(piece['shape'][0]) == 4:  # I piece
            # Select just one set of tests from WALL_KICK_DATA['I']
            kick_data = WALL_KICK_DATA['I'][0]  # Using the first test set
        else:  # JLSTZ pieces
            # Select just one set of tests from WALL_KICK_DATA['JLSTZ']
            kick_data = WALL_KICK_DATA['JLSTZ'][0]  # Using the first test set

        if self.try_wall_kick(piece, rotated, kick_data):
            pass

    def place_piece(self, piece):
        for i, row in enumerate(piece['shape']):
            for j, cell in enumerate(row):
                if cell:
                    self.grid[piece['y'] + i][piece['x'] + j] = piece['color']

    def clear_lines(self):
        """Clear completed lines and update score"""
        # Call the new utility function to clear lines and get indices of cleared lines
        lines_to_clear = tetris_utils.clear_lines(self.grid, GRID_WIDTH)

        num_lines_cleared = len(lines_to_clear)

        if num_lines_cleared:
            # Calculate score and update combo
            score_to_add, self.combo = tetris_utils.calculate_score(num_lines_cleared, self.level, self.combo)
            self.score += score_to_add

            # Update total lines cleared
            self.lines_cleared += num_lines_cleared

            # Update level
            self.update_level()

            # Update high score
            if self.score > self.high_score:
                self.high_score = self.score
                self.save_high_score()

            if self.level < (self.lines_cleared // LEVEL_UP_LINES) + 1:
                pass
        else:
            self.combo = 0

    def get_ghost_piece_position(self):
        """Get the position where the current piece would land"""
        ghost_y = self.current_piece['y']
        while self.valid_move(self.current_piece, self.current_piece['x'], ghost_y + 1):
            ghost_y += 1
        return ghost_y

    def instant_drop(self):
        """Drop the piece instantly to the bottom"""
        while self.valid_move(self.current_piece,
                            self.current_piece['x'],
                            self.current_piece['y'] + 1):
            self.current_piece['y'] += 1
        self.place_piece(self.current_piece)
        self.clear_lines()
        self.current_piece = self.new_piece()
        if not self.valid_move(self.current_piece,
                             self.current_piece['x'],
                             self.current_piece['y']):
            self.game_over = True

    def draw_next_piece(self, x, y):
        """Draw the next piece preview"""
        # Draw the "Next Piece" text
        next_font = pygame.font.Font(None, 30)
        next_text = next_font.render('Next Piece:', True, WHITE)
        self.screen.blit(next_text, (x, y))

        # Calculate the size of the preview box
        box_size = BLOCK_SIZE * 4
        box_margin = 10
        box_y = y + 30  # Space below the text

        # Draw preview box background
        pygame.draw.rect(self.screen, GRID_COLOR, 
                        (x, box_y, box_size, box_size))

        # Center the piece in the preview box
        piece_height = len(self.next_piece['shape']) * BLOCK_SIZE
        piece_width = len(self.next_piece['shape'][0]) * BLOCK_SIZE
        start_x = x + (box_size - piece_width) // 2
        start_y = box_y + (box_size - piece_height) // 2

        # Draw the next piece
        for i, row in enumerate(self.next_piece['shape']):
            for j, cell in enumerate(row):
                if cell:
                    pygame.draw.rect(
                        self.screen,
                        self.next_piece['color'],
                        (start_x + j * BLOCK_SIZE,
                         start_y + i * BLOCK_SIZE,
                         BLOCK_SIZE - 1, BLOCK_SIZE - 1)
                    )

    def draw_held_piece(self, x, y):
        if not self.held_piece:
            return

        held_font = pygame.font.Font(None, 30)
        held_text = held_font.render('Hold:', True, WHITE)
        self.screen.blit(held_text, (x, y))

        box_size = BLOCK_SIZE * 4
        box_y = y + 30

        pygame.draw.rect(self.screen, GRID_COLOR, 
                        (x, box_y, box_size, box_size))

        piece_height = len(self.held_piece['shape']) * BLOCK_SIZE
        piece_width = len(self.held_piece['shape'][0]) * BLOCK_SIZE
        start_x = x + (box_size - piece_width) // 2
        start_y = box_y + (box_size - piece_height) // 2

        for i, row in enumerate(self.held_piece['shape']):
            for j, cell in enumerate(row):
                if cell:
                    pygame.draw.rect(
                        self.screen,
                        self.held_piece['color'],
                        (start_x + j * BLOCK_SIZE,
                         start_y + i * BLOCK_SIZE,
                         BLOCK_SIZE - 1, BLOCK_SIZE - 1)
                    )

    def draw(self):
        self.screen.fill(BLACK)

        # Draw border around play area
        pygame.draw.rect(self.screen, BORDER_COLOR, 
                        (0, 0, GRID_WIDTH * BLOCK_SIZE, GRID_HEIGHT * BLOCK_SIZE), 2)

        # Draw light grid
        for i in range(GRID_HEIGHT):
            pygame.draw.line(self.screen, GRID_COLOR, 
                           (0, i * BLOCK_SIZE), 
                           (GRID_WIDTH * BLOCK_SIZE, i * BLOCK_SIZE))
        for j in range(GRID_WIDTH):
            pygame.draw.line(self.screen, GRID_COLOR, 
                           (j * BLOCK_SIZE, 0), 
                           (j * BLOCK_SIZE, GRID_HEIGHT * BLOCK_SIZE))

        # Draw grid
        for i in range(GRID_HEIGHT):
            for j in range(GRID_WIDTH):
                if self.grid[i][j]:
                    pygame.draw.rect(self.screen, self.grid[i][j],
                                   (j * BLOCK_SIZE, i * BLOCK_SIZE,
                                    BLOCK_SIZE - 1, BLOCK_SIZE - 1))

        if not self.game_over:
            # Draw ghost piece
            ghost_y = self.get_ghost_piece_position()
            for i, row in enumerate(self.current_piece['shape']):
                for j, cell in enumerate(row):
                    if cell:
                        ghost_color = tuple(min(255, c + 100) for c in self.current_piece['color'])
                        pygame.draw.rect(
                            self.screen,
                            ghost_color,
                            ((self.current_piece['x'] + j) * BLOCK_SIZE,
                             (ghost_y + i) * BLOCK_SIZE,
                             BLOCK_SIZE - 1, BLOCK_SIZE - 1),
                            2
                        )

            # Draw current piece
            for i, row in enumerate(self.current_piece['shape']):
                for j, cell in enumerate(row):
                    if cell:
                        pygame.draw.rect(
                            self.screen,
                            self.current_piece['color'],
                            ((self.current_piece['x'] + j) * BLOCK_SIZE,
                             (self.current_piece['y'] + i) * BLOCK_SIZE,
                             BLOCK_SIZE - 1, BLOCK_SIZE - 1)
                        )

        # Draw score and level information
        sidebar_x = GRID_WIDTH * BLOCK_SIZE + 10
        font = pygame.font.Font(None, 36)

        # Score
        score_text = font.render(f'Score: {self.score}', True, WHITE)
        self.screen.blit(score_text, (sidebar_x, 10))

        # High Score
        high_score_text = font.render(f'High: {self.high_score}', True, WHITE)
        self.screen.blit(high_score_text, (sidebar_x, 40))

        # Level
        level_text = font.render(f'Level: {self.level}', True, WHITE)
        self.screen.blit(level_text, (sidebar_x, 70))

        # Lines
        lines_text = font.render(f'Lines: {self.lines_cleared}', True, WHITE)
        self.screen.blit(lines_text, (sidebar_x, 100))

        # Draw held piece
        self.draw_held_piece(sidebar_x, 140)

        # Draw next piece (moved down)
        self.draw_next_piece(sidebar_x, 280)

        # Controls (moved down to make space for next piece preview)
        controls_font = pygame.font.Font(None, 24)
        controls = [
            'Controls:',
            '↑: Rotate',
            '←→: Move',
            '↓: Fast Drop',
            'Space: Instant Drop',
            'R: Restart',
            'Q: Quit'
        ]

        for i, text in enumerate(controls):
            control_text = controls_font.render(text, True, WHITE)
            self.screen.blit(control_text, (sidebar_x, 200 + i * 25))  # Moved down

        if self.game_over:
            game_over_text = font.render('GAME OVER', True, WHITE)
            self.screen.blit(game_over_text, (sidebar_x, 370))
            restart_text = controls_font.render('Press R to restart', True, WHITE)
            self.screen.blit(restart_text, (sidebar_x, 410))

        pygame.display.flip()

    def run(self):
        while True:
            if self.game_over:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        return
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_r:
                            self.reset_game()
                        elif event.key == pygame.K_q:
                            return
                self.draw()
                continue

            current_time = pygame.time.get_ticks()

            # Reset fall speed to normal at the start of each frame
            self.fall_speed = NORMAL_FALL_SPEED

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    return
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_UP:
                        self.rotate_piece(self.current_piece)
                    elif event.key == pygame.K_SPACE:
                        self.instant_drop()
                    elif event.key == pygame.K_q:
                        return
                    # Handle immediate movement for left/right keys
                    elif event.key == pygame.K_LEFT:
                        if self.valid_move(self.current_piece,
                                         self.current_piece['x'] - 1,
                                         self.current_piece['y']):
                            self.current_piece['x'] -= 1
                            self.last_move_time = current_time
                            self.first_move = True
                    elif event.key == pygame.K_RIGHT:
                        if self.valid_move(self.current_piece,
                                         self.current_piece['x'] + 1,
                                         self.current_piece['y']):
                            self.current_piece['x'] += 1
                            self.last_move_time = current_time
                            self.first_move = True
                    elif event.key == pygame.K_c:  # 'C' key for hold
                        self.hold_piece()
                elif event.type == pygame.KEYUP:
                    if event.key in [pygame.K_LEFT, pygame.K_RIGHT]:
                        self.first_move = True

            # Handle continuous key presses for horizontal movement
            keys = pygame.key.get_pressed()
            if keys[pygame.K_LEFT] or keys[pygame.K_RIGHT]:
                if self.first_move:
                    self.move_delay = NORMAL_MOVE_DELAY
                    self.first_move = False
                elif current_time - self.last_move_time >= self.move_delay:
                    dx = -1 if keys[pygame.K_LEFT] else 1
                    if self.valid_move(self.current_piece,
                                     self.current_piece['x'] + dx,
                                     self.current_piece['y']):
                        self.current_piece['x'] += dx
                        self.last_move_time = current_time
                        self.move_delay = FAST_MOVE_DELAY
            else:
                self.first_move = True

            # Handle vertical movement
            if keys[pygame.K_DOWN]:
                self.fall_speed = FAST_FALL_SPEED

            # Handle piece falling
            if current_time - self.fall_time > self.fall_speed:
                self.fall_time = current_time
                if self.valid_move(self.current_piece,
                                 self.current_piece['x'],
                                 self.current_piece['y'] + 1):
                    self.current_piece['y'] += 1
                else:
                    self.place_piece(self.current_piece)
                    self.clear_lines()
                    self.current_piece = self.new_piece()
                    if not self.valid_move(self.current_piece,
                                         self.current_piece['x'],
                                         self.current_piece['y']):
                        self.game_over = True

            self.draw()
            self.clock.tick(60)

    def load_high_score(self):
        try:
            with open('highscore.txt', 'r') as f:
                return int(f.read())
        except:
            return 0

    def save_high_score(self):
        with open('highscore.txt', 'w') as f:
            f.write(str(max(self.score, self.high_score)))

    def update_level(self):
        new_level = (self.lines_cleared // LEVEL_UP_LINES) + 1
        if new_level != self.level:
            self.level = new_level
            self.fall_speed = int(BASE_FALL_SPEED * (LEVEL_SPEED_FACTOR ** (self.level - 1)))

    def hold_piece(self):
        if not self.can_hold:
            return

        if self.held_piece is None:
            self.held_piece = {
                'shape': self.current_piece['shape'],
                'color': self.current_piece['color']
            }
            self.current_piece = self.new_piece()
        else:
            temp = self.held_piece
            self.held_piece = {
                'shape': self.current_piece['shape'],
                'color': self.current_piece['color']
            }
            self.current_piece = {
                'shape': temp['shape'],
                'color': temp['color'],
                'x': GRID_WIDTH // 2 - len(temp['shape'][0]) // 2,
                'y': 0
            }
        self.can_hold = False

    def try_wall_kick(self, piece, rotated_shape, tests):
        original_x = piece['x']
        original_y = piece['y']

        for dx, dy in tests:
            piece['x'] = original_x + dx
            piece['y'] = original_y + dy
            if self.valid_move({'shape': rotated_shape, 'x': piece['x'], 'y': piece['y']},
                              piece['x'], piece['y']):
                piece['shape'] = rotated_shape
                return True

        piece['x'] = original_x
        piece['y'] = original_y
        return False

    def draw_menu(self):
        title_font = pygame.font.Font(None, 64)
        menu_font = pygame.font.Font(None, 36)

        title = title_font.render('TETRIS', True, WHITE)
        start = menu_font.render('Press ENTER to Start', True, WHITE)
        controls = menu_font.render('Press H for Controls', True, WHITE)

        self.screen.blit(title, (SCREEN_WIDTH//2 - title.get_width()//2, SCREEN_HEIGHT//4))
        self.screen.blit(start, (SCREEN_WIDTH//2 - start.get_width()//2, SCREEN_HEIGHT//2))
        self.screen.blit(controls, (SCREEN_WIDTH//2 - controls.get_width()//2, SCREEN_HEIGHT//2 + 50))

    def draw_pause_menu(self):
        overlay = pygame.Surface((SCREEN_WIDTH, SCREEN_HEIGHT))
        overlay.set_alpha(128)
        overlay.fill(BLACK)
        self.screen.blit(overlay, (0, 0))

        pause_font = pygame.font.Font(None, 36)
        pause_text = pause_font.render('Game Paused', True, WHITE)
        self.screen.blit(pause_text, (SCREEN_WIDTH//2 - pause_text.get_width()//2, SCREEN_HEIGHT//2 - 50))

if __name__ == '__main__':
    game = Tetris()
    game.run()
    pygame.quit()
