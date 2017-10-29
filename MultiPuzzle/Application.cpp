#include "Application.h"
#include "MainMenu.h"
#include "InGame.h"
#include "SDLGraphics.h"
#include "SDLText.h"

Application::Application()
  : m_mainMenuWindow(nullptr),
    m_inGameWindow(nullptr)
{
	
}
	
Application::~Application()
{
  m_pActiveWindow = nullptr;
}

bool Application::Initialize()
{
	m_mainMenuWindow = new MainMenu();
	m_inGameWindow = new InGame();

	if (!m_mainMenuWindow->Initialize())
	{
		return false;
	}

	if (!m_inGameWindow->Initialize())
	{
		return false;
	}
	
	m_windowMap.insert(std::pair<WindowState, BaseWindow*>(WS_MAINMENU, m_mainMenuWindow));
	m_windowMap.insert(std::pair<WindowState, BaseWindow*>(WS_INGAME, m_inGameWindow));

	SetState(WS_MAINMENU);

	return true;
}

bool Application::InitModules()
{
	if (!SDLGraphics::StartUp())
	{
		printf("Can't Init SDL Graphic Module");
		return false;
	}

	FontData fontData;
	fontData._pathFontFile = "c:/windows/fonts/arialbd.ttf";
	fontData._fontSize = 32;

	if (!SDLText::StartUp(fontData))
	{
		printf("Can't Init SDL Text Module");
		return false;
	}

	return true;
}

void Application::Run()
{
	//SDL input events
	SDL_Event event;

	//Init timer
	m_timer.Reset();
	srand(SDL_GetTicks());

	//Init Modules
	if (!InitModules())
	{
		return;
	}
	
	//Init Application
	if (!Initialize())
	{
		return;
	}
	
	//Get Current Ticks
	m_fLastTime = static_cast<float>(m_timer.getMilliseconds());
	double lag = 0.0f;

	bool bQuit = false;

	while (!bQuit)
	{
		//Get Current Ticks
		m_fActualTime = static_cast<float>(m_timer.getMilliseconds());

		//DeltaTime Calculus in milliseconds
		m_fDeltaTime = m_fActualTime - m_fLastTime;
		m_fLastTime = m_fActualTime;
		lag += m_fDeltaTime;

    while (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT) {
        bQuit = true;
        break;
      }

      m_pActiveWindow->ManageInputs(event);
    }

	if (m_pActiveWindow->m_bChangeWindow)
	{
		m_pActiveWindow->m_bChangeWindow = false;

		WindowState actualState = m_pActiveWindow->GetWindowChange();
		SetState(actualState);

		if (actualState == WS_INGAME)
		{
			m_pActiveWindow->Destroy();
			m_pActiveWindow->Initialize();
		}
	}

		while (lag >= MS_PER_UPDATE)
		{
			Update(static_cast<float>(MS_PER_UPDATE));
			lag -= MS_PER_UPDATE;
		}

		Render();
	}

	Destroy();

	SDLGraphics::ShutDown();
	SDLText::ShutDown();
}

void Application::Update(float _deltaTime)
{
	SDL_GetMouseState(&m_mousePos.X, &m_mousePos.Y);
	m_pActiveWindow->SetMousePos(m_mousePos);
	m_pActiveWindow->Update(_deltaTime);
}

void Application::Render()
{
	SDLGraphics::Instance().ClearBackBuffer();

	m_pActiveWindow->Render();

	SDLGraphics::Instance().RenderPresent();
}

void Application::Destroy()
{
	m_windowMap.clear();

	m_pActiveWindow = nullptr;

	m_mainMenuWindow->Destroy();
	delete m_mainMenuWindow;
	m_mainMenuWindow = nullptr;

	m_inGameWindow->Destroy();
	delete m_inGameWindow;
	m_inGameWindow = nullptr;
}

void Application::SetState(WindowState _state)
{
  auto foundObj = m_windowMap.find(_state);
  if (foundObj == m_windowMap.end())
  {
	  printf("Actual state don´t exist");
	  return;
  }

  m_pActiveWindow = foundObj->second;
}
