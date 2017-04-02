#ifndef ENGINE__H
#define ENGINE__H

#include <vector>
#include <SDL.h>
//#include "ioMod.h"
//#include "renderContext.h"
//#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "hud.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World worldC;
  World worldB;
  World worldA;
  Viewport& viewport;

  std::vector<Drawable*> sprites;

  int currentSprite;
  bool makeVideo;

  void draw() const;
  void update(Uint32);
  Player* player;
  Hud* hud;
  bool showHud;
  int hudTicks;
  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
};
#endif