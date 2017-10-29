#include "Pieces.h"

//Matrices of all Pieces 
int iTP_SQUARE[4][25] =
{
	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,0,1,1,0,
	 0,0,1,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,0,1,1,0,
	 0,0,1,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,0,1,1,0,
	 0,0,1,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,0,1,1,0,
	 0,0,1,1,0,
	 0,0,0,0,0}
};

int iTP_LINE[4][25] =
{
	{ 0,0,0,0,0,
	0,0,0,0,0,
	0,1,1,1,1,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,0,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0,
	0,0,1,0,0 },

	{ 0,0,0,0,0,
	0,0,0,0,0,
	1,1,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0 },

	{ 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0 }
};

int iTP_L[4][25] =
{
	{0,0,0,0,0,
	 0,1,0,0,0,
	 0,1,0,0,0,
	 0,1,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,1,0,
	 0,1,0,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,1,0,
	 0,0,0,1,0,
	 0,0,0,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,0,0,1,0,
	 0,1,1,1,0,
	 0,0,0,0,0}
};

int iTP_L_MIRRORED[4][25] =
{
	{0,0,0,0,0,
	 0,0,0,1,0,
	 0,0,0,1,0,
	 0,0,1,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,0,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,1,0,0,0,
	 0,1,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,0,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0}
};

int iTP_N[4][25] =
{
	{0,0,0,0,0,
	 0,0,0,1,0,
	 0,0,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,1,0,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,1,0,0,
	 0,0,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0}
};

int iTP_N_MIRRORED[4][25] =
{
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,1,0,
	 0,0,0,1,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,0,1,1,0,
	 0,1,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,1,0,0,0,
	 0,1,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,1,0,
	 0,1,1,0,0,
	 0,0,0,0,0,
	 0,0,0,0,0}
};

int iTP_T[4][25] =
{
	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,0,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,0,0,0,
	 0,1,1,1,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,0,0,
	 0,0,1,0,0,
	 0,0,0,0,0},

	{0,0,0,0,0,
	 0,0,1,0,0,
	 0,1,1,1,0,
	 0,0,0,0,0,
	 0,0,0,0,0}
};



Pieces::Pieces()
{
	m_bActive = false;
	m_bIsCreated = false;
}


Pieces::~Pieces()
{
}

int Pieces::m_rotatePos = 0;

void Pieces::Create(PIECETYPE& _type, BLOCKCOLOR& _color, Point& _initPos, Point& _worldPos)
{
	m_color = _color;
	m_position.X = _worldPos.X +_initPos.X;
	m_position.Y = _worldPos.Y + _initPos.Y;

	switch (_type)
	{
	case PT_SQUARE:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				//Set initial orientetion
				m_matrix[i][j] = iTP_SQUARE[PO_0][(i * 5) + j];
			}
		}
		m_type = _type;
		break;
	case PT_LINE:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				//Set initial orientetion
				m_matrix[i][j] = iTP_LINE[PO_0][(i * 5) + j];
			}
		}
		m_type = _type;
		break;
	case PT_L:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				//Set initial orientetion
				m_matrix[i][j] = iTP_L[PO_0][(i * 5) + j];
			}
		}
		m_type = _type;
		break;
	case PT_L_MIRRORED:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				//Set initial orientetion
				m_matrix[i][j] = iTP_L_MIRRORED[PO_0][(i * 5) + j];
			}
		}
		m_type = _type;
		break;
	case PT_N:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				//Set initial orientetion
				m_matrix[i][j] = iTP_N[PO_0][(i * 5) + j];
			}
		}
		m_type = _type;
		break;
	case PT_N_MIRRORED:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				//Set initial orientetion
				m_matrix[i][j] = iTP_N_MIRRORED[PO_0][(i * 5) + j];
			}
		}
		m_type = _type;
		break;
	case PT_T:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				//Set initial orientetion
				m_matrix[i][j] = iTP_T[PO_0][(i * 5) + j];
			}
		}
		m_type = _type;
		break;
	default:
		break;
	}
	m_bIsCreated = true;
	m_bActive = true;
}

void Pieces::RotateLeft()
{
	m_rotatePos++;

	if (m_rotatePos > 3)
	{
		m_rotatePos = 0;
	}

	switch (m_type)
	{
	case PT_SQUARE:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_SQUARE[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_LINE:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_LINE[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_L:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_L[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_L_MIRRORED:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_L_MIRRORED[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_N:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_N[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_N_MIRRORED:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_N_MIRRORED[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_T:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_T[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	default:
		break;
	}
}

void Pieces::RotateRight()
{
	m_rotatePos--;

	if (m_rotatePos < 0)
	{
		m_rotatePos = 3;
	}

	switch (m_type)
	{
	case PT_SQUARE:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_SQUARE[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_LINE:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_LINE[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_L:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_L[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_L_MIRRORED:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_L_MIRRORED[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_N:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_N[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_N_MIRRORED:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_N_MIRRORED[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	case PT_T:
		for (size_t i = 0; i < PIECE_ROWS; ++i)
		{
			for (size_t j = 0; j < PIECE_COLUMS; ++j)
			{
				m_matrix[i][j] = iTP_T[m_rotatePos][(i * 5) + j];
			}
		}
		break;
	default:
		break;
	}
}

bool Pieces::IsCreated()
{
	return m_bIsCreated;
}

void Pieces::Update()
{
	if (m_bActive)
	{
		m_position.Y += 1;
	}
	
}

void Pieces::Render(Texture& _texture, std::map<BLOCKCOLOR, MPColor>& _colorMap)
{
	for (size_t i = 0; i < PIECE_ROWS; ++i)
	{
		for (size_t j = 0; j < PIECE_COLUMS; ++j)
		{
			if (m_matrix[i][j] != 0)
			{
				MPColor pieceColor = _colorMap.find(m_color)->second;
				_texture.SetColor(static_cast<char>(pieceColor.r), static_cast<char>(pieceColor.g), static_cast<char>(pieceColor.b));
				_texture.Render((m_position.X + j) * BLOCK_SIZE, (m_position.Y + i) * BLOCK_SIZE, nullptr, BLOCK_SIZE, BLOCK_SIZE);
			}
		}
	}
}

void Pieces::Destroy()
{
}

BLOCKCOLOR* Pieces::GetColor()
{
	return &m_color;
}

PIECETYPE * Pieces::GetType()
{
	return &m_type;
}

bool Pieces::IsActive()
{
	return m_bActive;
}

void Pieces::SetIsActive(bool _active)
{
	m_bActive = _active;
}

void Pieces::SetWorldPos(Point& _boardPos, Point& _movementPice)
{
	m_position.X = _movementPice.X + _boardPos.X;
	m_position.Y = _movementPice.Y + _boardPos.Y;
}
