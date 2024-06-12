#include <iostream>
#include <vector>
#include <cstdlib> // For rand() function
#include <ctime>   // For time() function

enum class Direction { NORTH, SOUTH, EAST, WEST };

class MazeGame {
private:
    int playerX, playerY; // Player coordinates
    int treasureX, treasureY; // Treasure coordinates
    bool hasTreasure;
    std::vector<std::vector<char>> maze; // Maze grid

public:
    MazeGame() : playerX(0), playerY(0), hasTreasure(false) {
        srand(time(NULL)); // Seed the random number generator
        // Initialize maze grid
        maze = std::vector<std::vector<char>>(10, std::vector<char>(10, '.'));
        // Place the treasure at a random location in the maze
        treasureX = rand() % 10;
        treasureY = rand() % 10;
        maze[treasureY][treasureX] = 'T'; // Mark treasure location
        // Place obstacles in the maze
        for (int i = 0; i < 10; ++i) {
            int obstacleX = rand() % 10;
            int obstacleY = rand() % 10;
            if (obstacleX != treasureX || obstacleY != treasureY)
                maze[obstacleY][obstacleX] = '#'; // Mark obstacle location
        }
    }

    void displayWelcomeMessage() {
        std::cout << "Welcome to the Maze Game!\n";
        std::cout << "Your goal is to find the hidden treasure.\n";
        std::cout << "You are currently at the entrance of the maze.\n";
    }

    void displayInstructions() {
        std::cout << "Choose a direction to move (N, S, E, W): ";
    }

    void move(Direction direction) {
        switch (direction) {
            case Direction::NORTH:
                if (playerY > 0 && maze[playerY - 1][playerX] != '#') // Check if moving north is within bounds and not blocked by obstacle
                    playerY--;
                break;
            case Direction::SOUTH:
                if (playerY < 9 && maze[playerY + 1][playerX] != '#') // Check if moving south is within bounds and not blocked by obstacle
                    playerY++;
                break;
            case Direction::EAST:
                if (playerX < 9 && maze[playerY][playerX + 1] != '#') // Check if moving east is within bounds and not blocked by obstacle
                    playerX++;
                break;
            case Direction::WEST:
                if (playerX > 0 && maze[playerY][playerX - 1] != '#') // Check if moving west is within bounds and not blocked by obstacle
                    playerX--;
                break;
        }
    }

    void checkForTreasure() {
        if (playerX == treasureX && playerY == treasureY) {
            std::cout << "Congratulations! You found the treasure!\n";
            hasTreasure = true;
        }
    }

    bool foundTreasure() const {
        return hasTreasure;
    }

    void displayMazeMatrixStyle() const {
        // Display maze in matrix style
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 10; ++x) {
                if (x == playerX && y == playerY)
                    std::cout << 'P' << ' '; // Player position
                else
                    std::cout << maze[y][x] << ' ';
            }
            std::cout << std::endl;
        }
    }

    void displayMazeTreeStyle() const {
        // Display maze in tree style
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 10; ++x) {
                if (x == playerX && y == playerY)
                    std::cout << 'P'; // Player position
                else
                    std::cout << maze[y][x];
            }
            std::cout << std::endl;
        }
    }

    int getPlayerX() const {
        return playerX;
    }

    int getPlayerY() const {
        return playerY;
    }
};

int main() {
    MazeGame game;
    game.displayWelcomeMessage();

    while (!game.foundTreasure()) {
        std::cout << "Matrix Style:\n";
        game.displayMazeMatrixStyle();
        std::cout << "Tree Style:\n";
        game.displayMazeTreeStyle();

        game.displayInstructions();

        char choice;
        std::cin >> choice;

        Direction direction;
        switch (choice) {
            case 'N':
            case 'n':
                direction = Direction::NORTH;
                break;
            case 'S':
            case 's':
                direction = Direction::SOUTH;
                break;
            case 'E':
            case 'e':
                direction = Direction::EAST;
                break;
            case 'W':
            case 'w':
                direction = Direction::WEST;
                break;
            default:
                std::cout << "Invalid choice! Please enter N, S, E, or W.\n";
                continue;
        }

        game.move(direction);
        game.checkForTreasure();

        // Display player's current location
        std::cout << "You are now at position (" << game.getPlayerX() << ", " << game.getPlayerY() << ").\n";
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}
