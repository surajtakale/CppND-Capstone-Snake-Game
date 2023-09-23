#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <chrono>
#include <memory>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  bool isSuperFood = false;
  std::shared_ptr<std::chrono::system_clock::time_point> superFoodPlacedOn; // = std::chrono::system_clock::now();


  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlaceSuperFood();
  void Update();
  int calculateSuperFoodScore(const std::shared_ptr<std::chrono::system_clock::time_point>& timestamp);

};

#endif