#include <catch2/catch.hpp>
#include <core/tile.h>
#include <core/game_engine.h>

using std::vector;
using game_2048::Tile;
using game_2048::GameEngine;

TEST_CASE("Game engine logic") {

    SECTION("Initialize board vector size 2") {
        GameEngine game(2);
        REQUIRE(game.GetTiles().size() == 2);
        REQUIRE(game.GetTiles()[0].size() == 2);
        REQUIRE(game.GetTiles()[1].size() == 2);
    }

    SECTION("Initialize board vector size 3") {
        GameEngine game_2(3);
        REQUIRE(game_2.GetTiles().size() == 3);
        REQUIRE(game_2.GetTiles()[0].size() == 3);
        REQUIRE(game_2.GetTiles()[1].size() == 3);
        REQUIRE(game_2.GetTiles()[2].size() == 3);
    }

    SECTION("Initialize board vector size 6") {
        GameEngine game_3(6);
        REQUIRE(game_3.GetTiles().size() == 6);
        REQUIRE(game_3.GetTiles()[0].size() == 6);
        REQUIRE(game_3.GetTiles()[1].size() == 6);
        REQUIRE(game_3.GetTiles()[2].size() == 6);
        REQUIRE(game_3.GetTiles()[3].size() == 6);
        REQUIRE(game_3.GetTiles()[4].size() == 6);
        REQUIRE(game_3.GetTiles()[5].size() == 6);
    }
}

TEST_CASE("Move Tiles") {
    GameEngine game(2);

    //Check initializes random tiles in board correctly
    size_t num_nonempty_tiles = 0;
    vector<size_t> rows;
    vector<size_t> columns;
    for (size_t row = 0; row < 2; row++) {
        for (size_t col = 0; col < 2; col++) {
            if (!game.GetTiles()[row][col].IsEmpty()) {
                num_nonempty_tiles++;
                rows.push_back(row);
                columns.push_back(col);
            }
        }
    }

    SECTION("Added 2 random nonempty tiles") {
        REQUIRE(game.GetGameState() == GameEngine::GameState::ACTIVE);
        REQUIRE(num_nonempty_tiles == 2);
    }

    SECTION("Move Tiles when direction is still") {
        game.MoveTiles();

        REQUIRE(game.GetTiles()[rows[0]][columns[0]].GetNumber() == 2);
        REQUIRE(game.GetTiles()[rows[1]][columns[1]].GetNumber() == 2);
    }

    SECTION("Move Tiles Down") {
        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();

        //If same column, check tiles merge
        if (columns[0] == columns[1]) {

            //Cannot check empty tiles since new tile is randomly generated
            REQUIRE(game.GetTiles()[rows[1]][columns[1]].GetNumber() == 4);

        } else {
            REQUIRE(game.GetTiles()[1][columns[0]].GetNumber() == 2);
            REQUIRE(game.GetTiles()[1][columns[0]].GetNumber() == 2);
        }
    }

    SECTION("Move Tiles Up") {
        game.SetCurrentDirection(game_2048::Direction::UP);
        game.MoveTiles();
        if (columns[0] == columns[1]) {
            REQUIRE(game.GetTiles()[rows[0]][columns[0]].GetNumber() == 4);

        } else {
            REQUIRE(game.GetTiles()[0][columns[0]].GetNumber() == 2);
            REQUIRE(game.GetTiles()[0][columns[0]].GetNumber() == 2);
        }
    }

    SECTION("Move Tiles Right") {
        game.SetCurrentDirection(game_2048::Direction::RIGHT);
        game.MoveTiles();
        if (rows[0] == rows[1]) {
            REQUIRE(game.GetTiles()[rows[1]][columns[1]].GetNumber() == 4);

        } else {
            REQUIRE(game.GetTiles()[rows[0]][1].GetNumber() == 2);
            REQUIRE(game.GetTiles()[rows[1]][1].GetNumber() == 2);
        }
    }

    SECTION("Move Tiles Left") {
        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();
        if (rows[0] == rows[1]) {
            REQUIRE(game.GetTiles()[rows[0]][columns[0]].GetNumber() == 4);

        } else {
            REQUIRE(game.GetTiles()[rows[0]][0].GetNumber() == 4);
            REQUIRE(game.GetTiles()[rows[1]][0].GetNumber() == 2);
        }
    }
}

