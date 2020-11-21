#ifndef HOLE
#define HOLE

enum Player { Left, Right };

class Hole {
public:
  Hole() = default;
  Hole(unsigned short int stones) : stones(stones) {}

  auto add_stone() -> void;
  auto add_stones(unsigned short int) -> void;
  auto remove_stones() -> void;
  auto get_stones() const -> unsigned short int;

private:
  unsigned short int stones = 4;
};

auto Hole::add_stone() -> void { this->stones++; }
auto Hole::add_stones(unsigned short int i) -> void { this->stones += i; }
auto Hole::remove_stones() -> void { this->stones = 0; }
auto Hole::get_stones() const -> unsigned short int { return this->stones; };

#endif
