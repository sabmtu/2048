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

    //Setup basic display for color, title, and score for game
    ci::Color8u background_color(230, 230, 220);  // light yellow
    ci::gl::clear(background_color);
    DrawTitles();
    DrawScore();

    //Draw board and tiles
    board_display_.Draw();
    board_display_.DrawNumberTiles(game_engine_.GetTiles());

    //Show win or loss message if player reaches 2048 or fills board with no more possible moves
    if (game_engine_.GetGameState() != GameEngine::GameState::ACTIVE) {
        win_loss_message_.FindStateOfGame(game_engine_.GetGameState());
        win_loss_message_.Draw();
    }

}

void Game2048App::update() {

    //Stop updating if player wins or loses
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

void Game2048App::DrawTitles() {

    //Label game titles
    ci::gl::drawString("2048", glm::vec2(kMargin, kSmallerMargin),kOutlineColor,
                       ci::Font("Times New roman", 70));
    ci::gl::drawString("Join the tiles, get to 2048!", glm::vec2(kMargin, 0.75 * kMargin),
                       kOutlineColor, ci::Font("Times New roman", 20));
}

void Game2048App::DrawScore() {

    //Creates and draws rectangle above board to display score
    double score_box_length = 0.4 * kMargin;
    glm::vec2 top_left = glm::vec2(kWindowSize - 2 * kMargin, kSmallerMargin);
    glm::vec2 bottom_right = glm::vec2(kWindowSize - kMargin, kSmallerMargin + score_box_length);

    ci::Rectf score_outline(top_left, bottom_right);
    ci::gl::color(kOutlineColor);
    ci::gl::drawSolidRect(score_outline);

    //Draws score label in top of box that was just drawn
    size_t center_of_box = (top_left.x + bottom_right.x) / 2;
    ci::gl::drawStringCentered("SCORE", glm::vec2(center_of_box,top_left.y + (0.2 * score_box_length)), "white",
                               ci::Font("Times New roman", 20));
    //Displays current game score within score box
    ci::gl::drawStringCentered(std::to_string(game_engine_.GetScore()),
                               glm::vec2(center_of_box,top_left.y + (0.6 * score_box_length)), "white",
                               ci::Font("Times New roman", 20));
}

}
