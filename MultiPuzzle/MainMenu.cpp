#include "MainMenu.h"
#include "SDLGraphics.h"
#include "SDLText.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

bool MainMenu::Initialize()
{
	if (!LoadResources())
	{
		printf("Can´t Load Main Menu Resources");
	}

	m_playButton.X = 350;
	m_playButton.Y = 250;
	m_playButton.m_Width = 300;
	m_playButton.m_Height = 100;

	m_backGround.X = 0;
	m_backGround.Y = 0;
	m_backGround.m_Width = SCREEN_WIDTH;
	m_backGround.m_Height = SCREEN_HEIGHT;

	m_inputs.X = 250;
	m_inputs.Y = 450;
	m_inputs.m_Width = 500;
	m_inputs.m_Height = 250;

	m_titleTextColor = { 255, 255, 255 };
	m_strGameTitle = std::string("MultiPuzzle");
	m_titlePos.X = 430;
	m_titlePos.Y = 80;

	return true;
}

void MainMenu::Update(float _deltaTime)
{
	
	
	_deltaTime;
}

void MainMenu::Render()
{
	SDL_Renderer* renderer = SDLGraphics::Instance().GetSDLRenderer();

	m_backGroundTexture.Render(m_backGround.X, m_backGround.Y, nullptr, m_backGround.m_Width, m_backGround.m_Height);
	m_playButtonTexture.Render(m_playButton.X, m_playButton.Y, nullptr, m_playButton.m_Width, m_playButton.m_Height);
	m_inputsTexture.Render(m_inputs.X, m_inputs.Y, nullptr, m_inputs.m_Width, m_inputs.m_Height);
	
	SDLText::Instance().RenderBlendedText(m_strGameTitle, m_titleTextColor, m_titlePos.X, m_titlePos.Y, *renderer);
}

void MainMenu::Destroy()
{
	m_playButtonTexture.Free();
}

void MainMenu::ManageInputs(SDL_Event& pEvent)
{
	if (pEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		//If the left mouse button was pressed
		if (pEvent.button.button == SDL_BUTTON_LEFT)
		{
			if (CheckPointRectCollision(m_playButton, m_mousePos))
			{
				m_bChangeWindow = true;
			}
		}
	}

}

void MainMenu::SetMousePos(Point _mousePos)
{
	m_mousePos = _mousePos;
}

WindowState MainMenu::GetWindowChange()
{
	return WS_INGAME;
}

bool MainMenu::LoadResources()
{
	SDL_Renderer* renderer = SDLGraphics::Instance().GetSDLRenderer();

	if (!m_playButtonTexture.LoadFromFile(renderer, "Resources/Textures/play_button.png"))
	{
		return false;
	}

	if (!m_backGroundTexture.LoadFromFile(renderer, "Resources/Textures/MainMenuBackground.png"))
	{
		return false;
	}

	if (!m_inputsTexture.LoadFromFile(renderer, "Resources/Textures/Controls.png"))
	{
		return false;
	}
	return true;
}

bool MainMenu::CheckPointRectCollision(Rect& _rect, Point& _point)
{
	if (_point.X > _rect.X && _point.X < (_rect.X + static_cast<int>(_rect.m_Width)) &&
		_point.Y > _rect.Y && _point.Y < (_rect.Y + static_cast<int>(_rect.m_Height)))
	{
		return true;
	}
	return false;
}
