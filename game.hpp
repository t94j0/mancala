#ifndef GAME
#define GAME

#include "board.hpp"
#include <vector>

class Game {
public:
  Game() = default;
  Game(const std::vector<Hole> &v) : board(v) {}
  auto loop(const int idx) -> void;
  auto print_board() const -> void;
  auto get_valid_moves() -> std::vector<int>;
  auto get_current_player() const -> std::string;
  auto finished() const -> bool;
  auto winner() const -> Player;

private:
  Board board;
  Player current_player = Left;
  auto switch_current_player() -> void;
  auto next_player_blocked() -> bool;
};

auto Game::next_player_blocked() -> bool {
  auto next_player = current_player == Left ? Right : Left;
  return board.get_valid_moves(next_player).size() == 0;
}

auto Game::finished() const -> bool { return board.game_over(); }

auto Game::winner() const -> Player {
  auto left_score = board.score(Left);
  auto right_score = board.score(Right);
  return left_score > right_score ? Left : Right;
}

auto Game::get_valid_moves() -> std::vector<int> {
  return board.get_valid_moves(current_player);
}

auto Game::loop(const int idx) -> void {
  auto output = board.take_turn(current_player, idx);
  if (std::holds_alternative<std::string>(output)) {
    auto error = std::get<std::string>(output);
    std::cout << error << std::endl;
  }
  auto go_again = std::get<bool>(output);
  if (!go_again && !next_player_blocked())
    switch_current_player();
}

auto Game::get_current_player() const -> std::string {
  return current_player == Left ? "Left" : "Right";
}

auto Game::print_board() const -> void { std::cout << board << std::endl; }

auto Game::switch_current_player() -> void {
  current_player = current_player == Left ? Right : Left;
}

#endif
