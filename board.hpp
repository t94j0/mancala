#ifndef BOARD
#define BOARD

#include "hole.hpp"
#include <iostream>
#include <variant>
#include <vector>

class Board {
public:
  Board()
      : board(board_size), left_player_mancala(board[(board_size / 2) - 1]),
        right_player_mancala(board[board_size - 1]) {
    left_player_mancala.remove_stones();
    right_player_mancala.remove_stones();
  }
  Board(const std::vector<Hole> &b)
      : board_size(b.size()), board(b),
        left_player_mancala(board[(board_size / 2) - 1]),
        right_player_mancala(board[board_size - 1]) {}

  auto take_turn(const Player player, const int index)
      -> std::variant<bool, std::string>;
  auto get_valid_moves(const Player) -> std::vector<int>;
  auto score(const Player) const -> unsigned short int;
  auto game_over() const -> bool;
  friend auto operator<<(std::ostream &os, const Board &) -> std::ostream &;

private:
  int board_size = 14;
  std::vector<Hole> board;
  Hole &left_player_mancala;
  Hole &right_player_mancala;

  auto is_idx_out_of_range(const int) const -> bool;
  auto is_idx_mancala(Hole &) const -> bool;
  auto is_target_mancala(const Player, Hole &) const -> bool;
  auto is_target_other_mancala(const Player, Hole &) const -> bool;
  auto is_players_piece(Player, const int) const -> bool;
  auto get_opposite_hole(const int) -> Hole &;
  auto move_stones(const Player, const int, int) -> int;
};

auto Board::score(const Player player) const -> unsigned short int {
  return player == Left ? left_player_mancala.get_stones()
                        : right_player_mancala.get_stones();
}
auto Board::game_over() const -> bool {
  for (auto &i : board) {
    if (&i == &left_player_mancala || &i == &right_player_mancala)
      continue;
    if (i.get_stones() > 0)
      return false;
  }
  return true;
}

auto Board::get_valid_moves(const Player player) -> std::vector<int> {
  std::vector<int> v;
  for (int i = 0; i < board.size(); i++) {
    auto &target = board.at(i);
    if (!is_players_piece(player, i))
      continue;
    if (is_idx_mancala(target)) {
      continue;
    }
    if (target.get_stones() == 0)
      continue;
    v.push_back(i);
  }
  return v;
}

auto Board::get_opposite_hole(const int idx) -> Hole & {
  auto opposite_hole_idx = (board_size - 2) - idx;
  return board.at(opposite_hole_idx);
}

auto Board::is_players_piece(const Player player, const int idx) const -> bool {
  if (player == Left && (idx >= 0 && idx < board_size / 2))
    return true;
  if (player == Right && (idx >= board_size / 2))
    return true;
  return false;
}

auto Board::is_idx_out_of_range(const int idx) const -> bool {
  return idx > board.size();
}

auto Board::is_idx_mancala(Hole &chosen_hole) const -> bool {
  return (&chosen_hole == &left_player_mancala ||
          &chosen_hole == &right_player_mancala);
}

auto Board::is_target_other_mancala(Player player, Hole &hole) const -> bool {
  if (player == Left && &hole == &right_player_mancala)
    return true;
  if (player == Right && &hole == &left_player_mancala)
    return true;
  return false;
}

auto Board::is_target_mancala(Player player, Hole &last_hole) const -> bool {
  if (player == Left && &last_hole == &left_player_mancala)
    return true;
  if (player == Right && &last_hole == &right_player_mancala)
    return true;
  return false;
}

auto Board::move_stones(const Player player, const int idx, int num_stones)
    -> int {
  auto target_hole_idx = -1;

  for (int i = 1; i < num_stones + 1; i++) {
    target_hole_idx = (idx + i) % board_size;
    auto &target_hole = board.at(target_hole_idx);
    if (is_target_other_mancala(player, target_hole)) {
      num_stones++;
      continue;
    }
    target_hole.add_stone();
  }

  return target_hole_idx;
}

// the std::string is the error message and bool represents if the player sh
// ould go again
auto Board::take_turn(const Player player, const int idx)
    -> std::variant<bool, std::string> {
  auto moves = get_valid_moves(player);
  if (std::find(std::cbegin(moves), std::cend(moves), idx) ==
      std::cend(moves)) {
    return "Illegal move";
  }

  auto &chosen_hole = board.at(idx);
  auto num_stones = chosen_hole.get_stones();
  chosen_hole.remove_stones();

  auto target_hole_idx = move_stones(player, idx, num_stones);
  auto &last_hole = board.at(target_hole_idx);

  if (num_stones == 0)
    return "Hole is empty";

  if (!is_idx_mancala(last_hole)) {
    auto &opposite_hole = get_opposite_hole(target_hole_idx);

    if (last_hole.get_stones() == 1 &&
        is_players_piece(player, target_hole_idx)) {
      auto new_stones = opposite_hole.get_stones() + last_hole.get_stones();
      last_hole.remove_stones();
      opposite_hole.remove_stones();
      if (player == Left)
        left_player_mancala.add_stones(new_stones);
      if (player == Right)
        right_player_mancala.add_stones(new_stones);
    }
  }

  return is_target_mancala(player, last_hole);
}

auto operator<<(std::ostream &os, const Board &b) -> std::ostream & {
  for (int i = (b.board.size() / 2) - 1; i >= 0; i--) {
    os << b.board[i].get_stones() << " ";
  }
  os << std::endl << "  ";
  for (int i = (b.board.size() / 2); i < b.board.size(); i++) {
    os << b.board[i].get_stones() << " ";
  }
  return os;
}

#endif
