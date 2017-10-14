#include "player.h"
#include "graphics.h"

namespace player_constants 
{
	//This is where I got the values. http://tasvideos.org/GameResources/SNES/MegamanX/Data.html
	const float RUN_SPEED = 0.15f;
	const float DASH_SPEED = 0.35f;
	const float JUMP_SPEED = 0.5f;					//Initial upward speed from jump
	const float TERMINAL_DOWNWARD_SPEED = 0.575f;	//Max speed while falling
	const float GRAVITY = 0.25f;					
}

Player::Player() {}

Player::Player(Graphics &graphics, float x, float y) :
	//(graphics, filePath of spritesheet, x on sheet to start, y on sheet to start, draw sprite width, draw sprite height, x drawn on screen, y drawn on screen, frame update time)
	AnimatedSprite(graphics, "content/sprites/player_frames.png", 0, 0, 36, 35, x, y, 60)
//	AnimatedSprite(graphics, "content/sprites/player_frames.png", 0, 0, 64, 64, x, y, 60)
	
	{
		graphics.loadImage("content/sprites/player_frames.png");
		this->setupAnimations();	// Setup Player animations
//		this->playAnimation("standing_idle");

		this->facing = RIGHT;
	}

void Player::setupAnimations()
{
	//***** Largest width: 50px (dash)  Largest height: 56px (explosion) *****//
	//***** So I guess we'll make the sprite sheet frames 60x60 just for easy calculation *****//

	// Teleport animations
	this->addAnimation(7, 0, 0, "teleport_entry", 30, 46, Vector2(0, 0));
	this->reverseAnimation("teleport_entry", "teleport_exit");
 
	// Standing idle animations
	this->addAnimation(3, 0, 47, "standing_idle", 30, 34, Vector2(0, 0));

	// Running animations
	this->addAnimation(11, 0, 81, "running", 36, 35, Vector2(0, 0));
}

void Player::animationDone(std::string currentAnimation){}

void Player::moveLeft()
{
	this->dx = -player_constants::DASH_SPEED;
	this->playAnimation("running");
	this->facing = LEFT;
}

void Player::moveRight()
{
	this->dx = player_constants::RUN_SPEED;
	this->playAnimation("running");
	this->facing = RIGHT;
}

void Player::stopMoving()
{
	this->dx = 0;
	this->playAnimation("standing_idle");
}

void Player::update(float elapsedTime)
{
	// Move by dx
	this->x += dx * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics)
{
	if(this->facing == RIGHT){
		AnimatedSprite::draw(graphics, this->x, this->y, "right");
	}
	else if(this->facing == LEFT)
	{
		AnimatedSprite::draw(graphics, this->x, this->y, "left");
	}
}