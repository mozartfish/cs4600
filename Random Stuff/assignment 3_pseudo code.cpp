	// print the size of all the vectors
	std::cout << "The size of meshNormals is: " << g_meshNormals.size() / 3 << std::endl;
	std::cout << "The size of meshIndices is: " << g_meshIndices.size() / 3 << std::endl;
	std::cout << "The size of meshVertices is: " << g_meshVertices.size() / 3 << std::endl;

	for (int i = 0; i <= g_meshIndices.size() - 3; i++)
	{
		// select points three at a time
		int p1= i;
		int p2 = i + 1;
		int p3 = i + 2;

		// determine the mesh indices for mapping
	/*	std::cout << "Mesh Indices" << std::endl;
		unsigned int& p1Index = g_meshIndices[5];
		std::cout << "The index of P1 is: " << p1Index << std::endl;*/

	/*	std::cout << "Index 1: " << g_meshIndices[i] << std::endl;
		std::cout << "Index 2: " << g_meshIndices[i + 1] << std::endl;
		std::cout << "Index 3: " << g_meshIndices[i + 2] << std::endl;*/


		// determine the coordinates for p1
		float p1X = g_meshVertices[3 * p1 + 0];
		float p1Y = g_meshVertices[3 * p1 + 1];
		float p1Z = g_meshVertices[3 * p1 + 2];

		std::cout << 3 * p1 + 0 << std::endl;
		std::cout << 3 * p1 + 1 << std::endl;
		std::cout << 3 * p1 + 2 << std::endl;

		// print the p1 coordinates
		//std::cout << "p1 X coordinate: " << p1X << std::endl;
		//std::cout << "p1 Y coordinate: " << p1Y << std::endl;
		//std::cout << "p1 Z coordinate: " << p1Z << std::endl;

		// determine the coordinates for p2
		float p2X = g_meshVertices[3 * p2 + 0];
		float p2Y = g_meshVertices[3 * p2 + 1];
		float p2Z = g_meshVertices[3 * p2 + 2];

		// print the p2 coordinates
		//std::cout << "p2 X coordinate: " << p2X << std::endl;
		//std::cout << "p2 Y coordinate: " << p2Y << std::endl;
		//std::cout << "p2 Z coordinate: " << p2Z << std::endl;



		// determine the coordinates for p3
		float p3X = g_meshVertices[3 * p3 + 0];
		float p3Y = g_meshVertices[3 * p3 + 1];
		float p3Z = g_meshVertices[3 * p3 + 2];

		//// print the p3 coordinates
		//std::cout << "p3 X coordinate: " << p3X << std::endl;
		//std::cout << "p3 Y coordinate: " << p3Y << std::endl;
		//std::cout << "p3 Z coordinate: " << p3Z << std::endl;

		// compute the vectors for use in the cross product
		// let the vector from P1 to P2 be PQ
		float pqX = p2X - p1X;
		float pqY = p2Y - p1Y;
		float pqZ = p2Z - p1Z;

		// print the coordinates of vector PQ
		//std::cout << "PQ X coordinate: " << pqX << std::endl;
		//std::cout << "PQ Y coordinate: " << pqY << std::endl;
		//std::cout << "PQ Z coordinate: " << pqZ << std::endl;

		// let the vector from P1 to P3 be PR
		float prX = p3X - p1X;
		float prY = p3Y - p1Y;
		float prZ = p3Z - p1Z;

		// print the coordinates for vector PR
		//std::cout << "PR X coordinate: " << prX << std::endl;
		//std::cout << "PR Y coordinate: " << prY << std::endl;
		//std::cout << "PR Z coordinate: " << prZ << std::endl;

		// compute the cross product for vectors PQ and PR
		float cross_product_I = 1 * ((pqY * prZ) - (pqZ * prY));
		float cross_product_J = -1 * ((pqX * prZ) - (pqZ * prX));
		float cross_product_K = 1 * ((pqX * prY) - (pqY * prX));

		// print the coordinates of the normal vector
		//std::cout << "The i coordinate to PQ and PR: " << cross_product_I << std::endl;
		//std::cout << "The j coordinate to PQ and PR: " << cross_product_J << std::endl;
		//std::cout << "The k coordinate coordinate to PQ and PR: " << cross_product_K << std::endl;

		// normalize the normal vector
		float two_norm = std::sqrt(std::pow(cross_product_I, 2) + std::pow(cross_product_J, 2) + std::pow(cross_product_K, 2));

		// normalize components
		float unit_X = cross_product_I / two_norm;
		float unit_Y = cross_product_J / two_norm;
		float unit_Z = cross_product_K / two_norm;

		// Check the normalized components
		//float unit_vector = std::sqrt(std::pow(unit_X, 2) + std::pow(unit_Y, 2) + std::pow(unit_Z, 2));
		//std::cout << "The unit vector result is: " << unit_vector << std::endl;

		//break;
	}
