#include "InGame.h"
#include "Pieces.h"
#include "SDLGraphics.h"
#include <windows.h>
#include "SDLText.h"

InGame::InGame()
{
	
	m_pActiveBoard = nullptr;
	m_bCreateNextPiece = false;
	m_bCopyInfo = false;
	m_iScore = 0;
	m_iLineMade = 0;
}


InGame::~InGame()
{
}

bool InGame::Initialize()
{
	if (!LoadResources())
	{
		return false;
	}

	m_iScore = 0;
	m_iLineMade = 0;
	m_backGround.X = 0;
	m_backGround.Y = 0;
	m_backGround.m_Width = SCREEN_WIDTH;
	m_backGround.m_Height = SCREEN_HEIGHT;

	//Create map color
	m_colorMap.insert(std::pair<BLOCKCOLOR, MPColor>(BC_NONE, MPColor(128, 128, 128)));
	m_colorMap.insert(std::pair<BLOCKCOLOR, MPColor>(BC_RED, MPColor(255, 0, 0)));
	m_colorMap.insert(std::pair<BLOCKCOLOR, MPColor>(BC_GREEN, MPColor(0, 255, 0)));
	m_colorMap.insert(std::pair<BLOCKCOLOR, MPColor>(BC_BLUE, MPColor(0, 0, 255)));

	//Create num of boards
	m_vecBoards.push_back(Board());
	m_vecBoards.push_back(Board());
	m_vecBoards.push_back(Board());

	//Set boards color
	BLOCKCOLOR board1Color = BC_RED;
	BLOCKCOLOR board2Color = BC_GREEN;
	BLOCKCOLOR board3Color = BC_BLUE;

	//Set boards position
	Point board1Position = Point(5, 10);
	Point board2Position = Point(20, 10);
	Point board3Position = Point(35, 10);

	//Create boards
	m_vecBoards.at(BOARD_1).Create(board1Color, board1Position);
	m_vecBoards.at(BOARD_2).Create(board2Color, board2Position);
	m_vecBoards.at(BOARD_3).Create(board3Color, board3Position);

	//Set active board
	m_iActiveBoard = BOARD_2;
	SetActiveBoard(m_vecBoards.at(m_iActiveBoard));

	//Create first piece
	BLOCKCOLOR piecesColor = BC_RED;
	PIECETYPE piecesType = PT_T;
	Point piecesInitPosition = Point(INIT_WORLD_PIECE_POSX, INIT_WORLD_PIECE_POSY);

	m_pieces.Create(piecesType, piecesColor, piecesInitPosition, *m_pActiveBoard->GetPos());

	//Set piece in the actual board
	m_vecBoards.at(BOARD_2).SetPiece(m_pieces);


	//Create Next Piece
	int randPiece = rand() % PT_TOTALNUM;
	int randColor = (rand() % BC_GREEN) + 1;

	PIECETYPE newPieceType = static_cast<PIECETYPE>(randPiece);
	BLOCKCOLOR newPieceColor = static_cast<BLOCKCOLOR>(randColor);
	Point nextPieceRenderPosition = Point(22, 3);
	Point worldPos = Point(0, 0);

	m_nextPieces.Create(newPieceType, newPieceColor, nextPieceRenderPosition, worldPos);

	//Set score data
	m_scoreColor = { 0,0,0 };
	m_strScore = "SCORE: ";
	m_strScore += std::to_string(m_iScore);

	//Lines made
	m_numLinesColor = { 0,0,0 };
	m_strlinesMade = "DELETE CHANCES: ";
	m_strlinesMade += std::to_string(m_iLineMade);
	
	return true;
}

