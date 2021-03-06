#include "elements.h"
#include "tetris.h"
#include "define.h"
#include <stdbool.h>


int world[M_Y][M_X] = { 0 };

bool tabShape[SHAPE][ROTATION][ROWS][COL] = {
	{
		// I shape
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 }, // 0
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 }, // 90
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 }, // 180
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 }, // 270
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 }
		}
	},

	{
		//  O shape
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 }, // 0 
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 }, // 90
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 }, // 180
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 }, // 270
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		// S shape
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},

	{
		// S-shape (orientation 2)
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		}
	},

	{
		// T-piece
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},

	{
		// L-piece (orientation 2)
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 1 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 1 },
			{ 0, 0, 0, 1 },
			{ 0, 0, 0, 0 }
		}
	},

	{
		// L-piece (orientation 1)
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		}

	}
};