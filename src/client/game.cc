
#include <SDL.h>
#include <GL/glew.h>
#include <stdlib.h>

#include "client/game.h"

Game::Game() {
}

void Game::Init() {
  area_.units_[0].pos_[0] = 0.0f;
  area_.units_[0].pos_[1] = 0.5f;
  area_.units_[0].dir_ = 0.0f;

  area_.units_[1].pos_[0] = -0.5f;
  area_.units_[1].pos_[1] = -0.5f;
  area_.units_[1].dir_ = 2.0f;

  graphics_.Init();
  input_reader_.Init();
}

void Game::UpdateVertices() {
  for (size_t i = 0; i < 2; ++i) {
    Unit& u = area_.units_[i];
    float* vs = vertices_ + i*6;
    vs[0] = u.pos_[0];
    vs[1] = u.pos_[1] + 0.1f;
    vs[2] = u.pos_[0] + 0.1f;
    vs[3] = u.pos_[1];
    vs[4] = u.pos_[0] - 0.1f;
    vs[5] = u.pos_[1];
  }
}

void Game::UpdatePlayer(Actions& a) {
  Unit& u = area_.units_[0];
  if (a.actions & Commands::MOVE_FORWARD)
    u.pos_[1] += 0.05f;
  if (a.actions & Commands::MOVE_BACK)
    u.pos_[1] -= 0.05f;
  if (a.actions & Commands::MOVE_LEFT)
    u.pos_[0] -= 0.05f;
  if (a.actions & Commands::MOVE_RIGHT)
    u.pos_[0] += 0.05f;
}

void Game::Run()
{
  Actions actions;

  while (true)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (input_reader_.ReadInput(actions))
      break;
    UpdatePlayer(actions);

    UpdateVertices();
    graphics_.DrawTriangles(vertices_, 12);

    SDL_GL_SwapBuffers();
  }

}
