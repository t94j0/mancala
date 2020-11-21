#include <iostream>
#include <optional>
#include <vector>

#include "game.hpp"

class Node {
public:
  Node(Node *parent, std::vector<int> move_path)
      : parent(nullptr), move_path(move_path) {}

private:
  Node *parent;

  std::vector<int> move_path;
  unsigned int wins = 0;
  unsigned int losses = 0;
};

auto main() -> int { std::vector<int> parent = {}; }

// auto main() -> int {
//   auto game = Game({4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0});
//   // auto game = Game();
//   game.print_board();
//   int idx;
//   while (!game.finished()) {
//     std::cout << "Vaid Moves: ";
//     for (auto i : game.get_valid_moves())
//       std::cout << i << " ";
//     std::cout << std::endl;
//     std::cin >> idx;
//     game.loop(idx);
//     game.print_board();
//   }
//   auto winner = game.winner() == Left ? "Left" : "Right";
//   std::cout << winner << " Won" << std::endl;
// }
