//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// TheMathGame.h
// -------------
// This class represent the math game.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// 26/03/15	      Ori Riner				  Creation
// 27/03/15		  Ori Riner				  Handling the generating of random numbers on the screen.
// 28/03/15		  Ori Riner				  Drawing the control rows for a level.
// 28/03/15		  Omri Avrahami			  Adding players functionality
// 29/03/15		  Omri Avrahami			  Handle keyboard cycle
// 30/03/15		  Omri Avrahami			  Players movement + UI changes + levels change
// 06/04/15		  Ori Riner				  Updated the way the random numbers are checked - can handle numbers in any length (digit-wise)
// 25/04/15		  Omri Avrahami			  Added players shooting
// 25/05/15		  Omri Avrahami			  Semi flood-fill algorithem
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <list>
#include "TheMathGame.h"
#include "NumberCell.h"
#include "Question.h"
#include "ComplexQuestion.h"
#include "io_utils.h"
#include "NumberEater.h"
#include "ColumnFlyer.h"
#include "RowFlyer.h"

using namespace std;

BoardCell* TheMathGame::getCell(const Position& position)const{
	return board[position.getY()][position.getX()];
}

void TheMathGame::setCell(const Position& position, BoardCell* newCell){

	if (!board[position.getY()][position.getX()]->isPremanent()){
		delete board[position.getY()][position.getX()];
	}
	board[position.getY()][position.getX()] = newCell;
}

void TheMathGame::resetNeighboors(const Position& position){
	int i = position.getX()+1;

	// We are not actually replacing the cells with empty cells because resetting marks each cell as empty.

	// Clear the right side of the cell
	for (Position p(i, position.getY());
		i < 80 && !getCell(p)->isEmpty();
		p = Position(++i,position.getY())){
		getCell(p)->reset();
		draw(p);
	}

	// Clear the left side of the cell
	i = position.getX() - 1;
	for (Position p(i, position.getY());
		i >= 0 && !getCell(p)->isEmpty();
		p = Position(--i, position.getY())){
		getCell(p)->reset();
		draw(p);
	}
}

void TheMathGame::generateNumber(){
	
	int seed = currentLevel < 21 ? currentLevel : 11;
	
	// random new number to display which includes casting to char.
	int newNumber = rand() % (10 + seed) + 49;
	list<int> digits;
	Position currentPosition;

	getDigitsForNumber(newNumber - 48, digits);
	
	for (int i = 0; i < 10; i++){
		
		// Generate the currentPosition to place the number and the position next to it (for more than one digit numbers)
		currentPosition = Position(rand() % Position::X_EDGE, (rand() % (Position::Y_EDGE - Position::CONTROL_ROWS)) + Position::CONTROL_ROWS);
		Position nextPosition(currentPosition);
		
		bool canPlaceNumber = true;

		for (list<int>::iterator it = digits.begin(); it != digits.end(); it++)
		{
			// Check that the next digit has no neighboors.
			// Also if this is the last digit - verify that it is not out of bounds.
			if (!verifyEmptyNeighborhood(nextPosition) || 
				(*it != digits.back() && (nextPosition.getRightX() == nextPosition.getX())))
			{
				canPlaceNumber = false;
				break;
			}
			nextPosition = Position(nextPosition, Direction::RIGHT);

		}

		if (canPlaceNumber){
		
			nextPosition = Position(currentPosition);
			
			for (list<int>::iterator it = digits.begin(); it != digits.end(); it++)
			{
				// Update the number eaters of the new number
				list<Creature*>::iterator currentCreature = creatures.begin();
				while (currentCreature != creatures.end()){
					(*currentCreature)->informNewNumber(nextPosition);

					currentCreature++;
				}

				drawNewCell(nextPosition, new NumberCell((*it) + 48, newNumber - 48));
				nextPosition = Position(nextPosition, Direction::RIGHT);
			}
			
			break;
		}
	}
}

void TheMathGame::getDigitsForNumber(int number, list<int>& digits) const{

	while (number > 0){
		digits.push_front(number % 10);
		number /= 10;
	}

}

bool TheMathGame::verifyEmptyNeighborhood(const Position& position)const{
	return getCell(position)->isEmpty()
		&& getCell(Position(position, Direction::UP))->isEmpty()
		&& getCell(Position(position, Direction::DOWN))->isEmpty()
		&& getCell(Position(position, Direction::LEFT))->isEmpty()
		&& getCell(Position(position, Direction::RIGHT))->isEmpty();
}

