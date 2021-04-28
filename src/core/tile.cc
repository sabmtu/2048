#include <core/tile.h>

namespace game_2048 {

Tile::Tile() { }

Tile::Tile(size_t num, ci::Color color) {
    number_ = num;
    color_ = color;
    is_blocked_ = false;
}

const ci::Color &Tile::GetColor() const {
    return color_;
}

size_t Tile::GetNumber() const {
    return number_;
}

bool Tile::operator==(const Tile &tile) const {
    if (number_ != tile.GetNumber() || color_ != tile.GetColor()) {
        return false;
    }
    return true;
}

bool Tile::IsEmpty() const{
    return number_ == 0;
}

void Tile::SetIsBlocked(bool set) {
    is_blocked_ = set;
}

bool Tile::GetIsBlocked() const {
    return is_blocked_;
}


}