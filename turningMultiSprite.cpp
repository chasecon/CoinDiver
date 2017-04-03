#include "turningMultiSprite.h"
#include "gamedata.h"
#include "renderContext.h"

Vector2f TurningMultiSprite::makeVelocity(int xv, int yx) const {
   // float dxv = Gamedata::getInstance().getRandInRange(xv-100,yx+100);
    //float dyv = Gamedata::getInstance().getRandInRange(xv-100,yx+100);

  int dxv = xv;
  int dyx = yx;
  //int newY = 5 + (rand() % (int)(yx + 1));
  //int newX = -1*(5 + (rand() % (int)(xv + 1)));
  int switcher = (rand() % (int)20);
  int switcher2 = (rand() % (int)20);
  if(switcher%2 == 0){ dxv= dxv * (-1.0);}
  if(switcher2%2 == 0){ dyx= dyx * (-1.0);}

    return Vector2f(dxv, dyx);
    //return Vector2f(newX, newY);
}

//gives random location 
Vector2f TurningMultiSprite::makeStartLoc() const {


int newY = (int)(rand()%(Gamedata::getInstance().getXmlInt("world/height")-1) + 1);
int newX =  (int)(rand() %(Gamedata::getInstance().getXmlInt("world/width")-1 )+ 1);

    return Vector2f(newX, newY);
}

//keeps location above water for seagulls
Vector2f TurningMultiSprite::makeStartSeagullLoc() const {

  int newY = (int)(rand()%(Gamedata::getInstance().getXmlInt("world/height")-1) + 1);
  int newX =  (int)(rand() %(Gamedata::getInstance().getXmlInt("world/width")-1 )+ 1);
  if(getName() == "seagull")
  {
  newY = (int)(rand()%(80 + 1));
  }
      return Vector2f(newX, newY);
  }

void TurningMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}
//Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    //Gamedata::getInstance().getXmlInt(name+"/startLoc/y")
TurningMultiSprite::TurningMultiSprite( const std::string& name) :
  Drawable(name, 
           makeStartLoc(), 
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           1.0
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),
  framesRight( RenderContext::getInstance()->getFrames(name) ),
  framesLeft( RenderContext::getInstance()->getFrames(name+"Left") ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ 
  setPosition(makeStartLoc());//hopefully this works
}

TurningMultiSprite::TurningMultiSprite( const std::string& name, float vScale) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(vScale*Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    vScale*Gamedata::getInstance().getXmlInt(name+"/speedY")),
           1.0
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),
  framesRight( RenderContext::getInstance()->getFrames(name) ),
  framesLeft( RenderContext::getInstance()->getFrames(name+"Left") ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

TurningMultiSprite::TurningMultiSprite(const TurningMultiSprite& s) :
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

void TurningMultiSprite::draw() const { 
  frames[currentFrame]->draw(getX(), getY(),getScale());
}



void TurningMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getScale()*getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

if(getName() == "seagull"){

  if ( getY() < 0) {
      setVelocityY( fabs( getVelocityY() ) );
    }
    if ( getY() > 100) {
      setVelocityY( -fabs( getVelocityY() ) );
    }

    if ( getX() < 0) {
      setVelocityX( fabs( getVelocityX() ) );
    }
    if ( getX() > worldWidth-frameWidth) {
      setVelocityX( -fabs( getVelocityX() ) );
    }  

}else if ((getName() == "tuna") ||(getName() == "fish")){

    if ( getY() < 250) {
      setVelocityY( fabs( getVelocityY() ) );
    }
    if ( getY() > worldHeight-frameHeight) {
      setVelocityY( -fabs( getVelocityY() ) );
    }

    if ( getX() < 0) {
      setVelocityX( fabs( getVelocityX() ) );
    }
    if ( getX() > worldWidth-frameWidth) {
      setVelocityX( -fabs( getVelocityX() ) );
    }  

}else {

    if ( getY() < 0) {
      setVelocityY( fabs( getVelocityY() ) );
    }
    if ( getY() > worldHeight-frameHeight) {
      setVelocityY( -fabs( getVelocityY() ) );
    }

    if ( getX() < 0) {
      setVelocityX( fabs( getVelocityX() ) );
    }
    if ( getX() > worldWidth-frameWidth) {
      setVelocityX( -fabs( getVelocityX() ) );
    }  

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
