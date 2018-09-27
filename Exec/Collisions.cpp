//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Collisions.cpp
// ---------------
// This class handles all the collisions in the game between two cells.
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 19/05/15		  Ori Riner				  Creation.
//
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "Collisions.h"
#include "MathPlayer.h"
#include "NumberCell.h"
#include "ColumnFlyer.h"
#include "RowFlyer.h"
#include "NumberEater.h"
#include "PlayerShot.h"

#pragma region Player
bool Collisions::collide(  MathPlayer& player,   MathPlayer& otherPlayer){ 
	// Impossible, due to handling of "Blocking" cells instead of players.
	return false;
}

bool Collisions::collide(  MathPlayer& player,   NumberCell& number){ 
	if (player.getQuestion()->validate(number.getNumericValue()))
	{
		// Clear the number
		number.reset();
		if (player.getQuestion()->isDone()){
			player.setWinningStatus(true);
			player.increaseGameScore();

			// although the control rows need to be updated the level will end and it will re-draw eventually.
			return false;
		}
		else{
			// the question has been updated with the current hit.
			// need to update the control rows
			return true;
		}

	}
	else
	{
		number.reset();
		player.decreaseLifeAmount();

		// need to update the control rows
		return true;
	}
}

bool Collisions::collide(  MathPlayer& player,   PlayerShot& shot){
	player.reset();
	player.setClearAfterCollision(true);
	shot.reset();
	shot.setClearAfterCollision(true);
	return true;
}

bool Collisions::collide(  MathPlayer& player,   NumberEater& eater){
	eater.kill();
	eater.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  MathPlayer& player,   ColumnFlyer& flyer){
	player.reset();
	player.setClearAfterCollision(true);
	return true;
}

bool Collisions::collide(  MathPlayer& player,   RowFlyer& flyer){
	player.reset();
	player.setClearAfterCollision(true);
	return true;
}
#pragma endregion

#pragma region Shot
bool Collisions::collide(  PlayerShot& shot,   PlayerShot& otherShot){ 
	shot.reset();
	shot.setClearAfterCollision(true);
	otherShot.reset();
	otherShot.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  PlayerShot& shot,   NumberCell& number){
	shot.reset();
	shot.setClearAfterCollision(true);
	number.reset();
	number.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  PlayerShot& shot,   NumberEater& eater){
	shot.reset();
	shot.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  PlayerShot& shot,   ColumnFlyer& flyer){
	shot.reset();
	shot.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  PlayerShot& shot,   RowFlyer& flyer){
	shot.reset();
	shot.setClearAfterCollision(true); 
	return false;
} 
#pragma endregion

#pragma region Eater
bool Collisions::collide(  NumberEater& eater,   NumberCell& number){
	number.reset();
	number.setClearAfterCollision(true);
	eater.setHasDestinationNumber(false);
	return false;
}

bool Collisions::collide(  NumberEater& eater,   NumberEater& otherEater){
	eater.kill();
	eater.setClearAfterCollision(true); 
	otherEater.kill();
	otherEater.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  NumberEater& eater,   ColumnFlyer& flyer){
	eater.kill();
	eater.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  NumberEater& eater,   RowFlyer& flyer){
	eater.kill();
	eater.setClearAfterCollision(true);
	return false;
}
#pragma endregion

#pragma region ColumnFlyer
bool Collisions::collide(  ColumnFlyer& flyer,   NumberCell& number){
	number.reset();
	number.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  ColumnFlyer& flyer,   ColumnFlyer& otherFlyer){
	// Impossible, due to different columns.
	return false;
}

bool Collisions::collide(  ColumnFlyer& flyer,   RowFlyer& otherFlyer){
	// nothing happens.
	return false;
}
#pragma endregion

#pragma region RowFlyer
bool Collisions::collide(  RowFlyer& flyer,   NumberCell& number){
	number.reset();
	number.setClearAfterCollision(true);
	return false;
}

bool Collisions::collide(  RowFlyer& flyer,   RowFlyer& otherFlyer){
	// Impossible, due to different rows.
	return false;
}
#pragma endregion