void TheMathGame::draw(const Position& position)const{
	BoardCell* cell = getCell(position);

	setTextColor(cell->getColor());
	gotoxy(position.getX(), position.getY());
	cout << (cell->isEmpty() ? ' ' : cell->getSign());
	setTextColor(LIGHTGREY);
}

void TheMathGame::drawControlRows() const{
	// Draw level title + border
	gotoxy(0, 0);
	for (int rowIndex = 0; rowIndex < Position::CONTROL_ROWS; rowIndex++){
		cout << "                                                                                ";
	}
	gotoxy(32, 0);
	cout << "LEVEL-" << currentLevel;
	gotoxy(0, 4);
	cout << "--------------------------------------------------------------------------------";
	// Draw player 1.
	drawPlayerControlRows(this->leftPlayer, 0);
	// Draw player 2.
	drawPlayerControlRows(this->rightPlayer, 54);
}
void TheMathGame::drawPlayerControlRows(const MathPlayer& player, int column)const {
	gotoxy(column, 0);
	cout << "shots   :";
	setTextColor(YELLOW);
	cout << player.getShotsString();
	setTextColor(LIGHTGREY);
	gotoxy(column, 1);
	cout << "score   :";
	gotoxy(player.getGameScore() < 10 ? column + 9 : column + 10, 1);
	cout << player.getGameScore();
	gotoxy(column, 2);
	cout << "lives   :";
	gotoxy(column + 9, 2);
	setTextColor(LIGHTRED);
	cout << player.getLifeString();
	setTextColor(LIGHTGREY);
	gotoxy(column, 3);
	cout << "question:";
	gotoxy(column + 9, 3);
	cout << player.getQuestion()->toString();
}

TheMathGame::TheMathGame() 
	: rightPlayer(this->RIGHT_PLAYER_SIGN, Position(70, 9), this->RIGHT_PLAYER_FIRST_DIR,LIGHTGREEN),
	leftPlayer(this->LEFT_PLAYER_SIGN, Position(10, 9), this->LEFT_PLAYER_FIRST_DIR, LIGHTBLUE), isCurrentGameFinished(false),
	  currentLevel(0),currentIterationsNumber(1500) {
	creatures.push_back(new NumberEater(Position(10,19)));
	creatures.push_back(new NumberEater(Position(70, 19)));
	creatures.push_back(new ColumnFlyer(Position(45, 23), Direction::UP));
	creatures.push_back(new ColumnFlyer(Position(55, 15), Direction::DOWN));
	creatures.push_back(new RowFlyer(Position(30, 23), Direction::RIGHT));
	creatures.push_back(new RowFlyer(Position(50, 15), Direction::LEFT));
}

void TheMathGame::initBoard()
{
	for (int columnIndex = 0; columnIndex < Position::X_EDGE; columnIndex++){
		for (int rowIndex = 0; rowIndex < Position::Y_EDGE; rowIndex++)
		{
			// creating empty cells.
			board[rowIndex][columnIndex] = new BoardCell;
		}
	}

	// Clear the shots
	for (list<PlayerShot*>::iterator it = currentShots.begin(); it != currentShots.end(); it++)
	{
		delete (*it);
	}
	currentShots.clear();
}

bool TheMathGame::isLevelDone()const{
	return (rightPlayer.getWinningStatus() ||
		    leftPlayer.getWinningStatus()  ||
			(rightPlayer.getLifeAmount() == 0 && leftPlayer.getLifeAmount() == 0) ||
			currentIterationsNumber == 1500);
}
void TheMathGame::startLevel(){
	currentLevel++;
	isCurrentGameFinished = false;
	currentIterationsNumber = 0;
	rightPlayer.init(currentLevel);
	leftPlayer.init(currentLevel);
	initBoard();
	clear_screen();
	drawControlRows();

	// Draw the players
	drawNewCell(leftPlayer.getPosition(), &leftPlayer);
	drawNewCell(rightPlayer.getPosition(), &rightPlayer);

	list<Creature*>::iterator creature = creatures.begin();
	while (creature != creatures.end()){
		(*creature)->reset();
		drawNewCell((*creature)->getPosition(), *creature);
		creature++;
	}
}

void TheMathGame::continueLevel()
{
	clear_screen();

	// Draw the prevoius screen
	drawControlRows();

	for (int columnIndex = 0; columnIndex < Position::X_EDGE; columnIndex++){
		for (int rowIndex = 0; rowIndex < Position::Y_EDGE; rowIndex++)
		{
			Position currentPosition = Position(columnIndex,rowIndex);
			if (!getCell(currentPosition)->isEmpty()){
				draw(currentPosition);
			}
		}
	}

}

