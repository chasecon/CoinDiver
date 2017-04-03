#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "runningSprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "turningMultiSprite.h"
#include "runningTurningMultiSprite.h"
#include "stayingMultiSprite.h"
#include "player.h"
#include <random>

class SpriteLess {
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};


Engine::~Engine() { 

  std::cout << "Terminating program" << std::endl;
  //std::vector<Drawable*>::iterator it = sprites.begin();
  //while ( it != sprites.end() ) {
  for(auto it : sprites){
   // std::cout << it << " , " << it->getName()<< " deleted" << std::endl;
    delete it;
    //++it;
  }
  for(auto it : spritesBack){
   // std::cout << it << " , " << it->getName()<< " deleted" << std::endl;
    delete it;
    //++it;
  }
  for(auto it : spritesMiddle){
   // std::cout << it << " , " << it->getName()<< " deleted" << std::endl;
    delete it;
    //++it;
  }
  for(auto it : spritesFront){
   // std::cout << it << " , " << it->getName()<< " deleted" << std::endl;
    delete it;
    //++it;
  }
  //delete player;
  delete hud;

}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  worldC("c", Gamedata::getInstance().getXmlInt("c/factor") ),
  worldB("b", Gamedata::getInstance().getXmlInt("b/factor") ),
  worldA("a", Gamedata::getInstance().getXmlInt("a/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  spritesBack(),
  spritesMiddle(),
  spritesFront(),
  currentSprite(-1),
  makeVideo( false ),
  player(new Player("diver",1.0)),
  hud(new Hud("hud")),
  showHud(true),
  hudTicks(0)
{



  constexpr float u = 0.8f; //Mean size
  constexpr float d = 0.3f; //Std deviation

  std::random_device rd;
  std::mt19937 mt(rd());
  std::normal_distribution<float> dist(u,d);
  unsigned int numB = Gamedata::getInstance().getXmlInt("numBack");
  unsigned int numM = Gamedata::getInstance().getXmlInt("numMiddle");
  unsigned int numF = Gamedata::getInstance().getXmlInt("numFront");

for ( unsigned int i = 0; i < numB; ++i ) {
    auto* s = new TurningMultiSprite("seagull");
    float scale = dist(mt);
    while(scale > 0.33f) scale = dist(mt);
    s->setScale(scale);
    spritesBack.push_back(s);
  }
for ( unsigned int i = 0; i < numM; ++i ) {
  string name = "";
  if(i%2==0){ 
      name = "tuna";   
    }
    else{    
      name="fish";
    }
    auto* s = new TurningMultiSprite(name);

    float scale = dist(mt);
    while((scale < 0.2f) || (scale > 0.5f)) scale = dist(mt);
    s->setScale(scale);
    spritesMiddle.push_back(s);
  }
for ( unsigned int i = 0; i < numF; ++i ) {
  string name = "";
  if(i%2==0){ 
      name = "tuna";   
    }
    else{    
      name="fish";
    }
    auto* s = new TurningMultiSprite(name);
    float scale = dist(mt);
    while(scale < 0.66f) scale = dist(mt);
    s->setScale(scale);
    spritesFront.push_back(s);
  }

std::vector<Drawable*>::iterator ptr = spritesBack.begin();
  ++ptr;
  sort(ptr, spritesBack.end(), SpriteLess());
  for ( Drawable* sprite : sprites ) {
    Sprite* thisone = dynamic_cast<Sprite*>(sprite);
    if ( thisone ) {
      std::cout << thisone->getScale() << std::endl;
    }
  }
  ptr = spritesMiddle.begin();
  ++ptr;
  sort(ptr, spritesMiddle.end(), SpriteLess());
  for ( Drawable* sprite : sprites ) {
    Sprite* thisone = dynamic_cast<Sprite*>(sprite);
    if ( thisone ) {
      std::cout << thisone->getScale() << std::endl;
    }
  }

  ptr = spritesFront.begin();
  ++ptr;
  sort(ptr, spritesFront.end(), SpriteLess());
  for ( Drawable* sprite : sprites ) {
    Sprite* thisone = dynamic_cast<Sprite*>(sprite);
    if ( thisone ) {
      std::cout << thisone->getScale() << std::endl;
    }
  }

  sprites.push_back(player);
  //sprites.push_back( new TurningMultiSprite("diver"));
  sprites.push_back( new RunningTurningMultiSprite("malloy"));






  // sprites.push_back( new RunningTurningMultiSprite("tuna"));
  // sprites.push_back( new RunningTurningMultiSprite("fish"));
  // sprites.push_back( new TurningMultiSprite("tuna"));
  // sprites.push_back( new TurningMultiSprite("fish"));
  spritesFront.push_back( new StayingMultiSprite("coin",170,900));
  spritesFront.push_back( new StayingMultiSprite("coin",190,900));
  spritesFront.push_back( new StayingMultiSprite("coin",210,900));
  spritesFront.push_back( new StayingMultiSprite("coin",230,900));
  spritesFront.push_back( new StayingMultiSprite("coin",250,900));
  spritesFront.push_back( new StayingMultiSprite("coin",1480,900));
  spritesFront.push_back( new StayingMultiSprite("coin",1500,900));
  spritesFront.push_back( new StayingMultiSprite("coin",1520,900));
  spritesFront.push_back( new StayingMultiSprite("coin",1540,900));
  spritesFront.push_back( new StayingMultiSprite("coin",1560,900));

 // std::cout << Gamedata::getInstance().getXmlInt("malloy/startLoc/x") << std::endl;
  //std::cout << Gamedata::getInstance().getXmlInt("malloyLeft/startLoc/x") << std::endl;

  switchSprite();
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  worldC.draw();
  for(auto* s : spritesBack) s->draw();

  worldB.draw();
    for(auto* s : spritesMiddle) s->draw();

  worldA.draw();
  for(auto* s : spritesFront) s->draw();

  //std::stringstream strm;
  //std::cout <<clock.getAvgFps() <<std::endl;
  // strm << "fps: " << clock.getFps() << " | Avg FPS: "<<clock.getAvgFps();
  // io.writeText(strm.str(), 15, 50);
  // io.writeText("Chase Conklin", 350, 50,{0xff, 0, 0, 0});
  // io.writeText(Gamedata::getInstance().getXmlStr("username"), 15,25);
  io.writeText(Gamedata::getInstance().getXmlStr("name"), 0, Gamedata::getInstance().getXmlInt("view/height")-30,{255, 255, 0, 255 });

  io.writeText(Gamedata::getInstance().getXmlStr("screenTitle"), 15,0);
  for(auto* s : sprites) s->draw();

  if(showHud){
    hud->draw();
  }


  viewport.draw();

  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* s : sprites) s->update(ticks);
  for(auto* s : spritesBack) s->update(ticks);
  for(auto* s : spritesMiddle) s->update(ticks);
  for(auto* s : spritesFront) s->update(ticks);
  worldC.update();
  worldB.update();
  worldA.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  currentSprite++;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }

      if(event.type == SDL_KEYDOWN) 
      {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) 
        {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) 
        {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
          /*
          if ( keystate[SDL_SCANCODE_S] ) {
            clock.toggleSloMo();
          }
          */
          if ( keystate[SDL_SCANCODE_T] ) 
          {
            switchSprite();
          }
          if (keystate[SDL_SCANCODE_F4] && !makeVideo) 
          {
            std::cout << "Initiating frame capture" << std::endl;
            makeVideo = true;
          }else if (keystate[SDL_SCANCODE_F4] && makeVideo) 
          {
            std::cout << "Terminating frame capture" << std::endl;
            makeVideo = false;
          }
      }


}
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {



        if(showHud){
          hudTicks++;
          if(hudTicks == 200){
            hudTicks = 0;
            showHud=false;
          }
        }

        if (keystate[SDL_SCANCODE_F1]) {
          showHud = true;
          hudTicks=0;
        }

        if( (keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_S]) || (!keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S])){
          player->stopY();

        }else if(keystate[SDL_SCANCODE_W]){
          player->up();

        }else if(keystate[SDL_SCANCODE_S]){
          player->down();
        }

        if( (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_D]) || (!keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D])){
          player->stopX();

        }else if(keystate[SDL_SCANCODE_A]){
          player->left();

        }else if(keystate[SDL_SCANCODE_D]){
          player->right();
        }


      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}

