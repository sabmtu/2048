#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() {

}

GameEngine::GameEngine(const glm::vec2 &top_left_corner, size_t num_tiles_per_side, double board_size)
    : top_left_corner_(top_left_corner), num_tiles_per_side_(num_tiles_per_side),
    tile_side_length_(board_size / num_tiles_per_side_),
    board_size_(board_size) {
    current_direction_ = Direction::STILL;

    board_size_ += 1;
    glm::vec2 top_left = top_left_corner_;
    for (size_t i = 0; i < num_tiles_per_side_; i++) {
        vector<Tile> test;
        for (size_t j = 0; j < num_tiles_per_side_; j++) {
            test.push_back(kEmptyTile);
            top_left.x += tile_side_length_;
        }
        tiles_.push_back(test);
        top_left = glm::vec2(top_left_corner_.x, top_left.y + tile_side_length_);
    }

    Tile tile(2, "white");
    tiles_[0][0] = tile;
    tiles_[2][0] = tile;
    tiles_[3][0] = tile;
}

const vector<vector<Tile>> &GameEngine::GetTiles() {
    return tiles_;
}

void GameEngine::SetCurrentDirection(const Direction& direction) {
    current_direction_ = direction;
}

void GameEngine::MoveTiles() {
    switch (current_direction_) {
        case Direction::STILL:
            return;
        case Direction::UP:
            MoveTilesUp();
            break;

        case Direction::DOWN:
            MoveTilesDown();
            break;

        case Direction::LEFT:
            MoveTilesLeft();
            break;

        case Direction::RIGHT:
            MoveTilesRight();
            break;

        default:
            return;
    }
}


void GameEngine::MoveTilesUp() {
    for (size_t row = 0; row < num_tiles_per_side_ - 1; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[row][col].IsEmpty()) {

                //Moves tile below to current tile position and sets tile below position to an empty tile
                tiles_[row][col] = tiles_[row + 1][col];
                tiles_[row + 1][col] = kEmptyTile;

            } else if (CanMergeTileUp(row, col)) {
                MergeTiles(row, col);
            }
        }
    }
    //current_direction_ = Direction::STILL;
}

void GameEngine::MoveTilesRight() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = num_tiles_per_side_ - 1; col >= 1; col--) {
            if (tiles_[row][col].IsEmpty()) {

                //Moves tile to the left to current tile position and sets left tile to an empty tile
                tiles_[row][col] = tiles_[row][col - 1];
                tiles_[row][col - 1] = kEmptyTile;

            } else if (CanMergeTileRight(row, col)) {
                MergeTiles(row, col);
            }
        }
    }
}

void GameEngine::MoveTilesLeft() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_ - 1; col++) {
            if (tiles_[row][col].IsEmpty()) {

                //Moves tile to the right to current tile position and sets right tile position to an empty tile
                tiles_[row][col] = tiles_[row][col + 1];
                tiles_[row][col + 1] = kEmptyTile;

            } else if (CanMergeTileLeft(row, col)) {
                MergeTiles(row, col);
            }
        }
    }
}

void GameEngine::MoveTilesDown() {
    for (size_t row = num_tiles_per_side_ - 1; row >= 1; row--) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[row][col].IsEmpty()) {

                //Moves tile above to current tile position and sets tile above to an empty tile
                tiles_[row][col] = tiles_[row - 1][col];
                tiles_[row - 1][col] = kEmptyTile;

            } else if (CanMergeTileDown(row, col)) {
                MergeTiles(row, col);
            }
        }
    }
}

bool GameEngine::CanMergeTileUp(size_t row, size_t col) {
    return (!tiles_[row][col].IsEmpty() && (tiles_[row + 1][col].GetNumber() == tiles_[row][col].GetNumber()));
}

bool GameEngine::CanMergeTileRight(size_t row, size_t col) {
    return (!tiles_[row][col].IsEmpty() && (tiles_[row][col - 1].GetNumber() == tiles_[row][col].GetNumber()));
}

bool GameEngine::CanMergeTileLeft(size_t row, size_t col) {
    return (!tiles_[row][col].IsEmpty() && (tiles_[row][col + 1].GetNumber() == tiles_[row][col].GetNumber()));
}

bool GameEngine::CanMergeTileDown(size_t row, size_t col) {
    return (!tiles_[row][col].IsEmpty() && (tiles_[row - 1][col].GetNumber() == tiles_[row][col].GetNumber()));
}

void GameEngine::MergeTiles(size_t row, size_t col) {
    Tile combined_tile(2 * tiles_[row][col].GetNumber(), "yellow");

    //Sets tile at given row and column to new merged tile and sets corresponding touching tile to empty
    if (current_direction_ == Direction::UP) {
        tiles_[row][col] = combined_tile;
        tiles_[row + 1][col] = kEmptyTile;

    } else if (current_direction_ == Direction::RIGHT) {
        tiles_[row][col] = combined_tile;
        tiles_[row][col - 1] = kEmptyTile;

    } else if (current_direction_ == Direction::LEFT) {
        tiles_[row][col] = combined_tile;
        tiles_[row][col + 1] = kEmptyTile;

    } else if (current_direction_ == Direction::DOWN) {
        tiles_[row][col] = combined_tile;
        tiles_[row + 1][col] = kEmptyTile;
    }
}

bool GameEngine::HasFinishedMovingUp() {
    return false;
}


bool GameEngine::HasFinishedMovingRight() {
    return false;
}

bool GameEngine::HasFinishedMovingLeft() {
    return false;
}

bool GameEngine::HasFinishedMovingDown() {
    return false;
}

    bool GameEngine::IsDoneMoving() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (current_direction_ == Direction::LEFT) {
                if (col == 0) {
                    continue;

                } else if (tiles_[row][0].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                    return false;
                }
            }

            if (current_direction_ == Direction::RIGHT) {
                if (col == num_tiles_per_side_ - 1) {
                    continue;

                } else if (tiles_[row][num_tiles_per_side_ - 1].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                    return false;
                }
            }

            if (current_direction_ == Direction::UP) {
                if (tiles_[0][col].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                    return false;
                }
            }

            if (current_direction_ == Direction::DOWN) {
                if (tiles_[num_tiles_per_side_ - 1][col].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                    return false;
                }
            }
        }
    }
}


}