void TheMathGame::doIteration(list<char>& keyHits){
	this->currentIterationsNumber++;
	bool hasRightPlayerShot = false;
	bool hasLeftPlayerShot = false;
	if (this->currentIterationsNumber % 200 == 0)
	{
		this->rightPlayer.increaseShotsAmount();
		this->leftPlayer.increaseShotsAmount();
		drawControlRows();
	}

	for (list<char>::iterator it = keyHits.begin(); it != keyHits.end(); it++)
	{
		switch (*it)
		{
		case 'W':
		case 'w':	
			this->leftPlayer.setLastDirection(Direction::UP);
			break;
		case 'A':
		case 'a':
			this->leftPlayer.setLastDirection(Direction::LEFT);
			break;
		case 'D':
		case 'd':
			this->leftPlayer.setLastDirection(Direction::RIGHT);
			break;
		case 'X':
		case 'x':
			this->leftPlayer.setLastDirection(Direction::DOWN);
			break;
		case 'I':
		case 'i':
			this->rightPlayer.setLastDirection(Direction::UP);
			break;
		case 'J':
		case 'j':
			this->rightPlayer.setLastDirection(Direction::LEFT);
			break;
		case 'L':
		case 'l':
			this->rightPlayer.setLastDirection(Direction::RIGHT);
			break;
		case 'M':
		case 'm':
			this->rightPlayer.setLastDirection(Direction::DOWN);
			break;
		case 'Z':
		case 'z':
			if (!hasLeftPlayerShot){
				this->mathGameShoot(leftPlayer);
				hasLeftPlayerShot = true;
			}
			break;
		case 'N':
		case 'n':
			if (!hasRightPlayerShot){
				this->mathGameShoot(rightPlayer);
				hasRightPlayerShot = true;
			}
			break;
		}
	}
	
	// Move the players
	moveMathPlayer(rightPlayer,leftPlayer);
	moveMathPlayer(leftPlayer,rightPlayer);

	moveCreatures(false);

	// After we have finished doing all the work for the current iteration we need to "generate" some number to appear on the screen.
	generateNumber();
}
void TheMathGame::doSubIteration(){
	
	moveCreatures(true);

	// Move and draw the shots
	list<PlayerShot*>::iterator currentShot = this->currentShots.begin();
	while (currentShot != this->currentShots.end())
	{
		if (!(*currentShot)->isEmpty()){
			// empty the previous cell and draw it.
			drawNewCell((**currentShot).getPosition(), new BoardCell);

			(**currentShot).move();

			// Check if there is any collision
			if (!getCell((**currentShot).getPosition())->isEmpty())
			{
				if (getCell((**currentShot).getPosition())->collide(*currentShot)){
					drawControlRows();
				}
				if (getCell((**currentShot).getPosition())->isPartialCell()){
					resetNeighboors((**currentShot).getPosition());
				}
		
				if (getCell((**currentShot).getPosition())->getClearAfterCollision()){
					// clearing the current cell if there was a collision.
					drawNewCell((**currentShot).getPosition(), new BoardCell);
				}
				
				// Delete the shot
				delete *currentShot;
				currentShot = this->currentShots.erase(currentShot);
			}
			else{
				drawNewCell((**currentShot).getPosition(), new PlayerShot(**currentShot));
				currentShot++;
			}
		}
		else{
			delete *currentShot;
			currentShot = this->currentShots.erase(currentShot);
		}
	}
}

TheMathGame::~TheMathGame(){
}

void TheMathGame::moveMathPlayer(MathPlayer& player, MathPlayer& otherPlayer)
{
	if (player.getLifeAmount() > 0 &&
		player.getLastDirection() != Direction::STAY &&
		!getCell(player.getPosition(player.getLastDirection(), 1))->isBlocking())
	{
		drawNewCell(player.getPosition(), new BoardCell);
		player.move();

		if (!getCell(player.getPosition())->isEmpty()){
			if (getCell(player.getPosition())->collide(&player))
			{
				drawControlRows();
			}

			if (getCell(player.getPosition())->isPartialCell()){
				resetNeighboors(player.getPosition());
			}
		}

		if (!player.getClearAfterCollision() && player.getLifeAmount() > 0){
			drawNewCell(player.getPosition(), &player);
		}
		else{
			drawNewCell(player.getPosition(), new BoardCell);
			player.setClearAfterCollision(false);
		}
	}
}

