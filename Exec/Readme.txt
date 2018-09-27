
Student Name	|	ID			|	Group
----------------------------------------------
Ori Riner		|	203754197	|	Maof A
----------------------------------------------
Omri Avrahami	|	203945134	|	Maof A
----------------------------------------------


****************
** Exercise 2 **
****************
Some points for this exercise:
1. A legal value for all operands in a Complex Question is a positive integer < 10000.
2. The allowed value for a varible is one that does not cause the other variable to be:
   I.   over 21 
   II.  non-positive value
   III. other variable is of the form a/b where a,b are integers
3. Each player can shoot once per iteration.
4. When the two players are standing still and one of them shoots it will kill the other player if he is blocking him in the last direction he was headed before the standing still position.
5. Modified the Instructions to be 3 pages long - to keep the swag :)


****************
** Exercise 1 **
****************
Some ground rules for the game:
1. When the two players encounter each other they stop moving.
   But when just a single player has changed its' direction, the other player still stays in its' place.
2. When both players have no more lives the game advances to the next level.
3. When the players finished the last level the game returns to the main menu.
4. Removed the "const" from the function doIteration(const list<char>& keyHits) since it will not compile in MAMA ( also changed from cbegin/cend to begin/end ).
4. Added some ASCII Art for some swag :)

We have also removed the #define WINDOWS from the config.h to be able to compile in MAMA.

The program was developed with Visual Studio 2013