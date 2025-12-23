#pragma once

#include <sc-memory/sc_agent.hpp>

namespace economic_ecosystem
{

class CalculateCentralityAgent : public ScActionInitiatedAgent
{
public:
  ScAddr GetActionClass() const override;
  ScResult DoProgram(ScAction & action) override;
};

}
