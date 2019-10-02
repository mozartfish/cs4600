	// The Boiler Plate code from the professor

		
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



		// Calculate the distance between y coordinates
		int distance = y1 - y2;

		int tempY = y2;

		y2 = y1 + distance;


		int dx, dy, D, inc0, inc1, yk;
		yk = y1;
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
			putPixel(x1, 2 * yk - y1);
		}

		//// Calculate the distance between y coordinates
		//int distance = y1 - y2;

		//int tempY = y2;

		//y2 = y1 + distance;


		//int dx, dy, D, inc0, inc1, yk;
		//yk = y1;
		//dx = x2 - x1;
		//dy = y2 - y1;
		//D = 2 * dy - dx;
		//inc0 = 2 * dy;
		//inc1 = 2 * (dy - dx);
		//putPixel(x1, y1);

		//while (x1 < x2)
		//{
		//	if (D <= 0)
		//	{
		//		D = D + inc0;
		//	}
		//	else
		//	{
		//		D = D + inc1;
		//		y1 = y1 + 1;
		//	}
		//	x1 = x1 + 1;
		//	putPixel((2 * yk - y1), x1);
		//}
