#include <core/tile.h>

namespace game_2048 {

Tile::Tile() { }

Tile::Tile(glm::vec2 position, size_t num, ci::Color color) {
    position_ = position;
    //velocity_ = velocity;
    number_ = num;
    color_ = color;
}

const ci::Color &Tile::GetColor() const {
    return color_;
}

size_t Tile::GetNumber() const {
    return number_;
}

void Tile::MoveRight() {
    position_.x += kMoveSpeed;
}

void Tile::MoveLeft() {
    position_.x -= kMoveSpeed;
}

void Tile::MoveUp() {
    position_.y -= kMoveSpeed;
}

void Tile::MoveDown() {
    position_.y += kMoveSpeed;
}




}