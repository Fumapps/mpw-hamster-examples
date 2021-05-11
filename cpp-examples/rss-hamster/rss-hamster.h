#pragma once

#include <Mode.h>
#include "SimpleHamsterGame.h"
#include "blocking_queue.h"

using namespace mpw;
using namespace hamster;
using namespace hamstersimulator;

class SimpleHamsterGameInC : public SimpleHamsterGame {
public:
    static void createInstance(std::string& territoryFilename) {
        SimpleHamsterGameInC program(territoryFilename);
        program.doRun();
    }
private:
    blocking_queue<std::function<void(Hamster&)>> commandQueue;
    blocking_queue<std::optional<std::exception>> resultQueue;
    std::string& territoryFilename;
public:
    SimpleHamsterGameInC(std::string& territoryFilename) : commandQueue(1), resultQueue(1), territoryFilename(territoryFilename){};
	Hamster& getDefaultHamster() const {
		return this->paule;
	}
	void run() override;
	std::optional<std::exception> sendCommand(std::function<void(Hamster&)> command) {
        commandQueue.push(command);
        auto result = resultQueue.front();
        resultQueue.pop();
        return result;
	}
};

extern SimpleHamsterGameInC* runningGame;

typedef struct HamsterSpec {
    Hamster& hamster;
} HamsterSpec;

/** \brief Initializes the Hamster Simulator, sets up a default territory, and places Paule in it.
 *
 *  This function initalizes the hamster game, sets up a default territory, and places Paule in it.
 *  The function is useful for early exercises. In addition the UI of the Hamster Simulator is started and
 *  displayed. After init has executed, you are ready to issue Hamster commands or queries.
 */
 void init(void);

/** \brief Adds a new Hamster to the game.
*
* Adds a new hamster with the given position, the given looking direction and
* the given grain count to the game. Added hamsters cannot be removed from the territory
* without restarting the game.
*/
HamsterSpec addHamster(int row, int column, int direction, int grainCount);

/** \brief Release the ressources of the given hamster
 *
 * Releases the interal ressources of the given hamster. The hamster
 * simulator does not remove the hamster itself from the territory.
 * However, released hamsters are not allowed to execute any command
 * after they have been released.
 */
void releaseHamster(HamsterSpec hamster);

/** \brief Initializes the Hamster Simulator, sets up the provided territory, and places Paule in it.
 *
 *  This function initalizes the hamster game, sets up the provided territory, and places Paule in it.
 *  The function is useful for early exercises. In addition the UI of the Hamster Simulator is started and
 *  displayed. After init has executed, you are ready to issue Hamster commands or queries.
 */
void init(const char *filename);

/** \brief Moves the hamster a single steps towards its looking direction
*
* This function moves the hamster a single tile forward in its looking direction. The move
* is only allowed if the tile in front of the hamster exists (i.e., the hamster is not allowed
* to leave the gamefield) and it is not blocked by a wall. An attempt to make the move
* nevertheless results in an exception.
*/
void move(void);

/** \brief Moves the hamster a single steps towards its looking direction
*
* This function moves the given hamster a single tile forward in its looking direction. The move
* is only allowed if the tile in front of the hamster exists (i.e., the hamster is not allowed
* to leave the gamefield) and it is not blocked by a wall. An attempt to make the move
* nevertheless results in an exception.
*
* \param hamster A struct describing the hamster to be moved. To move the default hamster use the
*				 parameterless variant of this function.
*/
void move(HamsterSpec hamster);

/** \brief Rotates the hamster by 90 degrees counterclockwise.
*
* This function changes the hamster's looking direction by rotating the hamster 90 degrees counterclockwise.
*/
void turnLeft(void);

/** \brief Rotates the hamster by 90 degrees counterclockwise.
*
* This function changes the hamster's looking direction by rotating the hamster 90 degrees counterclockwise.
* \param hamster A struct describing the hamster to be moved. To move the default hamster use the
*				 parameterless variant of this function.
*/
void turnLeft(HamsterSpec hamster);

/** \brief Picks up a grain from the hamster's current tile.
*
* This function transfers a grain from the hamster's current tile into the mouth of the hamster. The function
* can only be called if there is a gain on the current tile. If not, the program raises an exception.
*/
void pickGrain(void);

/** \brief Picks up a grain from the hamster's current tile.
*
* This function transfers a grain from the hamster's current tile into the mouth of the hamster. The function
* can only be called if there is a gain on the current tile. If not, the program raises an exception.
* \param hamster A struct describing the hamster to be moved. To move the default hamster use the
*				 parameterless variant of this function.
*/
void pickGrain(HamsterSpec hamster);

/** \brief Puts a grain from the hamster's mouth on the hamster's current tile.
*
* This function transfers a grain from the hamster's mouth to the hamster's current tile. The function
* can only be called if there is a gain in the hamster's mouth. If not, the program raises an exception.
*/
void putGrain(void);

/** \brief Puts a grain from the hamster's mouth on the hamster's current tile.
*
* This function transfers a grain from the hamster's mouth to the hamster's current tile. The function
* can only be called if there is a gain in the hamster's mouth. If not, the program raises an exception.
* \param hamster A struct describing the hamster to be moved. To move the default hamster use the
*				 parameterless variant of this function.
*/
void putGrain(HamsterSpec hamster);

/** \brief Reads a number from the user by prompting the user using the provided message
*
* This function asks the user to enter a valid number. The passed message is used as
* message prompt.
* \param message The message used when prompting for the user's input.
* \result A pointer to an integer variable used to store the result.
*/
int readNumber(const char *message);

/** \brief Reads a number from the user by prompting the user using the provided message
*
* This function asks the user to enter a valid number. The passed message is used as
* message prompt.
* \param message The message used when prompting for the user's input.
* \param hamster A struct describing the hamster to be moved. To move the default hamster use the
*				 parameterless variant of this function.
* \result A pointer to an integer variable used to store the result.
*/
int readNumber(HamsterSpec hamster, const char *message);


/** \brief Shuts down the hamster game and terminates the hamster simulator core
*
* This function stops the running hamster game and shuts down the core hamster simulator engine.
* The UI stays active and the game history can still be tracked.
*/
void deinit(void);

/** \brief Returns true if the tile in front of the hmaster is clear
*
* \result true if the tile in front of the hamster is clear
*/
bool frontIsClear(void);

/** \brief Returns true if there are grains availabe to pick up on the hamster's current tile
*
* \result true if the hamster's current tile contains at least one grain
*/
bool grainAvailable();

/** \brief Returns true if the hamster has no grains in its mouth
*
* \result true if the hamster's mouth is empty
*/
bool mouthEmpty();

/** \brief Prints the given message on the hamster's log
*
* This function prints the provided message on the hamster's log.
* \param message The message to print to the log. Is not allowed to be null.
*
*/
void write(const char *message);

/** \brief Lets the hamster say a message formated with the same format string used in printf
*
* Lets the hamster say a message formated with the same format string used in printf. The number
* of arguments has to match the number of format placeholders used. It is also not necessary to
* use a newline ('\\n') at the end.
*
* Find the documentation of the printf
* function under http://www.cplusplus.com/reference/cstdio/printf/
*
* \param message_template A templated string of the message to be written.
*/
void writef(const char *message_template, ...);