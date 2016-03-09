#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <glm.hpp>
#include "..\..\include\tokamak.h"

class Utility
{
public:
	static std::vector<std::string> Split(std::string str, char delemiter);
	static neV3 glmToNe(glm::vec3 v);
	static glm::vec3 neToGlm(neV3 v);
};

#endif // Utility



