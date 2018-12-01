#ifndef JAMTEMPLATE_RANDOM_HPP_INCLUDEGUARD
#define JAMTEMPLATE_RANDOM_HPP_INCLUDEGUARD

#include <random>

namespace JamTemplate {

	class Random
	{
	public:
		Random() = delete;
		
		static int getInt(int min = 0, int max = 100);
		static float getFloat(float min = 0.0, float max = 1.0);
		static float getFloatGauss(float mu = 0, float sigma = 1);

	private:
		static std::default_random_engine m_engine;
		
	};
}
#endif