void InGame::Update(float _deltaTime)
{
	static float elapsedTime = 0;
	elapsedTime += _deltaTime;

	m_pActiveBoard->Update();

	if (m_pActiveBoard->CheckGameOver())
	{
		m_bChangeWindow = true;
		return;
	}

	if (m_pActiveBoard->m_bLeftBoardCollision)
	{
		m_pActiveBoard->m_bLeftBoardCollision = false;
		m_pieces.m_position.X += 1;
	}

	if (m_pActiveBoard->m_bRightBoardCollision)
	{
		m_pActiveBoard->m_bRightBoardCollision = false;
		m_pieces.m_position.X -= 1;
	}

	if (m_pActiveBoard->m_bBelowBoardCollision)
	{
		m_pActiveBoard->m_bBelowBoardCollision = false;
		
		m_pieces.m_position.Y -= 1;
		m_pieces.SetIsActive(false);
		m_bCopyInfo = true;
	}

	if (m_pActiveBoard->m_bBelowCollision)
	{
		m_pActiveBoard->m_bBelowCollision = false;

		m_pieces.SetIsActive(false);
		m_bCopyInfo = true;

	}

	if (m_bCopyInfo)
	{
		CopyInfoToBoard();
		m_bCopyInfo = false;
	}

	//Put penalties
	if (m_pActiveBoard->m_bIncorrectPieceColor)
	{
		m_pActiveBoard->m_bIncorrectPieceColor = false;

		for (size_t i = 0; i < m_vecBoards.size(); ++i)
		{
			int numBoard = static_cast<int>(i);

			if (m_iActiveBoard != numBoard)
			{
				SetActiveBoard(m_vecBoards.at(i));
				m_pActiveBoard->PutPenalty(*m_vecBoards.at(m_iActiveBoard).GetBaseColor(), m_vecPenalties, numBoard);
			}
		}

		SetActiveBoard(m_vecBoards.at(m_iActiveBoard));
	}

	bool needsOtherCheck = true;
	while (needsOtherCheck)
	{
		needsOtherCheck = false;
		m_pActiveBoard->CheckLine();

		if (m_pActiveBoard->m_bDeletedLines)
		{
			m_pActiveBoard->m_bDeletedLines = false;
			int countLines = *m_pActiveBoard->GetCounteLines();
			UpdateScoreAndDeleteChances(countLines);
			m_pActiveBoard->ResetCounterLines();
			needsOtherCheck = true;
		}
	}

	CreatePieces();

	if (elapsedTime > 1000.0f)
	{
		m_pieces.Update();
		elapsedTime = 0.0f;
	}
}

void InGame::Render()
{
	SDL_Renderer* renderer = SDLGraphics::Instance().GetSDLRenderer();

	//Render background
	m_backGroundTexture.Render(m_backGround.X, m_backGround.Y, nullptr, m_backGround.m_Width, m_backGround.m_Height);

	//Rnder boards
	if (!m_vecBoards.empty())
	{
		for (size_t i = 0; i < m_vecBoards.size(); ++i)
		{
			m_vecBoards[i].Render(m_blockTexture, m_colorMap);
		}
	}
	
	//Render piece
	if (m_pieces.IsCreated())
	{
		m_pieces.Render(m_blockTexture, m_colorMap);
	}

	//Render Next Piece
	if (m_nextPieces.IsCreated())
	{
		m_nextPieces.Render(m_blockTexture, m_colorMap);
	}

	//Render Score
	m_strScore = "SCORE: ";
	m_strScore += std::to_string(m_iScore);
	SDLText::Instance().RenderSolidText(m_strScore, m_scoreColor, 800, 5, *renderer);

	//Render Lines Made
	m_strlinesMade = "DELETE CHANCES: ";
	m_strlinesMade += std::to_string(m_iLineMade);
	SDLText::Instance().RenderSolidText(m_strlinesMade, m_numLinesColor, 300, 5, *renderer);
}

void InGame::Destroy()
{
	m_pActiveBoard = nullptr;

	for (size_t i = 0; i < m_vecBoards.size(); ++i)
	{
		m_vecBoards[i].Destroy();
	}  

	m_vecPenalties.clear();
	m_vecBoards.clear();
	m_colorMap.clear();
	m_blockTexture.Free();
	m_iScore = 0;
}