TEST_CASE("Add New Tiles Correctly Bigger Board") {
    vector<vector<Tile>> tiles;
    for (size_t row = 0; row < 4; row++) {
        vector<Tile> cols;
        for (size_t col = 0; col < 4; col++) {
            Tile tile(0, "beige");
            cols.push_back(tile);
        }
        tiles.push_back(cols);
    }
    Tile tile2(2, "white");
    tiles[3][0] = tile2;
    tiles[2][1] = tile2;

    GameEngine game(tiles);

    SECTION("Initialize game from vector") {
        REQUIRE(game.GetTiles() == tiles);
        REQUIRE(game.GetNumTilesPerSide() == 4);
    }

    SECTION("Move Tiles Left") {
        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();

        REQUIRE(game.GetTiles()[2][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[3][0].GetNumber() == 2);
    }

    SECTION("Add new tile correctly") {
        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();

        REQUIRE(game.GetTiles()[2][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[3][0].GetNumber() == 2);

        size_t num_nonempty_tiles = 0;
        size_t empty_tiles = 0;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                if (!game.GetTiles()[row][col].IsEmpty()) {
                    num_nonempty_tiles++;

                } else {
                    empty_tiles++;
                }
            }
        }
        REQUIRE(empty_tiles == 13);
        REQUIRE(num_nonempty_tiles == 3);
    }
}

TEST_CASE("Check adding tiles conditions") {
    vector<vector<Tile>> tiles;
    for (size_t row = 0; row < 2; row++) {
        vector<Tile> cols;
        for (size_t col = 0; col < 2; col++) {
            Tile tile(0, "beige");
            cols.push_back(tile);
        }
        tiles.push_back(cols);
    }
    Tile tile2(2, "white");

    SECTION("Check will not add tiles if finished moving up") {
        tiles[0][0] = tile2;
        tiles[0][1] = tile2;
        GameEngine game(tiles);

        //Check tiles won't move since already moved to top and won't add new tiles
        game.SetCurrentDirection(game_2048::Direction::UP);
        game.MoveTiles();
        game.MoveTiles();

        REQUIRE(game.GetTiles()[0][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[0][1].GetNumber() == 2);
        REQUIRE(game.GetTiles()[1][0].GetNumber() == 0);
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 0);
    }

    SECTION("Check will not add tiles if finished moving down") {
        tiles[1][0] = tile2;
        tiles[1][1] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();
        game.MoveTiles();

        REQUIRE(game.GetTiles()[0][0].GetNumber() == 0);
        REQUIRE(game.GetTiles()[0][1].GetNumber() == 0);
        REQUIRE(game.GetTiles()[1][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 2);
    }

    SECTION("Check will not add tiles if finished moving left") {
        tiles[0][0] = tile2;
        tiles[1][0] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();
        game.MoveTiles();

        REQUIRE(game.GetTiles()[0][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[0][1].GetNumber() == 0);
        REQUIRE(game.GetTiles()[1][0].GetNumber() == 2);
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 0);
    }

    SECTION("Check will not add tiles if finished moving right") {
        tiles[0][1] = tile2;
        tiles[1][1] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::RIGHT);
        game.MoveTiles();
        game.MoveTiles();

        REQUIRE(game.GetTiles()[0][0].GetNumber() == 0);
        REQUIRE(game.GetTiles()[0][1].GetNumber() == 2);
        REQUIRE(game.GetTiles()[1][0].GetNumber() == 0);
        REQUIRE(game.GetTiles()[1][1].GetNumber() == 2);
    }
}

