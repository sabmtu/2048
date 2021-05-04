#include <visualizer/game_2048_app.h>

namespace game_2048 {

Game2048App::Game2048App()
    : game_engine_(kBoardDimension),
      board_display_(glm::vec2(kMargin, 1.1* kMargin), kBoardDimension,
            kWindowSize - 2 * kMargin),
      win_loss_message_(glm::vec2(kMargin, 1.1* kMargin), kWindowSize - 2 * kMargin) {
    ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void Game2048App::draw() {
    ci::Color8u background_color(230, 230, 220);  // light yellow
    ci::gl::clear(background_color);
    ci::gl::drawString("2048", glm::vec2(kMargin, 0.25 * kMargin),
                               ci::Color("gray"), ci::Font("Times New roman", 70));
    ci::gl::drawString("Join the tiles, get to 2048!", glm::vec2(kMargin, 0.75 * kMargin),
                               ci::Color("gray"), ci::Font("Times New roman", 20));

    board_display_.Draw();
    board_display_.DrawNumberTiles(game_engine_.GetTiles());

    if (game_engine_.GetGameState() != GameEngine::GameState::ACTIVE) {
        win_loss_message_.FindStateOfGame(game_engine_.GetGameState());
        win_loss_message_.Draw();
    }

}

void Game2048App::update() {
    if (game_engine_.GetGameState() == GameEngine::GameState::ACTIVE) {
        game_engine_.MoveTiles();
    }
}

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
            break;
    }
}

}
