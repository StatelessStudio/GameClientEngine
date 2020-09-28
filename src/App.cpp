#include "App.h"
#include "Engine.h"
#include "CollisionEntity.h"

#include <map>
#include <iostream>

#include <RTShaderSystem/OgreRTShaderSystem.h>

using std::map;

using namespace Ogre;
using namespace OgreBites;

namespace SSGEClient
{

App::App() : ApplicationContext("GameClient")
{
	engine = getEngine();
	conn = new SSGEClient::Connection("127.0.0.1", 2222);
	conn->connected();
}

App::~App()
{
	delete engine;
	delete conn;
}

void App::start()
{
	// Startup
	initApp();
	getRoot()->startRendering();

	// Close after rendering
	closeApp();
}

void App::setup()
{
	// Create application
	ApplicationContext::setup();
	addInputListener(this);

	// Create scene manager
	root = getRoot();
	scnMgr = root->createSceneManager();

	// Setup RTSS
	RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);

	// Create scene
	this->createScene();
}

void App::createScene()
{
	// Create light
	scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));

	Light* light = scnMgr->createLight("MainLight");
	SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->attachObject(light);
	lightNode->setPosition(20, 80, 50);

	SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

	// Create camera
	Camera* cam = scnMgr->createCamera("MainCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	camNode->setPosition(0, 0, 140);

	getRenderWindow()->addViewport(cam);
}

void App::frameRendered(const Ogre::FrameEvent& ev)
{
	// TODO: Catch exceptions here (and above), or they will terminate the program
	try {
		conn->sendMessage();
		engine->step();

		// Update the scene from the server's response
		// TODO: Server should dictate entity type/model
		std::map<unsigned int, CollisionEntity>::iterator it = engine->entities.begin();
		for (it; it != engine->entities.end(); ++it) {
			SSGEClient::CollisionEntity* cent = &(it->second);
			SSGE::Vec3 centpos = cent->getPosition();

			if (cent->hasMesh) {
				cent->ogreNode->setPosition(centpos.x, centpos.y, centpos.z);
			}
			else {
				cent->ogreEntity = scnMgr->createEntity("ogrehead.mesh");
				cent->ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
				cent->ogreNode->setPosition(centpos.x, centpos.y, centpos.z);
				cent->ogreNode->setScale(0.1, 0.1, 0.1);
				//cent->ogreNode->roll(Degree(-90));
				cent->ogreNode->attachObject(cent->ogreEntity);
				cent->hasMesh = true;
			}
		}

		OgreBites::InputListener::frameRendered(ev);

	}
	catch (std::exception ex) {
		std::cerr << "[ERROR] Frame Error: " << ex.what() << std::endl;
		throw ex;
	}
}

bool App::keyPressed(const KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE) {
		getRoot()->queueEndRendering();
	}

	return true;
}

} // namespace SSGEClient
