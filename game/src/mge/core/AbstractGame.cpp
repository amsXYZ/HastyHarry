#include "AbstractGame.hpp"

#include <iostream>
using namespace std;

#include "mge/core/Timer.hpp"
#include "mge/core/FPS.hpp"
#include "mge/core/Renderer.hpp"
#include "mge/core/World.hpp"
#include "mge/core/SoundEngine.hpp"

AbstractGame::AbstractGame():_window(NULL),_renderer(NULL),_world(NULL),_running(false)
{
    //ctor
}

AbstractGame::~AbstractGame()
{
    //dtor
    delete _window;
    delete _renderer;
    delete _world;
}

void AbstractGame::initialize() {
    cout << "Initializing engine..." << endl << endl;
    _initializeWindow();
    _printVersionInfo();
    _initializeGlew();
    _initializeRenderer();
    _initializeWorld();

    _initializeScene();

    cout << endl << "Engine initialized." << endl << endl;
}

///SETUP

void AbstractGame::_initializeWindow() {
	cout << "Initializing window..." << endl;
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Model Loader", sf::Style::Default, sf::ContextSettings(24, 8, 0, 3, 5));
	//_window = new sf::RenderWindow( sf::VideoMode(1920,1080), "My Game!", sf::Style::Fullscreen, sf::ContextSettings(24,8,0,3,5));
	_window->setVerticalSyncEnabled(true);
	_window->setMouseCursorVisible(false);
	cout << "Window initialized." << endl << endl;
}

void AbstractGame::_printVersionInfo() {
	cout << "Context info:" << endl;
    cout << "----------------------------------" << endl;
    //print some debug stats for whoever cares
    const GLubyte *renderer = glGetString( GL_RENDERER );
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
    printf("GL Renderer : %s\n", renderer);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    cout << "----------------------------------" << endl << endl;
}

void AbstractGame::_initializeGlew() {
	cout << "Initializing GLEW..." << endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
	cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << endl << endl;
}

void AbstractGame::_initializeRenderer() {
    //setup our own renderer
	cout << "Initializing renderer..." << endl;
	_renderer = new Renderer();
    cout << "Renderer done." << endl << endl;
}

void AbstractGame::_initializeWorld() {
    //setup our own renderer
	cout << "Initializing world..." << endl;
	_world = new World();
    cout << "World initialized." << endl << endl;
}

///LOOP

void AbstractGame::run()
{
	_running = true;

	while (_running) {
		Timer::update();
		FPS::update();

	    //clear frame, do it here so we can draw debug stuff in any other step etc
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        _update();

		if(Timer::deltaTime() > 0.0f) {
			_world->getPhysics()->Advance(Timer::deltaTime());
		}

        _render();

        //swap colorbuffer to screen
        _window->display();

		_processEvents();
	}
}

void AbstractGame::_update() {
    _world->update(Timer::deltaTime(), glm::mat4());
}

void AbstractGame::_render () {
    _renderer->render(_world);
}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

	//we must empty the event queue
	while( _window->pollEvent( event ) ) {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you...
        //SystemEventDispatcher::dispatchEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    exit = true;
                }
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }
	}

	if (exit) {
        _window->close();
        _running = false;
	}
}



