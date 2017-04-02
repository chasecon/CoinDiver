#ifndef RUNNINGTURNINGMULTISPRITE__H
#define RUNNINGTURNINGMULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "turningMultiSprite.h"

class RunningTurningMultiSprite : public TurningMultiSprite {
public:
  RunningTurningMultiSprite(const std::string&);
  RunningTurningMultiSprite(const RunningTurningMultiSprite&);

  //virtual void draw() const;
  virtual void update(Uint32 ticks);
  /*virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
*/
protected:
  /*
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
*/
  //void advanceFrame(Uint32 ticks);
};
#endif
