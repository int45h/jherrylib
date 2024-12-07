#pragma once

#include "seek.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

/*
		tahmlib
		A C++ library for Game Development

		Author: Tamta Asatiani
		tamta@geolab.edu.ge

		-- Main Engine --

		Contains declarations for all of the methods and attributes
		provided in tahmlib.
*/

#if defined(__unix__)
#include <dlfcn.h>

typedef void* PluginHandle;
#endif

typedef void(*StartMethod)();
typedef void(*KeyPressedMethod)(Event);
typedef void(*UpdateMethod)(float);
typedef void(*DrawMethod)();

#define SCRIPT_PATH "./"
class Tahm;
class NativeScript
{
    private:
    StartMethod m_start;
    KeyPressedMethod m_keyPressed;
    UpdateMethod m_update;
    DrawMethod m_draw;
    
    PluginHandle handle;

    public:
    NativeScript(): 
        m_start(NULL), 
        m_keyPressed(NULL), 
        m_update(NULL), 
        m_draw(NULL) {}

    bool LoadSharedObject(const char *filepath);
    bool Bind(Tahm *);
    bool Close();

    bool RunStart();
    bool RunKeyPressed(Event event);
    bool RunUpdate(float delta);
    bool RunDraw();
};


// engine class
class Tahm {
	
private:	// classes
	// tahm's window. made up of
	// the SDL window + methods and parameters for it
	class Window
	{
	public: // attributes
		SDL_Window* SDLwindow;

	public:	// methods
		// should get called in "start". passes a reference to
		// the desired window title, width, and height,
		// which is later used by void init to initialize a 
		// window with the desired parameters.
		void create(const char* title, int width, int height);

	private: // attributes
		const char* title = "Untitled";

		int width = 1280;
		int height = 720;

		int flags = 0;

	private: // methods
		// initialize a window, pass a reference inside the SDLwindow
		void init(void); 

		friend class Tahm;
	};

	class Input
	{
	public:
		// holds a reference to the keyboard state
		const Uint8* keyPressed = SDL_GetKeyboardState(NULL);
	};

	// tahm's renderer. made up of
	// the SDL renderer + methods and parameters for it
	class Renderer
	{
	public:	// attributes
		int flags = SDL_RENDERER_ACCELERATED;

		// pointer that points to the engine's window
		Window* window;
		SDL_Renderer* SDLrenderer;

	public: // methods
		// creates a reference to the game window
		Renderer(Window& window);

	private: // methods
		// initialize renderer
		void init(void); 


		// prepare a default scene to render - blank black screen
		// called before the "draw" function
		void prepare(void); 

		// present the rendered scene to the renderer
		void present(void);	

		friend class Tahm;
	};

public:	// classes
	// functions and methods associated with rendering
	// used by the developer for rendering different objects
	class Graphics
	{
	public:	// classes
		class Font
		{
		public: // methods
			Font();

			// create new font
			TTF_Font* newFont(const char* path, int size);

		};

		// class for drawing shapes or images
		class Draw
		{
		private: // attributes 
			Renderer* renderer;
		public:	// methods
			Draw(Renderer& renderer);

			SDL_Rect rect(int x, int y, int width, int height);
		};

	public:	// attributes
		Draw* draw;
		Font* font;

	public: // methods
		Graphics(Renderer& renderer);
		~Graphics();

		// fill the scene with a blank color
		// takes in arguments "red", "green", "blue", and "alpha" to determine the desired color
		void clear(int r, int g, int b, int a = 255);

		// set the drawing color. works like a state machine, tahm has an active color
		// takes in arguments "red", "green", "blue", and "alpha" to determine the desired color
		void setColor(int r, int g, int b, int a = 255);

		// draw text to screen
		// takes in arguments for the text position (x, y), font,
		// and the text that should be rendered
		void renderText(int x, int y, TTF_Font* font, const char* text);

		// draw text to screen and align it horizontally - left, center, or right
		// takes in arguments for the alignment style ('left', 'center', or 'right'),
		// alignment width, left and top margins, font,
		// and the text that should be rendered
		void renderText(const char* alignment, int alignmentWidth, int marginX, int marginY, TTF_Font* font, const char* text);

	private:	// attributes
		Renderer* renderer;

		// current active color
	private:
		Color color = { 0, 0, 0 , 255}; // all four attributes must be defined
	};


	// general class for audio management
	class Audio
	{
	public:	// classes
		// class for creating sound instances
		class Sound
		{
		private:	// attributes
			SDL_AudioSpec* spec;
			Uint8* waveStart;
			Uint32 waveLength;

			SDL_AudioDeviceID* device;

		public:	// methods
			Sound(const char* path, SDL_AudioSpec* spec);
			~Sound();

			void play();
		
		private:
			void linkDevice(SDL_AudioDeviceID& device); 

			friend class Audio;
		};

	public:	// methods
		Audio();

		// create a new sound
		Sound* newSound(const char* path);

	private:	// attributes
		SDL_AudioDeviceID device;	
		SDL_AudioSpec spec;

	private:	// methods
		void setupDevice();

		friend class Tahm;
	};

public:	// attributes
	// instances to all of the nested classes
	Window window;
	Input input;
	Renderer renderer;
	Graphics graphics;
	Audio audio;

public:	// methods
	static Tahm& getInstance();
	void run();
    bool loadPlugin(const char *path);

	~Tahm();

private:	// attributes
	static Tahm* tahm;

    // script instance
    NativeScript script;
    
    // callbacks shouldn't be allowed to be called from the outside

	// update & render running
	bool running;

private:	// methods
	Tahm(): 
        window(Window()), 
        input(Input()),
        renderer(Renderer(window)),
        graphics(Graphics(renderer)),
        audio(Audio()),
        running(true)
    {};
	void init(void); 

	void setup();		
	void loop();		
	void handleEvents();	

	// destroy window, renderer, and quit the application
	void destroy();	
	
};

