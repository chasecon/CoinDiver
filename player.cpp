#include "player.h"
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
Player::Player( const std::string& name) :  
TurningMultiSprite(name),
  xPressed(false),
  yPressed(false),
  initVelocity(getVelocity()) {}

Player::Player(const Player& s) : 
TurningMultiSprite(s),
  xPressed(s.xPressed),
  yPressed(s.yPressed),
  initVelocity(getVelocity()){}
/*
void RunningTurningMultiSprite::draw() const { 
  frames[currentFrame]->draw(getX(), getY());
}
*/
void Player::draw() const { 
  frames[currentFrame]->draw(getX(), getY());
}


void Player::stopY(){
 // if(!xPressed) setVelocityX(0.0);
  setVelocityY(0.0);
}
void Player::stopX(){
  setVelocityX(0.0);

 // if(!yPressed) setVelocityY(0.0);
}

void Player::right(){
xPressed=true;
if(getX()<worldWidth-frameWidth){
  //setVelocityX(-getVelocityX());
  setVelocityX(-initVelocity[0]);
}
}

void Player::left(){
xPressed=true;
if(getX()>0){
  setVelocityX(initVelocity[0]);
}
}

void Player::up(){
yPressed=true;
if(getY() > 0){
  setVelocityY(-initVelocity[1]);
}
}

void Player::down(){

yPressed=true;
/*
if(getY() < worldHeight -frameHeight){
  setVelocityY(initVelocity[1]);
}*/
if(getY() < worldHeight -170){
  setVelocityY(initVelocity[1]);
}

}

void Player::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  //double incrY = getVelocityY() * static_cast<float>(ticks) * 0.001;

  setPosition(getPosition() + incr);

  if ( getY() < 80) {

   stopY();

    //setVelocityY( fabs( getVelocityY() ) );
  }
  /*
  if ( getY() > worldHeight-frameHeight+70 && getY() > worldHeight-frameHeight+80) {
    std::cout<<"below" <<std::endl;
        setY(getY() - incr[1]);

    //stopY();
    //setVelocityY( -fabs( getVelocityY() ) );
  }*/
    if ( getY() > worldHeight-170) {
        setY(getY() - incr[1]);

    //stopY();
    //setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    stopX();
    //setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    stopX();
    //setVelocityX( -fabs( getVelocityX() ) );
  }   
  if(getVelocityX() < 0){
    if(frames != framesLeft){
      frames = framesLeft;
    }

  }else if (getVelocityX() > 0){
    if(frames != framesRight)
    {
        frames = framesRight;
    }
  }

  //if(!yPressed) stopY();
  if(!xPressed) stopX();
  yPressed=false;
  xPressed=false;



}
