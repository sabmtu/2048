#include <visualizer/game_2048_app.h>

namespace game_2048 {

Game2048App::Game2048App()
    : game_engine_(glm::vec2(kMargin, kMargin), kBoardDimension,
                   kWindowSize - 2 * kMargin),
      board_display_(glm::vec2(kMargin, kMargin), kBoardDimension,
            kWindowSize - 2 * kMargin) {
    ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void Game2048App::draw() {
    ci::Color8u background_color(230, 230, 220);  // light yellow
    ci::gl::clear(background_color);
    game_engine_.MoveTiles();

    board_display_.Draw();
    board_display_.DrawNumberTiles(game_engine_.GetTiles());
}

/*void Game2048App::update() {
    game_engine_.MoveTiles();
}*/

void Game2048App::keyDown(ci::app::KeyEvent event) {
    switch (event.getCode()) {
        case ci::app::KeyEvent::KEY_LEFT:
            game_engine_.SetCurrentDirection(Direction::LEFT);
            break;
        case ci::app::KeyEvent::KEY_RIGHT:
            game_engine_.SetCurrentDirection(Direction::RIGHT);
            break;
        case ci::app::KeyEvent::KEY_UP:
            game_engine_.SetCurrentDirection(Direction::UP);
            break;
        case ci::app::KeyEvent::KEY_DOWN:
            game_engine_.SetCurrentDirection(Direction::DOWN);
            //game_engine_.MoveTiles(Direction::DOWN);
            break;
    }
}

}