void TheMathGame::showGameInstructions()
{
	clear_screen();
	setTextColor(LIGHTBLUE);
	cout << "********************************************************************************";
	cout << " ..|'''.|                                '||''|.            '||" << endl;
	cout << ".|'     '   ....   .. .. ..     ....      ||   ||  ... ...   ||    ....   ...." << endl;
	cout << "||    .... '' .||   || || ||  .|...||     ||''|'    ||  ||   ||  .|...|| ||. '" << endl;
	cout << "'|.    ||  .|' ||   || || ||  ||          ||   |.   ||  ||   ||  ||      . '|.." << endl;
	cout << " ''|...'|  '|..'|' .|| || ||.  '|...'    .||.  '|'  '|..'|. .||.  '|...' |'..|'" << endl << endl;
	cout << "********************************************************************************";
	setTextColor(LIGHTGREY);
	cout << endl;
	cout << "              Player #1                             Controls" << endl;
	cout << "-------------------------------------------------------------------------------";
	cout << "" << endl;								                              
	cout << "              ,.-==-.                                ____                " << endl;
	cout << "           ,pd'      `g.                            ||W || <- UP         " << endl;
	cout << "          ,P   ,dMb.A  Y.                           ||__||               " << endl;
	cout << "         ,P   dP  ,MP  j8                           |/__\\|              " << endl;
	cout << "         8:  dM'  dM   d'                       ____       ____          " << endl;
	cout << "         Wb  YML.dML..d'               LEFT -> ||A ||     ||D || <- RIGHT" << endl;
	cout << "          Wb  ``\"\"^`\"'                         ||__||     ||__||      " << endl;
	cout << "           `M..     .,!                        |/__\\|     |/__\\|	     " << endl;
	cout << "             `Ybmmd'                              ____  ____	         " << endl;
	cout << "                                        SHOOT -> ||Z ||||X || <- DOWN    " << endl;
	cout << "                                                 ||__||||__||            " << endl;
	cout << "                                                 |/__\\||/__\\|          " << endl;
	cout << " Player #2 ->";
	_getch();
	clear_screen();
	setTextColor(LIGHTBLUE);
	cout << "********************************************************************************";
	cout << " ..|'''.|                                '||''|.            '||" << endl;
	cout << ".|'     '   ....   .. .. ..     ....      ||   ||  ... ...   ||    ....   ...." << endl;
	cout << "||    .... '' .||   || || ||  .|...||     ||''|'    ||  ||   ||  .|...|| ||. '" << endl;
	cout << "'|.    ||  .|' ||   || || ||  ||          ||   |.   ||  ||   ||  ||      . '|.." << endl;
	cout << " ''|...'|  '|..'|' .|| || ||.  '|...'    .||.  '|'  '|..'|. .||.  '|...' |'..|'" << endl << endl;
	cout << "********************************************************************************";
	setTextColor(LIGHTGREY);
	cout << endl;
	cout << "              Player #2                             Controls" << endl;
	cout << "-------------------------------------------------------------------------------";
	cout << "" << endl;
	cout << "                                                    ____                " << endl;
	cout << "             ,M' dP                          UP -> ||I ||               " << endl;
	cout << "             dP .M'                                ||__||               " << endl;
	cout << "           mmmMmmMmm                               |/__\\|              " << endl;
	cout << "            MP dP                              ____       ____          " << endl;
	cout << "         mmdMmmMmmm                   LEFT -> ||J ||     ||L || <- RIGHT" << endl;
	cout << "          ,M' dP                              ||__||     ||__||         " << endl;
	cout << "          dP ,M'                              |/__\\|     |/__\\|       " << endl;
	cout << "                                            ____  ____                  " << endl;
	cout << "                                  SHOOT -> ||N ||||M || <- DOWN         " << endl;
	cout << "                                           ||__||||__||                 " << endl;
	cout << "                                           |/__\\||/__\\|               " << endl;
	cout << " Insturctions ->";
	_getch();
	clear_screen();
	setTextColor(LIGHTBLUE);
	cout << "********************************************************************************";
	cout << " ..|'''.|                                '||''|.            '||" << endl;
	cout << ".|'     '   ....   .. .. ..     ....      ||   ||  ... ...   ||    ....   ...." << endl;
	cout << "||    .... '' .||   || || ||  .|...||     ||''|'    ||  ||   ||  .|...|| ||. '" << endl;
	cout << "'|.    ||  .|' ||   || || ||  ||          ||   |.   ||  ||   ||  ||      . '|.." << endl;
	cout << " ''|...'|  '|..'|' .|| || ||.  '|...'    .||.  '|'  '|..'|. .||.  '|...' |'..|'" << endl << endl;
	cout << "********************************************************************************";
	setTextColor(LIGHTGREY);
	cout << endl;
	cout << " You are two players, so there is only one WINNER!" << endl;
	cout << " Be the first to collect a solution for your equation and you score one point!" << endl;
	cout << " If you collect an answer that does not solve your equation you lose a life!" << endl;
	cout << " After 3 wrong answers you will die and will continue only in the next level." << endl;
	cout << " At which point, the other player can play freely to get his point." << endl;
	cout << " If you both lose all your life - you both will continue in the next level." << endl;
	cout << " Oh yeah, you have 5 shots as well, use them to destroy unwanted solutions." << endl;
	cout << " You will also regain a shoot every 200 cycles." << endl << endl << endl << endl << endl << endl << endl ;
	cout << " Back to the Main Menu ->";
	_getch();
	clear_screen();
}