void InGame::ManageInputs(SDL_Event& pEvent)
{
	if (pEvent.type == SDL_KEYDOWN)
	{
		//Move Left
		if (pEvent.key.keysym.sym == SDLK_LEFT)
		{
			if (m_pActiveBoard->CheckInputCollisions() == 2)
			{
				return;
			}
			else
			{
				m_pieces.m_position.X -= 1;
			}
			
		}

		//Move Right
		if (pEvent.key.keysym.sym == SDLK_RIGHT)
		{
			if (m_pActiveBoard->CheckInputCollisions() == 3)
			{
				return;
			}
			else
			{
				m_pieces.m_position.X += 1;
			}
			
		}
		if (pEvent.key.keysym.sym == SDLK_DOWN)
		{
			if (m_pieces.IsActive())
			{
				m_pieces.m_position.Y += 1;
			}
		}

		//Rotate Left
		if (pEvent.key.keysym.sym == SDLK_SPACE)
		{
			m_pieces.RotateLeft();
			if(m_pActiveBoard->CheckInputCollisions() == 1)
			{
				m_pieces.RotateRight();
			}
			
		}

		//Rotate Right
		if (pEvent.key.keysym.sym == SDLK_UP)
		{
			m_pieces.RotateRight();
			if (m_pActiveBoard->CheckInputCollisions() == 1)
			{
				m_pieces.RotateLeft();
			}
		}

		//Swap board to the left
		if (pEvent.key.keysym.sym == SDLK_q)
		{
			m_iActiveBoard -= 1;

			if (m_iActiveBoard >= BOARD_1)
			{
				SwapBoard(m_iActiveBoard);
				if (m_pActiveBoard->CheckInputCollisions() == 1)
				{
					m_iActiveBoard += 1;
					SwapBoard(m_iActiveBoard);
				}
			}
			else
			{
				m_iActiveBoard = BOARD_3;

				SwapBoard(m_iActiveBoard);

				if (m_pActiveBoard->CheckInputCollisions() == 1)
				{
					m_iActiveBoard = BOARD_3;
					SwapBoard(m_iActiveBoard);
				}
			}
		}
		//Swap board to the right
		if (pEvent.key.keysym.sym == SDLK_e)
		{
			m_iActiveBoard += 1;

			if (m_iActiveBoard < BOARD_TOTALNUM)
			{
				SwapBoard(m_iActiveBoard);

				if (m_pActiveBoard->CheckInputCollisions() == 1)
				{
					m_iActiveBoard -= 1;
					SwapBoard(m_iActiveBoard);
				}
			}
			else
			{
				m_iActiveBoard = BOARD_1;

				SwapBoard(m_iActiveBoard);
				if (m_pActiveBoard->CheckInputCollisions() == 1)
				{
					m_iActiveBoard = BOARD_1;
					SwapBoard(m_iActiveBoard);
				}
			}

		}

		//Delete penalty
		if (pEvent.key.keysym.sym == SDLK_w)
		{
			DeletePenalty();
		}
	}
}

void InGame::SetMousePos(Point _mousePos)
{
	_mousePos;
}

WindowState InGame::GetWindowChange()
{
	return WS_MAINMENU;
}

bool InGame::LoadResources()
{
	SDL_Renderer* renderer = SDLGraphics::Instance().GetSDLRenderer();

	if (!m_backGroundTexture.LoadFromFile(renderer, "Resources/Textures/InGameBackground.png"))
	{
		return false;
	}

	if (!m_blockTexture.LoadFromFile(renderer, "Resources/Textures/TetrisBlockBW.png"))
	{
		return false;
	}
	return true;
}


void InGame::SetActiveBoard(Board & _active)
{
	m_pActiveBoard = &_active;
}


void InGame::CopyInfoToBoard()
{
	Point tempBoardPos = *m_pActiveBoard->GetPos();
	int color = static_cast<int>(*m_pieces.GetColor());
	int boardColor = static_cast<int>(*m_pActiveBoard->GetBaseColor());
	int countRows = PIECE_ROWS - 1;
	int countPieceParts = 0;

	while (countRows > -1)
	{
		for (size_t j = 0; j < PIECE_COLUMS; j++)
		{
			if (m_pieces.m_matrix[countRows][j] != 0)
			{
				//If it is an incorrect piece 
				if (color != boardColor)
				{
					countPieceParts++;

					int worldPiecePosY = countRows + m_pieces.m_position.Y;
					int worldPiecePosX = static_cast<int>(j) + m_pieces.m_position.X;

					m_pActiveBoard->m_matrix[(worldPiecePosY - tempBoardPos.Y)][(worldPiecePosX - tempBoardPos.X)] = color;

					if (countPieceParts == 2)
					{
						m_pActiveBoard->m_bIncorrectPieceColor = true;
						return;
					}
				}
				else
				{
					int worldPiecePosY = countRows + m_pieces.m_position.Y;
					int worldPiecePosX = static_cast<int>(j) + m_pieces.m_position.X;

					m_pActiveBoard->m_matrix[(worldPiecePosY - tempBoardPos.Y)][(worldPiecePosX - tempBoardPos.X)] = color;
				}
			}
		}
		
		countRows--;
	}
}