TEST_CASE("Merge in different directions") {
    vector<vector<Tile>> tiles;
    for (size_t row = 0; row < 4; row++) {
        vector<Tile> cols;
        for (size_t col = 0; col < 4; col++) {
            Tile tile(0, "beige");
            cols.push_back(tile);
        }
        tiles.push_back(cols);
    }
    Tile tile2(2, "white");

    SECTION("Merge tiles Down correctly") {
        tiles[3][0] = tile2;
        tiles[2][1] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();
        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();
        game.MoveTiles();
        game.MoveTiles();

        REQUIRE(game.GetTiles()[3][0].GetNumber() == 4);

        size_t num_nonempty_tiles = 0;
        size_t empty_tiles = 0;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                if (!game.GetTiles()[row][col].IsEmpty()) {
                    num_nonempty_tiles++;

                } else {
                    empty_tiles++;
                }
            }
        }
        REQUIRE(empty_tiles == 13);
        REQUIRE(num_nonempty_tiles == 3);
    }

    SECTION("Merge Tiles Up") {
        tiles[0][0] = tile2;
        tiles[1][0] = tile2;
        GameEngine game_1(tiles);

        game_1.SetCurrentDirection(game_2048::Direction::UP);
        game_1.MoveTiles();
        REQUIRE(game_1.GetTiles()[0][0].GetNumber() == 4);

        size_t num_nonempty_tiles = 0;
        size_t empty_tiles = 0;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                if (!game_1.GetTiles()[row][col].IsEmpty()) {
                    num_nonempty_tiles++;

                } else {
                    empty_tiles++;
                }
            }
        }
        REQUIRE(empty_tiles == 14);
        REQUIRE(num_nonempty_tiles == 2);
    }

    SECTION("Merge Tiles Left") {
        tiles[2][0] = tile2;
        tiles[2][2] = tile2;
        GameEngine game_2(tiles);

        game_2.SetCurrentDirection(game_2048::Direction::LEFT);
        game_2.MoveTiles();
        game_2.MoveTiles();
        REQUIRE(game_2.GetTiles()[2][0].GetNumber() == 4);

        size_t num_nonempty_tiles = 0;
        size_t empty_tiles = 0;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                if (!game_2.GetTiles()[row][col].IsEmpty()) {
                    num_nonempty_tiles++;

                } else {
                    empty_tiles++;
                }
            }
        }
        REQUIRE(empty_tiles == 14);
        REQUIRE(num_nonempty_tiles == 2);
    }

    SECTION("Merge Tiles Right") {
        tiles[1][2] = tile2;
        tiles[1][1] = tile2;
        GameEngine game_3(tiles);

        game_3.SetCurrentDirection(game_2048::Direction::RIGHT);
        game_3.MoveTiles();
        game_3.MoveTiles();
        REQUIRE(game_3.GetTiles()[1][3].GetNumber() == 4);

        size_t num_nonempty_tiles = 0;
        size_t empty_tiles = 0;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                if (!game_3.GetTiles()[row][col].IsEmpty()) {
                    num_nonempty_tiles++;

                } else {
                    empty_tiles++;
                }
            }
        }
        REQUIRE(empty_tiles == 14);
        REQUIRE(num_nonempty_tiles == 2);
    }

    SECTION("Check merging adds to score") {
        tiles[3][0] = tile2;
        tiles[2][0] = tile2;
        GameEngine game(tiles);

        REQUIRE(game.GetScore() == 0);

        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();
        game.MoveTiles();

        REQUIRE(game.GetTiles()[3][0].GetNumber() == 4);
        REQUIRE(game.GetScore() == 4);
    }

    SECTION("Check score from merging multiple bigger numbers") {
        Tile tile4(4, "white");
        Tile tile8(8, "orange");
        tiles[2][0] = tile4;
        tiles[2][1] = tile4;
        tiles[3][0] = tile8;
        tiles[3][1] = tile8;
        GameEngine game(tiles);

        REQUIRE(game.GetScore() == 0);

        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();
        game.MoveTiles();

        REQUIRE(game.GetTiles()[2][0].GetNumber() == 8);
        REQUIRE(game.GetTiles()[3][0].GetNumber() == 16);
        REQUIRE(game.GetScore() == 24);
    }
}

