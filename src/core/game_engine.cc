#include <core/game_engine.h>

namespace game_2048 {

GameEngine::GameEngine() { }

GameEngine::GameEngine(size_t num_tiles_per_side)
    : num_tiles_per_side_(num_tiles_per_side) {
    score_ = 0;
    current_direction_ = Direction::STILL;
    game_state_ = ACTIVE;

    //Initialize board of tiles to empty tiles
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        vector<Tile> cols;
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            cols.push_back(kEmptyTile);
        }
        tiles_.push_back(cols);
    }

    //Initialize starter tiles
    AddNewTile();
    AddNewTile();
}

GameEngine::GameEngine(const vector<vector<Tile>> &tiles) {
    game_state_ = ACTIVE;
    score_ = 0;
    num_tiles_per_side_ = tiles.size();
    tiles_ = tiles;
}

const vector<vector<Tile>> &GameEngine::GetTiles() {
    return tiles_;
}

const size_t GameEngine::GetNumTilesPerSide() {
    return num_tiles_per_side_;
}

const GameEngine::GameState &GameEngine::GetGameState() {
    return game_state_;
}

const size_t GameEngine::GetScore() {
    return score_;
}

void GameEngine::SetCurrentDirection(const Direction& direction) {
    current_direction_ = direction;
}

