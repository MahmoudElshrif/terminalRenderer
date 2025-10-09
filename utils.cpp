#include <vector>
#include <cstdint>
#include <chrono>

uint64_t timeSinceEpochMillisec()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

std::vector<double> add(std::vector<double> v1, std::vector<double> v2)
{
	for (int i = 0; i < v1.size(); i++)
	{
		v1[i] += v2[i];
	}

	return v1;
}