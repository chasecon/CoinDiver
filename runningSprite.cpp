#include "runningSprite.h"
#include "gamedata.h"
#include "renderContext.h"

void RunningSprite::advanceFrame(Uint32 ticks) {
  timeSinceLastFrame += ticks;
  if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
    timeSinceLastFrame = 0;
  }
}

RunningSprite::RunningSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           1.0
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

RunningSprite::RunningSprite(const RunningSprite& s) :
  Drawable(s), 
  frames(s.frames),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }

void RunningSprite::draw() const { 
  frames[currentFrame]->draw(getX(), getY(),getScale());
}


void RunningSprite::update(Uint32 ticks) { 
    advanceFrame(ticks);
  float incr = getVelocityX() * static_cast<float>(ticks) * 0.001;
  setX(getX() + incr);

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  
}
