#include <Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <Bites/OgreInput.h>

#include "Engine.h"
#include "Connection.h"

namespace SSGEClient
{

class App :
	public OgreBites::ApplicationContext,
	public OgreBites::InputListener
{
public:
	SSGEClient::Engine* engine;
	SSGEClient::Connection* conn;

	Ogre::Root* root;
	Ogre::SceneManager* scnMgr;

	App();
	~App();

	/**
	 * Startup
	 */
	void start();

	/**
	 * Create scene
	 */
	void createScene();

	/**
	 * Setup OGRE renderer
	 */
	void setup();

	/**
	 * Keypress event handler
	 *
	 * @param evt Event
	 * @return Returns true
	 */
	bool keyPressed(const OgreBites::KeyboardEvent& evt);

	/**
	 * Frame event handler
	 * 
	 * @param evt Event
	 */
	void frameRendered(const Ogre::FrameEvent &evt);
};

} // namespace SSGEClient
