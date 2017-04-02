#include "runningTurningMultiSprite.h"
#include "gamedata.h"
#include "renderContext.h"
/*
void RunningTurningMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}
*/
RunningTurningMultiSprite::RunningTurningMultiSprite( const std::string& name) :  
TurningMultiSprite(name) {}

RunningTurningMultiSprite::RunningTurningMultiSprite(const RunningTurningMultiSprite& s) : 
TurningMultiSprite(s){}
/*
void RunningTurningMultiSprite::draw() const { 
  frames[currentFrame]->draw(getX(), getY());
}
*/
void RunningTurningMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  float incr = getVelocityX() * static_cast<float>(ticks) * 0.001;
  setX(getX() + incr);

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  
  if(getVelocityX() < 0){
    if(frames != framesLeft){
      frames = framesLeft;
    }

  }else{
    if(frames != framesRight)
    {
        frames = framesRight;
    }
  }

}