void InGame::SwapBoard(int& _activeBoard)
{
	Point tempBoardPos = *m_pActiveBoard->GetPos();

	//Get piece movement
	Point pieceMovement;
	pieceMovement.X = m_pieces.m_position.X - tempBoardPos.X;
	pieceMovement.Y = m_pieces.m_position.Y - tempBoardPos.Y;

	SetActiveBoard(m_vecBoards.at(_activeBoard));

	tempBoardPos = *m_pActiveBoard->GetPos();

	//Add piece movement to board position
	m_pieces.SetWorldPos(tempBoardPos, pieceMovement);

	m_pActiveBoard->SetPiece(m_pieces);
}

void InGame::CreatePieces()
{
	if (m_pieces.IsActive() == false)
	{
		m_pieces = Pieces();
		if (m_iActiveBoard != BOARD_2)
		{
			m_iActiveBoard = BOARD_2;
			SetActiveBoard(m_vecBoards.at(m_iActiveBoard));
		}

		//Set world piece position to next piece
		Point piecesInitPosition = Point(INIT_WORLD_PIECE_POSX, INIT_WORLD_PIECE_POSY);
		m_nextPieces.SetWorldPos(*m_pActiveBoard->GetPos(), piecesInitPosition);
		m_pieces = m_nextPieces;

		//Set the next piece to actual board
		m_pActiveBoard->SetPiece(m_pieces);

		m_bCreateNextPiece = true;
	}

	if (m_bCreateNextPiece)
	{
		int randPiece = rand() % PT_TOTALNUM;
		int randColor = (rand() % BC_GREEN) + 1;

		PIECETYPE newPieceType = static_cast<PIECETYPE>(randPiece);
		BLOCKCOLOR newPieceColor = static_cast<BLOCKCOLOR>(randColor);
		Point nextPieceRenderPosition = Point(22, 3);
		Point worldPos = Point(0, 0);

		m_nextPieces.Create(newPieceType, newPieceColor, nextPieceRenderPosition, worldPos);

		m_bCreateNextPiece = false;
	}
}

void InGame::DeletePenalty()
{
	//If there isn't penalties
	if (m_vecPenalties.empty() || m_iLineMade == 0)
	{
		return;
	}

	//Random penalty erasing
	if (m_vecPenalties.size() > 1)
	{
		//Change number of lines made
		m_iLineMade -= 1;

		//Get random penalty
		int randPenalty = rand() % m_vecPenalties.size();

		//Swap to the board
		SwapBoard(m_vecPenalties.at(randPenalty).board);

		//Delete penalty
		FallColumn(m_vecPenalties.at(randPenalty).pos);

		//Check for new lines
		m_pActiveBoard->CheckLine();

		if (m_pActiveBoard->m_bDeletedLines)
		{
			m_pActiveBoard->m_bDeletedLines = false;
			int countLines = *m_pActiveBoard->GetCounteLines();
			UpdateScoreAndDeleteChances(countLines);
			m_pActiveBoard->ResetCounterLines();
		}

		//Erase penalty of the list
		m_vecPenalties.erase(m_vecPenalties.begin() + randPenalty);

		//return to the past board
		SwapBoard(m_iActiveBoard);
	}
	else //There is just one penalty
	{
		//Change number of lines made
		m_iLineMade -= 1;

		//Swap to the board
		SwapBoard(m_vecPenalties.at(0).board);

		//Delete penalty
		FallColumn(m_vecPenalties.at(0).pos);

		//Check for new lines
		m_pActiveBoard->CheckLine();

		if (m_pActiveBoard->m_bDeletedLines)
		{
			m_pActiveBoard->m_bDeletedLines = false;
			int countLines = *m_pActiveBoard->GetCounteLines();
			UpdateScoreAndDeleteChances(countLines);
			m_pActiveBoard->ResetCounterLines();
		}

		//Erase penalty of the list
		m_vecPenalties.erase(m_vecPenalties.begin());

		//return to the past board
		SwapBoard(m_iActiveBoard);
	}
}


void InGame::FallColumn(Point& _penaltyPos)
{
	int initRow = _penaltyPos.Y;

	//Inverse iteration that starts in the delete penalty row
	while (initRow > 0)
	{
		m_pActiveBoard->m_matrix[initRow][_penaltyPos.X] = m_pActiveBoard->m_matrix[initRow - 1][_penaltyPos.X];
		initRow--;
	}
}

void InGame::UpdateScoreAndDeleteChances(int _num)
{
	m_iScore += (_num * 10);
	m_iLineMade += _num;
}