void TheMathGame::setLevel(int level)
{
	if (level < 1 || level > this->NUMBER_OF_LEVELS)
	{
		level = 1;
	}

	// start level will be called next so it will increase by one later.
	this->currentLevel = level - 1;
}

int TheMathGame::getLevel() const
{ 
	return this->currentLevel; 
}

int TheMathGame::getLastIterationsDuration() const
{
	return this->currentIterationsNumber;
}

bool TheMathGame::getLeftPlayerStatus()const
{
	return this->leftPlayer.getWinningStatus();
}

bool TheMathGame::getRightPlayerStatus()const
{
	return this->rightPlayer.getWinningStatus();
}

void TheMathGame::endCurrentLevel(){
	
	for (int columnIndex = 0; columnIndex < Position::X_EDGE; columnIndex++){
		for (int rowIndex = 0; rowIndex < Position::Y_EDGE; rowIndex++)
		{
			// deleting all the refrences we made this level.
			if (board[rowIndex][columnIndex] != NULL &&
			    !board[rowIndex][columnIndex]->isPremanent()){
				delete board[rowIndex][columnIndex];
				board[rowIndex][columnIndex] = NULL;
			}
		}
	}

	this->currentIterationsNumber = 1500;
}

void TheMathGame::mathGameShoot(MathPlayer& fromPlayer){

	if (fromPlayer.getShotsAmount() > 0)
	{
		fromPlayer.decreaseShotAmount();
		if (fromPlayer.getLastDirection() != Direction::STAY){
			this->currentShots.push_front(new PlayerShot(fromPlayer.getPosition(fromPlayer.getLastDirection()),
				fromPlayer.getLastDirection()));
		}
		else{
			this->currentShots.push_front(new PlayerShot(fromPlayer.getPosition(fromPlayer.getPreviousDirection(),1),
				fromPlayer.getPreviousDirection()));
		}

		drawControlRows();
	}

}

void TheMathGame::drawNewCell(const Position& position, BoardCell* newCell){
	setCell(position, newCell);
	draw(position);
}

void TheMathGame::endCurrentMatch(){
	isCurrentGameFinished = true;
}

void TheMathGame::startCurrentMatch(){
	isCurrentGameFinished = false;
}

bool TheMathGame::isMatchEnded() const{
	return isCurrentGameFinished;
}

