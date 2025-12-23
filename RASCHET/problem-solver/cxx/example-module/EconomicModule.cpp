#include "EconomicModule.hpp"
#include "agents/FindConnectedComponentsAgent.hpp"
#include "agents/CalculateCentralityAgent.hpp"

using namespace economic_ecosystem;

SC_MODULE_REGISTER(EconomicModule)
  ->Agent<FindConnectedComponentsAgent>()
  ->Agent<CalculateCentralityAgent>();
