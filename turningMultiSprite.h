#ifndef TURNINGMULTISPRITE__H
#define TURNINGMULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class TurningMultiSprite : public Drawable {
public:
  TurningMultiSprite(const std::string&);
  TurningMultiSprite(const std::string&, float vScale);
  TurningMultiSprite(const TurningMultiSprite&);

  Vector2f makeVelocity(int xv, int yx) const;
  Vector2f makeStartLoc() const;
  Vector2f makeStartSeagullLoc() const;


  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  std::vector<Frame *> frames;
  const std::vector<Frame *> framesRight;
  const std::vector<Frame *> framesLeft;



  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;


  void advanceFrame(Uint32 ticks);
};
#endif