void GameEngine::MoveTiles() {
    CheckFinishMoving();

    //Do nothing if all possible tile movements in given direction are already done
    if (HasFinishedMovingInDirection()) {
        current_direction_ = Direction::STILL;
        return;
    }

    //Moves tiles in given direction
    switch (current_direction_) {
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
    //If tiles finished moving in given direction, frees already merged tiles and randomly adds new tile to board
    EndMovement();
}


void GameEngine::MoveTilesUp() {
    for (size_t col = 0; col < num_tiles_per_side_; col++) {
        for (size_t row = 0; row < num_tiles_per_side_ - 1; row++) {
            if (tiles_[row][col].IsEmpty()) {

                //Moves tile below to current tile position and sets tile below position to an empty tile
                tiles_[row][col] = tiles_[row + 1][col];
                tiles_[row + 1][col] = kEmptyTile;

                //If the given tile can merge with the tile below and has not already been merged in this turn already
            } else if (CanMergeTileUp(row, col) && !tiles_[row][col].GetIsBlocked()) {
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

            } else if (CanMergeTileRight(row, col) && !tiles_[row][col].GetIsBlocked()) {
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

            } else if (CanMergeTileLeft(row, col) && !tiles_[row][col].GetIsBlocked()) {
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

            } else if (CanMergeTileDown(row, col) && !tiles_[row][col].GetIsBlocked()) {
                MergeTiles(row, col);
                tiles_[row][col].SetIsBlocked(true);
            }

        }
    }
}

bool GameEngine::CanMergeTileUp(size_t row, size_t col) {

    //Checks if given tile position is not empty and the tile below is the same number
    return ((!tiles_[row][col].IsEmpty() && !tiles_[row + 1][col].GetIsBlocked())
        && (tiles_[row + 1][col].GetNumber() == tiles_[row][col].GetNumber()));
}

bool GameEngine::CanMergeTileRight(size_t row, size_t col) {
    return ((!tiles_[row][col].IsEmpty() && !tiles_[row][col - 1].GetIsBlocked())
        && (tiles_[row][col - 1].GetNumber() == tiles_[row][col].GetNumber()));
}

bool GameEngine::CanMergeTileLeft(size_t row, size_t col) {
    return ((!tiles_[row][col].IsEmpty() && !tiles_[row][col + 1].GetIsBlocked())
        && (tiles_[row][col + 1].GetNumber() == tiles_[row][col].GetNumber()));
}

bool GameEngine::CanMergeTileDown(size_t row, size_t col) {
    return ((!tiles_[row][col].IsEmpty() && !tiles_[row - 1][col].GetIsBlocked())
    && (tiles_[row - 1][col].GetNumber() == tiles_[row][col].GetNumber()));
}

void GameEngine::MergeTiles(size_t row, size_t col) {
    Tile combined_tile = MakeMergedTile(row, col);

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

Tile GameEngine::MakeMergedTile(size_t row, size_t col) {
    size_t merged_number = 2 * tiles_[row][col].GetNumber();
    score_ += merged_number;

    //Check if new tile merged will cause player to win
    if (merged_number == 2048) {
        game_state_ = WON;
    }

    //Gets corresponding color for new merged tile from map of each number with its given color
    ci::Color color;
    auto it = kTileColors.find(merged_number);
    if (it != kTileColors.end()) {
        color = it->second;

    } else {
        //If number not in map, color it black
        color = ci::Color8u(14, 14, 0);
    }
    //Creates and returns new tile object with new merged tile number and color
    Tile combined_tile(merged_number, color);
    return combined_tile;
}

bool GameEngine::HasFinishedMovingUp() {
    for (size_t col = 0; col < num_tiles_per_side_; col++) {
        for (size_t row = 0; row < num_tiles_per_side_ - 1; row++) {

            //If tiles in first row are empty and tiles below are not, tiles must keep moving up
            if (tiles_[row][col].IsEmpty() && !tiles_[row + 1][col].IsEmpty()) {
                return false;
            }

            //If tiles can still merge on this turn, tiles have not finished moving
            if (CanMergeTileUp(row, col)) {
                if (!tiles_[row][col].GetIsBlocked() && !tiles_[row + 1][col].GetIsBlocked()) {
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
            if (tiles_[row][col + 1].IsEmpty() && !tiles_[row][col].IsEmpty()) {
                return false;
            }

            //If tiles can still merge on this turn, tiles have not finished moving
            if (CanMergeTileRight(row , col + 1)) {
                if (!tiles_[row][col].GetIsBlocked() && !tiles_[row][col + 1].GetIsBlocked()) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool GameEngine::HasFinishedMovingLeft() {
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_ - 1; col++) {
            if (tiles_[row][col].IsEmpty() && !tiles_[row][col + 1].IsEmpty()) {
                return false;
            }

            //If tiles can still merge on this turn, tiles have not finished moving
            if (CanMergeTileLeft(row, col)) {
                if (!tiles_[row][col].GetIsBlocked() && !tiles_[row][col + 1].GetIsBlocked()) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool GameEngine::HasFinishedMovingDown() {
    for (size_t col = 0; col < num_tiles_per_side_; col++) {
        for (size_t row = 1; row < num_tiles_per_side_; row++) {
            if (tiles_[row][col].IsEmpty() && !tiles_[row - 1][col].IsEmpty()) {
                return false;
            }
            //If tiles can still merge on this turn, tiles have not finished moving
            if (CanMergeTileDown(row, col)) {
                if (!tiles_[row][col].GetIsBlocked() && !tiles_[row - 1][col].GetIsBlocked()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void GameEngine::EndMovement() {
    CheckFinishMoving();

    if (HasFinishedMovingInDirection()) {
        current_direction_ = Direction::STILL;

        //Add new tile if tiles have finished moving
        FreeTilesForNextMove();
        AddNewTile();

        CheckFinishMoving();
        if ((is_done_moving_up_ && is_done_moving_right_) && (is_done_moving_left_ && is_done_moving_down_)) {
            game_state_ = LOST;
            return;
        }
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

    //Randomly generate number between 1 and 10 for 1/10 chance new tile is number 4, otherwise new tile is number 2
    size_t num = rand() % 10 + 1;
    Tile new_tile;
    if (num == 1) {
        new_tile = kStartTile4;

    } else {
        new_tile = kStartTile2;
    }

    tiles_[row][col] = new_tile;
}

void GameEngine::FreeTilesForNextMove() {

    //Sets is_blocked to false for all tiles so they can merge with other tiles
    for (size_t row = 0; row < num_tiles_per_side_; row++) {
        for (size_t col = 0; col < num_tiles_per_side_; col++) {
            tiles_[row][col].SetIsBlocked(false);
        }
    }
    //Resets so board is free to move for next movement
    is_done_moving_up_ = false;
    is_done_moving_left_ = false;
    is_done_moving_right_ = false;
    is_done_moving_down_ = false;
}

void GameEngine::CheckFinishMoving() {

    //Set bool values for if possible moves in one turn have finished in each direction
    is_done_moving_up_ = HasFinishedMovingUp();
    is_done_moving_down_ = HasFinishedMovingDown();
    is_done_moving_left_ = HasFinishedMovingLeft();
    is_done_moving_right_ = HasFinishedMovingRight();
}

bool GameEngine::HasFinishedMovingInDirection() {

    //Checks if tiles have finished moving in corresponding given direction
    return ((current_direction_ == Direction::UP && is_done_moving_up_)
            || (current_direction_ == Direction::LEFT && is_done_moving_left_)
            || (current_direction_ == Direction::RIGHT && is_done_moving_right_)
            || (current_direction_ == Direction::DOWN && is_done_moving_down_));
}

}
