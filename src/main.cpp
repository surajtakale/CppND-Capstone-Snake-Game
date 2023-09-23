#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "metadata.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  MetaData meta;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  int player_score = game.GetScore();
  int high_score = meta.getHighScore();

  if (player_score <= high_score)
  {
    std::cout << "current high score: " << high_score << "\n";
  }
  else
  {
    std::cout << "Hurray...! New Record !! Congratulations !!" << std::endl;
    meta.setHighScore(player_score);
  }

  return 0;
}