void TheMathGame::moveCreatures(bool isFaster){
	// Move all the creatures for the current iteration.
	list<Creature*>::iterator currentCreature = creatures.begin();
	while (currentCreature != creatures.end()){
		if (!(*currentCreature)->isDead()){
			if (!(*currentCreature)->getClearAfterCollision() && ((isFaster && (*currentCreature)->isFaster()) || !(isFaster || (*currentCreature)->isFaster()))){
				drawNewCell((*currentCreature)->getPosition(), new BoardCell);
				(*currentCreature)->move();
				if (!getCell((*currentCreature)->getPosition())->isEmpty()){
					Position originalPosition = (*currentCreature)->getPosition();

					//make a collision with the creature.
					if (getCell(originalPosition)->collide((*currentCreature))){
						drawControlRows();
					}
					if (getCell(originalPosition)->isPartialCell()){
						resetNeighboors((*currentCreature)->getPosition());
					}

					if (getCell(originalPosition)->getClearAfterCollision() && (*currentCreature)->getClearAfterCollision()){
						getCell(originalPosition)->setClearAfterCollision(false);
						drawNewCell(originalPosition, new BoardCell);
					}

					if (getCell(originalPosition)->getClearAfterCollision()){
						getCell(originalPosition)->setClearAfterCollision(false);
					}

					if (!(*currentCreature)->getClearAfterCollision()){
						drawNewCell(originalPosition, (*currentCreature));
					}
					else{
						// otherwise the current cell will remain drawn.
						(*currentCreature)->setClearAfterCollision(false);
					}
				}
				else{
					drawNewCell((*currentCreature)->getPosition(), (*currentCreature));
				}
			}

			// If the current creature is numberEater there is a need to give it a new destination
			if (!(*currentCreature)->getHasDestinationNumber())
			{
				bool isFound = false;

				(*currentCreature)->setNearestNumberPosition(this->getNearestNumber((*currentCreature)->getPosition(), isFound));

				(*currentCreature)->setHasDestinationNumber(isFound);
			}
		}
		currentCreature++;
	}
}

Position TheMathGame::getNearestNumber(const Position& sourcePos, bool& isFound) const
{
	Position nearestPosition;
	int radius = 0;
	bool found = false;

	while (!found  && radius < Position::X_EDGE)
	{
		++radius;

		for (int currRadius = 0; currRadius <= radius; currRadius++)
		{
			// Check the 8 cells in the currrent radius
			// Upper 2 cells
			if ((dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() + currRadius, sourcePos.getY() - radius).toRange())) != NULL) &&
				(!dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() + currRadius, sourcePos.getY() - radius).toRange()))->getIsEmptyNumber()))
			{
				nearestPosition = Position(sourcePos.getX() + currRadius, sourcePos.getY() - radius).toRange();
				found = true;
			}
			else if ((dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() - currRadius, sourcePos.getY() - radius).toRange())) != NULL) &&
				(!dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() - currRadius, sourcePos.getY() - radius).toRange()))->getIsEmptyNumber()))
			{
				nearestPosition = Position(sourcePos.getX() - currRadius, sourcePos.getY() - radius).toRange();
				found = true;
			}
			// Bottom 2 Cells
			else if ((dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() + currRadius, sourcePos.getY() + radius).toRange())) != NULL) &&
				(!dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() + currRadius, sourcePos.getY() + radius).toRange()))->getIsEmptyNumber()))
			{
				nearestPosition = Position(sourcePos.getX() + currRadius, sourcePos.getY() + radius).toRange();
				found = true;
			}
			else if ((dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() - currRadius, sourcePos.getY() + radius).toRange())) != NULL) &&
				(!dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() - currRadius, sourcePos.getY() + radius).toRange()))->getIsEmptyNumber()))
			{
				nearestPosition = Position(sourcePos.getX() - currRadius, sourcePos.getY() + radius).toRange();
				found = true;
			}
			// Left 2 Cells
			else if ((dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() - radius, sourcePos.getY() + currRadius).toRange())) != NULL) &&
				(!dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() - radius, sourcePos.getY() + currRadius).toRange()))->getIsEmptyNumber()))
			{
				nearestPosition = Position(sourcePos.getX() - radius, sourcePos.getY() + currRadius).toRange();
				found = true;
			}
			else if ((dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() - radius, sourcePos.getY() - currRadius).toRange())) != NULL) &&
				(!dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() - radius, sourcePos.getY() - currRadius).toRange()))->getIsEmptyNumber()))			
			{
				nearestPosition = Position(sourcePos.getX() - radius, sourcePos.getY() - currRadius).toRange();
				found = true;
			}
			// Right 2 cells
			else if ((dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() + radius, sourcePos.getY() + currRadius).toRange())) != NULL) &&
				(!dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() + radius, sourcePos.getY() + currRadius).toRange()))->getIsEmptyNumber()))			
			{
				nearestPosition = Position(sourcePos.getX() + radius, sourcePos.getY() + currRadius).toRange();
				found = true;
			}
			else if ((dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() + radius, sourcePos.getY() - currRadius).toRange())) != NULL) &&
				(!dynamic_cast<NumberCell*>
				(this->getCell(Position(sourcePos.getX() + radius, sourcePos.getY() - currRadius).toRange()))->getIsEmptyNumber()))
			{
				nearestPosition = Position(sourcePos.getX() + radius, sourcePos.getY() - currRadius).toRange();
				found = true;
			}
		}
	}

	isFound = found;

	return nearestPosition;
}