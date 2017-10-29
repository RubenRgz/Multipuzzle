#include "Board.h"

Board::Board()
{
	m_position.X = 0;
	m_position.Y = 0;
	m_iLinesCounter = 0;
	m_bDeletedLines = false;
	m_pPiece = nullptr;
	m_bIncorrectPieceColor = false;
	m_bLeftBoardCollision = false;
	m_bRightBoardCollision = false;
	m_bBelowBoardCollision = false;
	m_bBelowCollision = false;
	m_bTopCollision = false;
}


Board::~Board()
{
}

void Board::Create(BLOCKCOLOR& _color, Point& _position)
{
	m_color = _color;
	m_position = _position;

	for (size_t i = 0; i < BOARD_ROWS; ++i)
	{
		for (size_t j = 0; j < BOARD_COLUMS; ++j)
		{
			m_matrix[i][j] = 0;
		}
	}
}

BLOCKCOLOR* Board::GetBaseColor()
{
	return &m_color;
}

Point* Board::GetPos()
{
	return &m_position;
}

void Board::Update()
{
	CheckGameCollisions();
}

void Board::Render(Texture& _texture, std::map<BLOCKCOLOR, MPColor>& _colorMap)
{
	for (size_t i = 0; i < BOARD_ROWS; ++i)
	{
		for (size_t j = 0; j < BOARD_COLUMS; ++j)
		{
			MPColor blockColor = _colorMap.find(static_cast<BLOCKCOLOR>(m_matrix[i][j]))->second;
			_texture.SetColor(static_cast<char>(blockColor.r), static_cast<char>(blockColor.g), static_cast<char>(blockColor.b));
			_texture.Render((m_position.X + j) * BLOCK_SIZE, (m_position.Y + i) * BLOCK_SIZE, nullptr, BLOCK_SIZE, BLOCK_SIZE);
		}
	}
}

void Board::Destroy()
{
	m_pPiece = nullptr;
}

bool Board::CheckGameCollisions()
{
	int countRows = PIECE_ROWS - 1;

	while (countRows > -1)
	{
		for (size_t j = 0; j < PIECE_COLUMS; ++j)
		{
			//Is is a valid piece position
			if (m_pPiece->m_matrix[countRows][j] != 0)
			{
				//Establish Y and X position in the board
				int worldPiecePosY = countRows + m_pPiece->m_position.Y;
				int worldPiecePosX = j + m_pPiece->m_position.X;

				//if th position is greater than board width
				if (worldPiecePosX >= BOARD_COLUMS + m_position.X)
				{
					m_bRightBoardCollision = true;
					return true;

				}
				if (worldPiecePosX < 0 + m_position.X)
				{
					m_bLeftBoardCollision = true;
					return true;
				}

				//if th position is greater than board height
				if (worldPiecePosY >= BOARD_ROWS + m_position.Y)
				{
					m_bBelowBoardCollision = true;
					return true;
				}

				if (worldPiecePosY < m_position.Y)
				{
					m_bTopCollision = true;
					return true;
				}

				//If there is something below in the board matrix
				if (m_matrix[(worldPiecePosY - m_position.Y) + 1][(worldPiecePosX - m_position.X)] != 0)
				{
					m_bBelowCollision = true;
					return true;
				}
			}
		}
		countRows--;
	}
	return false;
}

void Board::CheckLine()
{
	int columCount = 0;

	//inverse iteration
	int countRows = BOARD_ROWS - 1;

	while (countRows > -1)
	{
		for (size_t j = 0; j < BOARD_COLUMS; ++j)
		{
			if (m_matrix[countRows][j] == m_color)
			{
				columCount++;
			}
		}

		if (columCount == BOARD_COLUMS)
		{
			//Delete a column
			DeleteLine(countRows);

			//Count lines to erase penalties
			m_iLinesCounter += 1;
			m_bDeletedLines = true;
		}

		columCount = 0;
		countRows--;
	}
}

void Board::DeleteLine(int _initRow)
{
	//Inverse iteration that starts in the delete row
	while (_initRow > 0)
	{
		//Delete a line of the board by moving all above lines down
		for (size_t j = 0; j < BOARD_COLUMS; ++j)
		{
			m_matrix[_initRow][j] = m_matrix[_initRow - 1][j];
		}
		_initRow--;
	}
}

void Board::ResetCounterLines()
{
	m_iLinesCounter = 0;
}

int * Board::GetCounteLines()
{
	return &m_iLinesCounter;
}

bool Board::CheckGameOver()
{
	for (size_t j = 0; j < BOARD_ROWS; j++)
	{
		if (m_matrix[0][j] != 0)
		{
			return true;
		}
	}
	return false;
}

void Board::PutPenalty(BLOCKCOLOR& _color, std::vector<Penalty>& _vecPenalties,
						int& _activeBoatd)
{
	//Pick a random column
	int randColumn = rand() % BOARD_COLUMS;

	//Search the first deep empty space in that row
	int countRows = BOARD_ROWS - 1;

	while (countRows > -1)
	{
		if (m_matrix[countRows][randColumn] == 0)
		{
			m_matrix[countRows][randColumn] = static_cast<int>(_color);

			//Add to penalties
			Penalty tempPenaltyPos;
			tempPenaltyPos.board = _activeBoatd;
			tempPenaltyPos.pos = Point(randColumn, countRows);

			_vecPenalties.push_back(tempPenaltyPos);
			return;
		}
		countRows--;
	}
}

int Board::CheckInputCollisions()
{
	for (size_t i = 0; i < PIECE_ROWS; ++i)
	{
		for (size_t j = 0; j < PIECE_COLUMS; ++j)
		{
			if (m_pPiece->m_matrix[i][j] != 0)
			{
				int worldPiecePosY = (i + m_pPiece->m_position.Y) - m_position.Y;
				int worldPiecePosX = (j + m_pPiece->m_position.X) - m_position.X;

				//Actual pos collision
				if (m_matrix[worldPiecePosY][worldPiecePosX] != 0)
				{
					return 1;
				}

				//Left collision
				if (m_matrix[worldPiecePosY][worldPiecePosX - 1] != 0)
				{
					return 2;
				}

				//Right collision
				if (m_matrix[worldPiecePosY][worldPiecePosX + 1] != 0)
				{
					return 3;
				}

			}
		}
	}

	return 0;
}

void Board::SetPiece(Pieces & _piece)
{
	m_pPiece = &_piece;
}
