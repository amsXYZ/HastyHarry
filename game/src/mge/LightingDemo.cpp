#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/FPS.hpp"

#include "mge/core/Camera.hpp"
#include "mge/core/Light.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "materials\TextureMaterial.hpp"
#include "materials\PhongMaterial.hpp"

#include "mge/behaviours/PlayerBehaviour.hpp"
#include "behaviours\LookAt.hpp"
#include "behaviours\Turret.hpp"
#include "behaviours\SoundBehaviour.hpp"
#include "behaviours\MovingBehaviour.hpp"
#include "behaviours\Butterfly.hpp"
#include "behaviours/ArmBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/LightingDemo.hpp"

#include "mge\core\Level.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
LightingDemo::LightingDemo():AbstractGame ()
{
}

void LightingDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void LightingDemo::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

	//Turrets and Butterfly showcase

	/*Level::Load("Goal.xml", _world);

	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "Billboard.obj");
	AbstractMaterial* textureMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.png"));
	
	GameObject* billboard = new GameObject("Billboard", glm::vec3(0, 0, 0), GameObject::PhysicsType::ANIMATEDBODY);
	_world->add(billboard);
	billboard->setMesh(planeMeshDefault);
	billboard->scale(glm::vec3(1.0f, 0.5f, 1.0f));
	billboard->setMaterial(textureMaterial);
	billboard->setBehaviour(new Turret(Level::CurrentPlayer, 10.0f));

	std::vector<glm::vec3> waypoints;
	waypoints.push_back(glm::vec3(0, 0, 10));
	waypoints.push_back(glm::vec3(0, 0, 0));
	waypoints.push_back(glm::vec3(0, 0, -10));

	GameObject* butterfly = new GameObject("Butterfly", glm::vec3(0, 0, -10), GameObject::PhysicsType::ANIMATEDBODY);
	_world->add(butterfly);
	butterfly->setMesh(planeMeshDefault);
	butterfly->setMaterial(textureMaterial);
	butterfly->setBehaviour(new MovingBehaviour(glm::vec3(0, 0, -10), glm::vec3(0, 0, -10), 1.0f, false));
	butterfly->setBehaviour(new Butterfly(Level::CurrentPlayer, 5.0f, (MovingBehaviour*)butterfly->getBehaviour(), waypoints));*/

	Level::Load("TestDanny.xml", _world);

	//Level::Load("Level_03.xml", _world);

	/*
	GameObject * s = new GameObject("lol");
	_world->add(s);
	s->setBehaviour(new ArmBehaviour(true));
	*/

	//Init Light
    Light* light = new Light("Light",glm::vec3(3.0f,3.0f,3.0f),glm::vec3(-2.0f,-1.0f,-3.0f),glm::vec3(1.0f,1.0f,1.0f),2.0f,60.0f,false);
    _world->add(light);
    _world->setLights(light);
}

void LightingDemo::_render() {
    AbstractGame::_render();
    _updateHud();

    //_world->renderDebugInfo();
}

void LightingDemo::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}


LightingDemo::~LightingDemo()
{
	delete _hud;
}
