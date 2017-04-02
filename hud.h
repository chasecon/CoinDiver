#ifndef HUD__H
#define HUD__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "renderContext.h"
#include "clock.h"
#include "ioMod.h"
#include <sstream>


class Hud : public Drawable {
public:
  Hud(const std::string&);
  Hud(const Hud&);
  ~Hud();
  Hud& operator=(const Hud&);


  virtual void draw() const;

  virtual void update(Uint32 ticks);
  const Frame* getFrame() const{return NULL;};


protected:
Clock& clock;

const IOmod& io;
const RenderContext* rc;


int width;
int height;
SDL_Rect hudRect;
SDL_Renderer * const renderer;


};
#endif
