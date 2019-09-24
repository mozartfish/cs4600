

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Vertical Lines (Top Down)
void verticalLinesTopDown(int x1, int y1, int scaleX, int scaleY)
{
	int oldTempX1, oldTempY1;

	oldTempX1 = x1;
	oldTempY1 = y1;

	// Reflect Across Y axis
	x1 = -x1;

	// Map to Screen Coordinates
	x1 = x1 + scaleX;
	y1 = y1 + scaleY;

	// Swap Coordinates

	int tempX1 = x1;
	x1 = y1;
	y1 = tempX1;


	//std::cout << x1 << ", " << y1 << std::endl;

	putPixel(x1, y1);
}

// Function that maps Cartesian Coordinate System to Screen Coordinate System for Vertical Lines (Bottom Up)
//void verticalLinesBottomUp(int x1, int y1, int scaleX, int scaleY)
//{
//	int oldTempX1, oldTempY1;
//
//	oldTempX1 = x1;
//	oldTempY1 = y1;
//
//	 Map to Screen Coordinates
//	x1 = x1 + scaleX;
//	y1 = y1 + scaleY;
//
//	 Swap Coordinates
//
//	int tempX1 = x1;
//	x1 = y1;
//	y1 = tempX1;
//
//	std::cout << x1 << ", " << y1 << std::endl;
//	putPixel(x1, y1);
//}















	







	// Vertical Line Case (Top Down)
	if (x1 == x2 && y2 < y1 && std::abs(x2 - x1) < std::abs(y2 - y1))
	{
		std::cout << "Vertical Line Case (Top Down)" << std::endl;

		int tempX1, tempY1, tempX2, tempY2, scaleX, scaleY;

		// Swap Coordinates
		tempX1 = x1;
		tempY1 = y1;
		tempX2 = x2;
		tempY2 = y2;

		x1 = y1;
		y1 = tempX1;
		x2 = y2;
		y2 = tempX2;

		// Set Mapping to Cartesian Coordinates
		scaleX = x1;
		scaleY = y1;

		// Map to Cartesian Coordinates
		x1 = x1 - scaleX;
		y1 = y1 - scaleY;
		x2 = x2 - scaleX;
		y2 = y2 - scaleY;

		// Reflect Across the Y axis
		x2 = -x2;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(tempX1, tempY1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			verticalLinesTopDown(x1, y1, scaleX, scaleY);
		}
	}

	// Vertical Line Case (Bottom Up)
	if (x1 == x2 && y1 < y2 && std::abs(x2 - x1) < std::abs(y2 - y1))
	{
		std::cout << "Vertical Line Case (Bottom Up)" << std::endl;
		int tempX1, tempY1, tempX2, tempY2, scaleX, scaleY;

		// Swap Coordinates
		tempX1 = x1;
		tempY1 = y1;
		tempX2 = x2;
		tempY2 = y2;

		x1 = y1;
		y1 = tempX1;
		x2 = y2;
		y2 = tempX2;

		// Set Mapping to Cartesian Coordinates
		scaleX = x1;
		scaleY = y1;

		// Map to Cartesian Coordinates
		x1 = x1 - scaleX;
		y1 = y1 - scaleY;
		x2 = x2 - scaleX;
		y2 = y2 - scaleY;

		// Reflect Across the Y axis
		x2 = -x2;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(tempX1, tempY1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			verticalLinesTopDown(x1, y1, scaleX, scaleY);
		}

	}

	// Horizontal Lines Case (Left Right)
	if (x1 < x2 && y1 == y2 && std::abs(x2 - x1) >(std::abs(y2 - y1)))
	{
		std::cout << "Horizontal Line Case (Left Right)" << std::endl;
		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(x1, y1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			putPixel(x1, y1);
		}
	}

	// Horizontal Line Case (Right to Left)
	if (x1 > x2 && y1 == y2 && std::abs(x2 - x1) > std::abs(y2 - y1))
	{
		std::cout << "Horizontal Line Case (Right to Left)" << std::endl;

		int tempX1 = x1;
		x1 = x2;
		x2 = tempX1;

		int dx, dy, D, inc0, inc1;

		dx = x2 - x1;
		dy = y2 - y1;
		D = 2 * dy - dx;
		inc0 = 2 * dy;
		inc1 = 2 * (dy - dx);
		putPixel(x1, y1);

		while (x1 < x2)
		{
			if (D <= 0)
			{
				D = D + inc0;
			}
			else
			{
				D = D + inc1;
				y1 = y1 + 1;
			}
			x1 = x1 + 1;
			putPixel(x1, y1);
		}
	}

