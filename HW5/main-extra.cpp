#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include <algorithm>
#include <Eigen>

using namespace Eigen;

const int MAX_DEPTH = 5;

// image background color
Vector3f bgcolor(1.0f, 1.0f, 1.0f);

// lights in the scene
std::vector<Vector3f> lightPositions = { Vector3f(0.0, 60, 60)
									   , Vector3f(-60.0, 60, 60)
									   , Vector3f(60.0, 60, 60) };

class Sphere
{
public:
	Vector3f center;  // position of the sphere
	float radius;  // sphere radius
	Vector3f surfaceColor; // surface color
	bool specular; // boolean that determines whether a sphere has specular shading

	Sphere(
		const Vector3f& c,
		const float& r,
		const Vector3f& sc,
		const bool& spec) :
		center(c), radius(r), surfaceColor(sc), specular(spec)
	{
	}

	// line vs. sphere intersection (note: this is slightly different from ray vs. sphere intersection!)
	bool intersect(const Vector3f& rayOrigin, const Vector3f& rayDirection, float& t0, float& t1) const
	{
		Vector3f l = center - rayOrigin;
		float tca = l.dot(rayDirection);
		if (tca < 0) return false;
		float d2 = l.dot(l) - tca * tca;
		if (d2 > (radius * radius)) return false;
		float thc = sqrt(radius * radius - d2);
		t0 = tca - thc;
		t1 = tca + thc;

		return true;
	}
};

// diffuse reflection model
Vector3f diffuse(const Vector3f& L, // direction vector from the point on the surface towards a light source
	const Vector3f& N, // normal at this point on the surface
	const Vector3f& diffuseColor,
	const float kd // diffuse reflection constant
)
{
	Vector3f resColor = Vector3f::Zero();

	// TODO: implement diffuse shading model
	resColor = 0.333 * kd * std::max(L.dot(N), 0.f) * diffuseColor;

	return resColor;
}

// Phong reflection model
Vector3f phong(const Vector3f& L, // direction vector from the point on the surface towards a light source
	const Vector3f& N, // normal at this point on the surface
	const Vector3f& V, // direction pointing towards the viewer
	const Vector3f& diffuseColor,
	const Vector3f& specularColor,
	const float kd, // diffuse reflection constant
	const float ks, // specular reflection constant
	const float alpha) // shininess constant aka the Phong Exponent
{
	Vector3f resColor = Vector3f::Zero();

	// TODO: implement Phong shading model
	Vector3f reflection_vector = 2 * (L.dot(N)) * N - L;
	reflection_vector.normalize();
	// Phong Equation
	// PS = diffuse * kd + specular * ks * specular color
	// Specular Shadng  = (V * R) ^n
	resColor = diffuse(L, N, diffuseColor, kd) + ks * std::powf(std::max(reflection_vector.dot(V), 0.f), alpha) * specularColor * 0.333;
	return resColor;
}

// Blinn-Phong reflection model
Vector3f blinn_phong(const Vector3f& L, // direction vector from the point on the surface towards a light source
	const Vector3f& N, // normal at this point on the surface
	const Vector3f& V, // direction pointing towards the viewer
	const Vector3f& diffuseColor,
	const Vector3f& specularColor,
	const float kd, // diffuse reflection constant
	const float ks, // specular reflection constant
	const float alpha) // shininess constant aka the Phong Exponent
{
	Vector3f resColor = Vector3f::Zero();

	Vector3f reflection_vector = 2 * (L.dot(N)) * N - L;
	reflection_vector.normalize();
	// Phong Equation
	// PS = diffuse * kd + specular * ks * specular color
	// Specular Shadng  = (V * R) ^n
	float specular = 0.f;
	Vector3f half_direction = L + V;
	half_direction.normalize();
	float specular_angle = std::max(half_direction.dot(N), 0.f);
	specular = std::powf(specular_angle, ks);
	resColor = diffuse(L, N, diffuseColor, kd) + ks * std::powf(std::max(N.dot(half_direction), 0.f), alpha) * specularColor * 0.333 * specular;
	return resColor;
}

