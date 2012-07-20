#include <alloca.h>
#include <iostream>
#include <math.h>
#include <SDL.h>

#include "client/view/graphics.h"
#include "client/view/video.h"
#include "common/world/world.h"

Graphics::Graphics() {
}

void Graphics::Init() {
  InitTriangles();
}

void Graphics::Destroy() {
  DestroyTriangles();
}

void Graphics::DestroyTriangles() {
  glDeleteProgram(triangle_program_);
  //glDeleteShader( fragmentShader );
  //glDeleteShader( vertexShader );

  glDeleteBuffers(1, &vbo_units_);
  glDeleteVertexArrays(1, &vao_units_);
}

void Graphics::InitTriangles() {
  glGenVertexArrays(1, &vao_units_);
  glBindVertexArray(vao_units_);

  glGenBuffers(1, &vbo_units_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_units_);

  triangle_program_ = LoadShaders("resources/shaders/first.vert",
    "resources/shaders/first.frag");

  GLint posAttrib = glGetAttribLocation(triangle_program_, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);
}

void Graphics::DrawTriangles(float* vertices, size_t n) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6*n, vertices, GL_STREAM_DRAW);
  glDrawArrays(GL_TRIANGLES, 0, 3*(GLsizei)n);
}

void Graphics::DrawWorld(const World& w) {
  const std::map<EntityId, Entity>& entities = w.entities();
  float* vs = (float*) alloca(sizeof(float) * entities.size() * 6);
  float* p = vs;
  float size = 0.2f;
  for (const auto& kv : entities) {
    const Entity& e = kv.second;
    vs[0] = e.x_;
    vs[1] = e.y_ + size;
    vs[2] = e.x_ + size;
    vs[3] = e.y_;
    vs[4] = e.x_ - size;
    vs[5] = e.y_;
    p += 6;
  }
  DrawTriangles(vs, entities.size());
}