TEST_CASE("Merge Tiles Twice Bigger Board") {
    vector<vector<Tile>> tiles;

    //Initialize 4x4 board of empty tiles
    for (size_t row = 0; row < 4; row++) {
        vector<Tile> cols;
        for (size_t col = 0; col < 4; col++) {
            Tile tile(0, "beige");
            cols.push_back(tile);
        }
        tiles.push_back(cols);
    }
    Tile tile2(2, "white");
    Tile tile4(4, "white");
    Tile tile8(8, "white");

    SECTION("Check will not merge same tile right twice") {
        tiles[2][0] = tile2;
        tiles[2][1] = tile2;
        tiles[2][2] = tile2;
        tiles[2][3] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::RIGHT);
        game.MoveTiles();
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][3].GetNumber() == 4);

        //Check calling MoveTiles again won't move tiles since they have already been merged
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][3].GetNumber() == 4);
    }

    SECTION("Check will not merge same tile left twice") {
        tiles[2][0] = tile2;
        tiles[2][1] = tile2;
        tiles[2][2] = tile2;
        tiles[2][3] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][0].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 4);

        //Check calling MoveTiles again won't move tiles since they have already been merged
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][0].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 4);
    }

    SECTION("Check will not merge same tile up twice") {
        tiles[0][2] = tile2;
        tiles[1][2] = tile2;
        tiles[2][2] = tile2;
        tiles[3][2] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::UP);
        game.MoveTiles();
        game.MoveTiles();
        REQUIRE(game.GetTiles()[0][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[1][2].GetNumber() == 4);

        //Check calling MoveTiles again won't move tiles since they have already been merged
        game.MoveTiles();
        REQUIRE(game.GetTiles()[0][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[1][2].GetNumber() == 4);
    }

    SECTION("Check will not merge same tile down twice") {
        tiles[0][2] = tile2;
        tiles[1][2] = tile2;
        tiles[2][2] = tile2;
        tiles[3][2] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();
        game.MoveTiles();
        REQUIRE(game.GetTiles()[3][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);

        //Check calling MoveTiles again won't move tiles since they have already been merged
        game.MoveTiles();
        REQUIRE(game.GetTiles()[3][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);
    }

    SECTION("Check will not merge right if has already been merged in one move") {
        tiles[2][0] = tile2;
        tiles[2][1] = tile2;
        tiles[2][2] = tile4;
        tiles[2][3] = tile8;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::RIGHT);
        game.MoveTiles();
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][3].GetNumber() == 8);

        //Check calling MoveTiles again won't merge the 4's since one of the 4's was just merged in one turn
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][3].GetNumber() == 8);
    }

    SECTION("Check will not merge left if has already been merged in one move") {
        tiles[2][0] = tile2;
        tiles[2][1] = tile2;
        tiles[2][2] = tile4;
        tiles[2][3] = tile8;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][0].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 8);

        //Check calling MoveTiles again won't merge the 4's since one of the 4's was just merged in one turn
        game.MoveTiles();
        REQUIRE(game.GetTiles()[2][0].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][1].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 8);
    }

    SECTION("Check will not merge up if has already been merged in one move") {
        tiles[0][2] = tile8;
        tiles[1][2] = tile4;
        tiles[2][2] = tile2;
        tiles[3][2] = tile2;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::UP);
        game.MoveTiles();
        game.MoveTiles();
        REQUIRE(game.GetTiles()[0][2].GetNumber() == 8);
        REQUIRE(game.GetTiles()[1][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);

        //Check calling MoveTiles again won't merge the 4's since one of the 4's was just merged in one turn
        game.MoveTiles();
        REQUIRE(game.GetTiles()[0][2].GetNumber() == 8);
        REQUIRE(game.GetTiles()[1][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);
    }

    SECTION("Check will not merge down if has already been merged in one move") {
        tiles[0][2] = tile2;
        tiles[1][2] = tile2;
        tiles[2][2] = tile4;
        tiles[3][2] = tile8;
        GameEngine game(tiles);

        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();
        game.MoveTiles();
        REQUIRE(game.GetTiles()[1][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[3][2].GetNumber() == 8);

        //Check calling MoveTiles again won't merge the 4's since one of the 4's was just merged in one turn
        game.MoveTiles();
        REQUIRE(game.GetTiles()[1][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[2][2].GetNumber() == 4);
        REQUIRE(game.GetTiles()[3][2].GetNumber() == 8);
    }

}

TEST_CASE("Check win and lose") {
    vector<vector<Tile>> tiles;
    for (size_t row = 0; row < 2; row++) {
        vector<Tile> cols;
        for (size_t col = 0; col < 2; col++) {
            Tile tile(0, "beige");
            cols.push_back(tile);
        }
        tiles.push_back(cols);
    }
    Tile tile(1024, "yellow");
    tiles[0][0] = tile;
    tiles[0][1] = tile;

    GameEngine game(tiles);

    SECTION("Game is active") {
        REQUIRE(game.GetGameState() == GameEngine::GameState::ACTIVE);

        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();

        REQUIRE(game.GetGameState() == GameEngine::GameState::ACTIVE);
    }

    SECTION("Player wins") {
        game.SetCurrentDirection(game_2048::Direction::LEFT);
        game.MoveTiles();

        REQUIRE(game.GetTiles()[0][0].GetNumber() == 2048);
        REQUIRE(game.GetGameState() == GameEngine::GameState::WON);
    }

    SECTION("Player lost") {
        REQUIRE(game.GetGameState() == GameEngine::GameState::ACTIVE);

        game.SetCurrentDirection(game_2048::Direction::DOWN);
        game.MoveTiles();
        game.SetCurrentDirection(game_2048::Direction::UP);
        game.MoveTiles();

        size_t num_nonempty_tiles = 0;
        size_t empty_tiles = 0;
        for (size_t row = 0; row < 2; row++) {
            for (size_t col = 0; col < 2; col++) {
                if (!game.GetTiles()[row][col].IsEmpty()) {
                    num_nonempty_tiles++;

                } else {
                    empty_tiles++;
                }
            }
        }
        REQUIRE(game.GetGameState() == GameEngine::GameState::LOST);
        REQUIRE(empty_tiles == 0);
        REQUIRE(num_nonempty_tiles == 4);
    }
}