Vector3f trace(
	const Vector3f& rayOrigin,
	const Vector3f& rayDirection,
	const std::vector<Sphere>& spheres,
	int depth)
{
	Vector3f pixelColor = Vector3f::Zero();
	Vector3f hitPoint = Vector3f::Zero();
	Vector3f hitNormal = Vector3f::Zero();
	float t0; // corresponds to the the t0 for the sphere intersection
	float t1; // corresponds to the t1 for the sphere intersection
	bool hitObject = false;
	float minDistance = INFINITY;
	float sphereIndex = -1;
	// TODO: implement ray tracing as described in the homework description
	// iterate over the scene
	for (int i = 0; i < spheres.size(); i++)
	{
		bool raySphereIntersection = spheres[i].intersect(rayOrigin, rayDirection, t0, t1);
		if (raySphereIntersection)
		{
			hitObject = true;
			if (t0 < minDistance)
			{
				minDistance = t0;
				sphereIndex = i;
				hitPoint = rayOrigin + rayDirection * t0; // parametric equation for determing the point where the sphere was hit
				hitNormal = hitPoint - spheres[sphereIndex].center; // vector from the point of intersection to the center of the sphere
			}
		}
	}
	if (hitObject)
	{
		// Part 1: Color the Scene Red
		//pixelColor[0] = 1;
		//pixelColor[1] = 0;
		//pixelColor[2] = 0;

		// Part 1: Color the Scene according to the correct colors
		//pixelColor = spheres[sphereIndex].surfaceColor;

		for (int j = 0; j < lightPositions.size(); j++)
		{
			bool theShadow = false;
			float shadowt0; // t0 for the shadow
			float shadowt1; // t1 for the sahdow
			Vector3f shadowRayOrigin = hitPoint;
			Vector3f shadowRayDirection = lightPositions[j] - hitPoint;
			Vector3f eyeRay = -rayDirection;
			eyeRay.normalize();
			shadowRayDirection.normalize();
			hitNormal.normalize();
			for (int d = 0; d < spheres.size(); d++)
			{
				bool shadowIntersection = spheres[d].intersect(shadowRayOrigin, shadowRayDirection, shadowt0, shadowt1);
				if (shadowIntersection)
				{
					theShadow = true;
					break;
				}
			}
	
			if (!theShadow)
			{
				// Part 2: The Shadows
				//pixelColor += spheres[sphereIndex].surfaceColor * 0.333;

				// Part 3: Diffuse Shading
				//pixelColor += diffuse(shadowRayDirection, hitNormal, spheres[sphereIndex].surfaceColor, 1);

				// Part 3: Phong Shading
				pixelColor += phong(shadowRayDirection, hitNormal, eyeRay, spheres[sphereIndex].surfaceColor, Vector3f::Ones(), 1.f, 3.f, 100.f);

				//// Extra-Credit: Blinn-Phong Shading
				//pixelColor += blinn_phong(shadowRayDirection, hitNormal, eyeRay, spheres[sphereIndex].surfaceColor, Vector3f::Ones(), 1.f, 3.f, 100.f);
			}
		}
		depth = depth + 1;
		if (depth <= MAX_DEPTH)
		{
			Vector3f reflection_vector = rayDirection - 2 * rayDirection.dot(hitNormal.normalized()) * hitNormal.normalized();
			pixelColor = 0.5 * trace(hitPoint + hitNormal, reflection_vector.normalized(), spheres, depth);
		}
	}
	if (!hitObject)
	{
		pixelColor = bgcolor;
	}

	return pixelColor;
}

void render(const std::vector<Sphere>& spheres)
{
	unsigned width = 640;
	unsigned height = 480;
	Vector3f* image = new Vector3f[width * height];
	Vector3f* pixel = image;
	float invWidth = 1 / float(width);
	float invHeight = 1 / float(height);
	float fov = 30;
	float aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5f * fov / 180.f);

	// Trace rays
	for (unsigned y = 0; y < height; ++y)
	{
		for (unsigned x = 0; x < width; ++x)
		{
			float rayX = (2 * ((x + 0.5f) * invWidth) - 1) * angle * aspectratio;
			float rayY = (1 - 2 * ((y + 0.5f) * invHeight)) * angle;
			Vector3f rayDirection(rayX, rayY, -1);
			rayDirection.normalize();
			*(pixel++) = trace(Vector3f::Zero(), rayDirection, spheres, 0);
		}
	}

	// Save result to a PPM image
	std::ofstream ofs("./render.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (unsigned i = 0; i < width * height; ++i)
	{
		const float x = image[i](0);
		const float y = image[i](1);
		const float z = image[i](2);

		ofs << (unsigned char)(std::min(float(1), x) * 255)
			<< (unsigned char)(std::min(float(1), y) * 255)
			<< (unsigned char)(std::min(float(1), z) * 255);
	}

	ofs.close();
	delete[] image;
}

int main(int argc, char** argv)
{
	std::vector<Sphere> spheres;
	// position, radius, surface color
	spheres.push_back(Sphere(Vector3f(0.0, -10004, -20), 10000, Vector3f(1.f, 1.f, 1.f), true));
	spheres.push_back(Sphere(Vector3f(0.0, 0, -20), 4, Vector3f(1.00, 0.32, 0.36), true));
	spheres.push_back(Sphere(Vector3f(5.0, -1, -15), 2, Vector3f(0.90, 0.76, 0.46), true));
	spheres.push_back(Sphere(Vector3f(5.0, 0, -25), 3, Vector3f(0.65, 0.77, 0.97), true));
	spheres.push_back(Sphere(Vector3f(-5.5, 0, -13), 3, Vector3f(0.90, 0.90, 0.90), true));

	render(spheres);

	return 0;
}
