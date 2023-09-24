#include "game.h"
#include <iostream>
#include "SDL.h"
#include <chrono>
#include "controller.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, *this);
    Update(&renderer);
    renderer.Render(snake, food, isSuperFood);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      isSuperFood = false;
      return;
    }
  }
}

void Game::PlaceSuperFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      isSuperFood = true;
      superFoodPlacedOn = std::make_shared<std::chrono::system_clock::time_point>(
        std::chrono::system_clock::now()
    );
      return;
    }
  }
}

void Game::Update(Renderer *renderer) {
  if(isGamePaused){
    (*renderer).setGamePausedTitle();
    return;
  }
  bool isSlowingSpeed = false;

  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    if (isSuperFood){
      
      std::cout << "You Ate A Super Food ";// << std::endl;

      // score = score + 2;
      auto new_score = calculateSuperFoodScore(superFoodPlacedOn);
      if(new_score > 3){
        std::cout << "High Score achived in super food so reducing score..!" << std::endl;
        std::thread affectSpeed(TimerThread, &snake, (snake.speed + 0.02));
        snake.speed = 0.02;
        isSlowingSpeed = true;
        affectSpeed.detach();
      }
      score = score + new_score;
    }else{
      std::cout << "food is normal food" << std::endl;
      score = score + 1;
    }
    
    if(score != 0 && score % 5 == 0){
      std::cout << "now placing food is super food" << std::endl;
      PlaceSuperFood();
    }
    else{
      std::cout << "now placing food is Normal food" << std::endl;
      isSuperFood = false;
      PlaceFood();
    }
    
    // Grow snake and increase speed.
    snake.GrowBody();
    if(!isSlowingSpeed){
      snake.speed += 0.02;
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

int Game::calculateSuperFoodScore(const std::shared_ptr<std::chrono::system_clock::time_point>& timestamp) {
    if (!timestamp) {
        std::cout << "Error: Invalid timestamp pointer." << std::endl;
        return 0; // Return a zero value to indicate an error.
    }

    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    std::chrono::duration<int> elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - *timestamp);
    int seconds = elapsed_seconds.count();
    std::cout << "Within seconds: " << seconds;
    if (seconds < 1) {
        seconds = 1;
    } else if (seconds > 5) {
        seconds = 5;
    }
    std::cout << " Points Got : " << 6 - seconds<< std::endl;
    // Calculate return the output value inversely proportional to the input
    
    return 6 - seconds;
}


void Game::pauseOrResumeGame(){
  if((*this).isGamePaused)
  { 
    resume();
  }else{
    pause();
    }
}


void Game::pause(){
  (*this).isGamePaused = true;  
  std::cout << "Game Paused : " << std::endl;
}

void Game::resume(){
  (*this).isGamePaused = false;
  std::cout << "Game Resumed : " << std::endl;
}

void TimerThread(Snake &snake, float actual) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    // get back to normal after 5 seconds
    snake.speed = actual
}