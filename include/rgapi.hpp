/*!ricardogames api*/
#pragma once
#include <string>

/**the version number of the current build of the api
*/
#define RGAPI_VERSION "0.0.1"
/**the serverside api version this build of the library uses.
*/
#define RGAPI_SERVER_VERSION "0.1.0"

/**load the api.
* load the ricardogames api, must be called before any other fuctions are run (exept getplayername and getplayersession)
*/
extern void loadrgapi();

/**get the latest api version of the library.
* \param dologging log info about the version to the console (still logs deprication message)
* \return returns true if on the latest version
*/
extern bool getapiversion(bool dologging);

/**get the latest server api version.
* this can be different than the library version because of bugfixes
* \param dologging log info about the version to the console (still logs deprication message)
* \return returns true if on the latest version
*/
extern bool getserverapiversion(bool dologging);

/**the latest version of the api.
* run getapiversion to get a value
*/
extern std::string latestapiver;

/**the version of the api on the server.
* run getserverapiversion to get a value
*/
extern std::string latestserverapiver;


/**get the id of a player with a specific name.
* \param name name of the player to search
* \return returns the id of the player with the given name
*/
extern int getidfromname(std::string name);

/**get the id of a player with a specific name.
* \param name the name of the player to search
* \return returns the id of the player with the given name or -1 if no player was found
*/
extern int getidfromname(const char* name);

/**get the username of a player with a specific id.
* \param id the id of the player to search
* \returns the name of the player with te given id or "ERROR: no player found" if no player was found
*/
extern std::string getnamefromid(int id);

/**get player name given by launcer
* pass trough __argc and __argv on windows and  argc and argv on linux
* \param argc argc launch argument
* \param argv argv launch argument
* \returns the username of the player
*/
extern std::string getplayername(int argc, char* argv[]);

/**get session given by launcer
* pass trough __argc and __argv on windows and  argc and argv on linux
* \param argc argc launch argument
* \param argv argv launch argument
* \returns the session of the player
*/
extern std::string getplayersession(int argc, char* argv[]);

/**get the amount of records the player has in doolhof, de game!
* \param id id of the player
* \returns the amount of world records the player has or -1 on an error
*/
extern int getwrcount(int id);

/**get a new session.
* if ERROR is returned imediatly exit because the session may have been stolen by the server
* \param id the id of the player
* \param session the current session
* \returns the new session or ERROR on an error
*/
extern std::string newsession(int id, std::string session);

/**check if a given session is correct.
* used for checking if the player is who he says he is on the server
* only accept players when this function returns true
* \param id id of the player to check
* \param session the session given by the player
* \returns a boolean, if true the session is correct, false if incorrect
*/
extern bool checksession(int id, std::string session);