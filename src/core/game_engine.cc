#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() {

}

GameEngine::GameEngine(size_t num_tiles_per_side)
    : num_tiles_per_side_(num_tiles_per_side) {

    current_direction_ = Direction::STILL;

    //Initialize board of tiles to empty tiles
    for (size_t i = 0; i < num_tiles_per_side_; i++) {
        vector<Tile> test;
        for (size_t j = 0; j < num_tiles_per_side_; j++) {
            test.push_back(kEmptyTile);
        }
        tiles_.push_back(test);
    }

    //Initialize starter tiles
    Tile tile(2, "white");
    tiles_[2][0] = tile;
    tiles_[1][1] = tile;
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
    for (size_t col = 0; col < num_tiles_per_side_; col++) {
        for (size_t row = 0; row < num_tiles_per_side_ - 1; row++) {
            if (tiles_[row][col].IsEmpty()) {

                //Moves tile below to current tile position and sets tile below position to an empty tile
                tiles_[row][col] = tiles_[row + 1][col];
                tiles_[row + 1][col] = kEmptyTile;
            }

            //If the given tile can merge with the tile below and has not already been merged in this turn already
            if (CanMergeTileUp(row, col) && !tiles_[row][col].GetIsBlocked()) {
                MergeTiles(row, col);

                //Sets block to true so tile cannot be merged again on this turn of movement
                tiles_[row][col].SetIsBlocked(true);
            }
        }
    }
}

void GameEngine::MoveTilesRight() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = num_tiles_per_side_ - 1; col >= 1; col--) {
            if (tiles_[row][col].IsEmpty()) {

                //Moves tile to the left to current tile position and sets left tile to an empty tile
                tiles_[row][col] = tiles_[row][col - 1];
                tiles_[row][col - 1] = kEmptyTile;

            }
            if (CanMergeTileRight(row, col) && !tiles_[row][col].GetIsBlocked()) {
                MergeTiles(row, col);
                tiles_[row][col].SetIsBlocked(true);
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

            }
            if (CanMergeTileLeft(row, col) && !tiles_[row][col].GetIsBlocked()) {
                MergeTiles(row, col);
                tiles_[row][col].SetIsBlocked(true);
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
            }

            if (CanMergeTileDown(row, col) && !tiles_[row][col].GetIsBlocked()) {
                MergeTiles(row, col);
                tiles_[row][col].SetIsBlocked(true);
            }

        }
    }
}

bool GameEngine::CanMergeTileUp(size_t row, size_t col) {

    //Checks if given tile position is not empty and the tile below is the same number
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
    Tile combined_tile(2 * tiles_[row][col].GetNumber(), "white");

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
        tiles_[row - 1][col] = kEmptyTile;
    }
}


bool GameEngine::HasFinishedMovingUp() {
    for (size_t row = 1; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {

            //If tiles in first row are empty and tiles below are not, tiles must keep moving up
            if (tiles_[0][col].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                return false;
            }

            //If tiles can still merge on this turn, tiles have not finished moving
            if (CanMergeTileUp(row - 1, col)) {
                if (!tiles_[row][col].GetIsBlocked()) {
                    return false;
                }
            }
        }
    }
    return true;
}


bool GameEngine::HasFinishedMovingRight() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_ - 1; col++) {
            if (tiles_[row][num_tiles_per_side_ - 1].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                return false;
            }

            //If tiles can still merge on this turn, tiles have not finished moving
            if (CanMergeTileRight(row , col + 1)) {
                if (!tiles_[row][col].GetIsBlocked()) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool GameEngine::HasFinishedMovingLeft() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 1; col < num_tiles_per_side_; col++) {
            if (tiles_[row][0].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                return false;
            }

            //If tiles can still merge on this turn, tiles have not finished moving
            if (CanMergeTileLeft(row, col - 1)) {
                if (!tiles_[row][col].GetIsBlocked()) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool GameEngine::HasFinishedMovingDown() {
    for (size_t row = 1; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            if (tiles_[num_tiles_per_side_ - 1][col].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                return false;
            }
            //If tiles can still merge on this turn, tiles have not finished moving
            if (CanMergeTileUp(row - 1, col)) {
                if (!tiles_[row][col].GetIsBlocked()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void GameEngine::EndMovement() {
    if ((current_direction_ == Direction::UP && HasFinishedMovingUp())
        || (current_direction_ == Direction::LEFT && HasFinishedMovingLeft())
        || (current_direction_ == Direction::RIGHT && HasFinishedMovingRight())
        || (current_direction_ == Direction::DOWN && HasFinishedMovingDown())) {
        current_direction_ = Direction::STILL;

        //Add new tile if tiles have finished moving
        FreeTilesForNextMove();
        AddNewTile();
    }
}

void GameEngine::AddNewTile() {
    size_t row;
    size_t col;

    //Randomly generates row and column that are empty on the board
    do {
        row = rand() % num_tiles_per_side_;
        col = rand() % num_tiles_per_side_;
    } while (!tiles_[row][col].IsEmpty());

    Tile new_tile(2, "white");
    tiles_[row][col] = new_tile;
}



void GameEngine::FreeTilesForNextMove() {

    //Sets is_blocked to false for all tiles so they can merge with other tiles
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            tiles_[row][col].SetIsBlocked(false);
        }
    }
}

}
