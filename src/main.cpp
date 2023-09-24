#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "metadata.h"
#include "SDL.h"


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
  const char* title = "Game Over";
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  int player_score = game.GetScore();
  int high_score = meta.getHighScore();
  const char* message = ("Score: " + std::to_string(game.GetScore()) + "\n Size: " + std::to_string(game.GetScore())).c_str();
  if (player_score <= high_score)
  {
    std::cout << "current high score: " << high_score << "\n";
    
    
  }
  else
  {
    std::cout << "Hurray...! New Record !! Congratulations !!" << std::endl;
    title = "Game Over New Record !! Congratulations !!";
    
    meta.setHighScore(player_score);
  }
  renderer.ShowMessage(title, message);

  return 0;
}