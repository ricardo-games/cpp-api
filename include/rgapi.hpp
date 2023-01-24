#pragma once
#include <string>

/**the major version number of the current build of the api
*/
#define RGAPI_MAJOR_VERSION "0"
/**the minor version number of the current build of the api
*/
#define RGAPI_MINOR_VERSION "2"
/**the fix version number of the current build of the api
*/
#define RGAPI_FIX_VERSION "0"

/**the major serverside api version this build of the library uses.
*/
#define RGAPI_SERVER_MAJOR_VERSION "0"
/**the minor serverside api version this build of the library uses.
*/
#define RGAPI_SERVER_MINOR_VERSION "2"
/**the fix serverside api version this build of the library uses.
*/
#define RGAPI_SERVER_FIX_VERSION "0"

/**boolean to use localhost for the api site.
* defaults to false, only set to true if you want to debug serverside and have the serverside files
*/
extern bool uselocalhost;

/**load the ricardogames api, must be called before any other fuctions are run (exept getplayername and getplayersession)
* \param dologging log info to the console
* \param description short description of the program. it is best to just put the name of your program here.
* \param contactinfo info that will be used to contact you if there is a problem with the api usage (no info = ban)
*/
extern void RGAPI_Load(bool dologging, std::string description, std::string contactinfo);

/**load the ricardogames api, must be called before any other fuctions are run (exept getplayername and getplayersession)
* \param dologging log info to the console
* \param description short description of the program. it is best to just put the name of your program here.
* \param contactinfo info that will be used to contact you if there is a problem with the api usage (no info = ban)
*/
extern void RGAPI_Load(bool dologging, const char* description, const char* contactinfo);

/**correctly shut down the api.
* this correctly closes things the library uses
*/ 
extern void RGAPI_Quit();

/**get the latest api version of the library.
* \param dologging log info about the version to the console
* \return 1 if up to date, 0 if outdated, -1 if depricated
*/
extern int RGAPI_GetVersion(bool dologging);

/**get the latest server api version.
* this can be different than the library version because of bugfixes
* \param dologging log info about the version to the console
* \return 1 if up to date, 0 if outdated, -1 if depricated
*/
extern int RGAPI_GetServerVersion(bool dologging);

/**the latest version of the api.
* run getapiversion to get a value
*/
extern std::string RGAPI_LatestVer;

/**the version of the api on the server.
* run getserverapiversion to get a value
*/
extern std::string RGAPI_LatestServerVer;


/**get the id of a player with a specific name.
* \param name the name of the player to search
* \return the id of the player with the given name or -1 if no player was found
*/
extern int RGAPI_NameToID(std::string name);

/**get the id of a player with a specific name.
* \param name the name of the player to search
* \return the id of the player with the given name or -1 if no player was found
*/
extern int RGAPI_NameToID(const char* name);

/**get the username of a player with a specific id.
* \param id the id of the player to search
* \return the name of the player with te given id or "ERROR: no player found" if no player was found
*/
extern std::string RGAPI_IDToName(int id);

/**get player name given by launcher
* \param argc argc launch argument
* \param argv argv launch argument
* \return the username of the player
*/
extern std::string RGAPI_GetName(int argc, char* argv[]);

/**get session given by launcher.
* \param argc argc launch argument
* \param argv argv launch argument
* \return the session of the player
*/
extern std::string RGAPI_GetSession(int argc, char* argv[]);

/**get the amount of records the player has in doolhof, de game!
* \param id id of the player
* \return the amount of world records the player has or -1 on an error
*/
extern int RGAPI_GetWRCount(int id);

/**get a new session.
* if ERROR is returned imediatly exit because the session may have been stolen by the server
* \param id the id of the player
* \param session the current session
* \return the new session or ERROR on an error
*/
extern std::string RGAPI_NewSession(int id, std::string session);

/**check if a given session is correct.
* used for checking if the player is who he says he is on the server
* only accept players when this function returns true
* \param id id of the player to check
* \param session the session given by the player
* \return true if the session is correct, false if incorrect
*/
extern bool RGAPI_CheckSession(int id, std::string session);