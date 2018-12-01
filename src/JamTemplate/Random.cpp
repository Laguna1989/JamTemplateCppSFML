#include "Random.hpp"

using namespace JamTemplate;

std::default_random_engine Random::m_engine;

int Random::getInt(int min , int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(m_engine);
}

float Random::getFloat(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(m_engine);
}

float Random::getFloatGauss(float mu, float sigma )
{
	std::normal_distribution<float> dist(mu,sigma);
	return dist(m_engine);
}