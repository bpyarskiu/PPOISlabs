#include "CalculateCentralityAgent.hpp"
#include "keynodes/Keynodes2.hpp"
#include "utils/utils.hpp"
#include <sc-memory/sc_memory.hpp>
#include <algorithm>

using namespace economic_ecosystem;

ScAddr CalculateCentralityAgent::GetActionClass() const
{
  return Keynodes::action_calculate_centrality;
}

ScResult CalculateCentralityAgent::DoProgram(ScAction & action)
{
  // 1. Извлечение аргументов через структурированный подход
  auto const & [argsAddr] = action.GetArguments<1>();
  
  if (!m_context.IsElement(argsAddr))
  {
    SC_LOG_ERROR("Action has no arguments structure");
    return action.FinishWithError();
  }
  
  // Используем утилиту для извлечения аргументов 
  ScAddr const company = resolve_arg(m_context, argsAddr, Keynodes::rrel_1);
  
  if (!company.IsValid())
  {
    SC_LOG_ERROR("Company argument is invalid or missing");
    return action.FinishWithError();
  }
  

  ScAddrVector relationTypes = {
    Keynodes::nrel_agreement_contract,
    Keynodes::nrel_agreement_supplies,
    Keynodes::nrel_agreement_credit
  };
  
  int totalConnections = 0;
  std::set<ScAddr, ScAddrLessFunc> uniquePartners;
  int diversityScore = 0;
  
  // 2. Анализ всех типов отношений
  for (const auto& relType : relationTypes)
  {
    bool typeUsed = false;
    
    // Исходящие связи (компания -> партнер)
    ScIterator5Ptr itOut = m_context.CreateIterator5(
      company,
      ScType::ConstCommonArc,
      ScType::ConstNode,
      ScType::ConstPermPosArc,
      relType
    );
    
    while (itOut->Next())
    {
      ScAddr partner = itOut->Get(2);
      totalConnections++;
      uniquePartners.insert(partner);
      typeUsed = true;
    }
    
    // Входящие связи (партнер -> компания)
    ScIterator5Ptr itIn = m_context.CreateIterator5(
      ScType::ConstNode,
      ScType::ConstCommonArc,
      company,
      ScType::ConstPermPosArc,
      relType
    );
    
    while (itIn->Next())
    {
      ScAddr partner = itIn->Get(0);
      totalConnections++;
      uniquePartners.insert(partner);
      typeUsed = true;
    }
    
    if (typeUsed) diversityScore++;
  }
  
  // 3. Определение центральности (адаптивный порог)
  int uniqueConnections = uniquePartners.size();
  bool isCentral = false;
  
  // Критерий: много связей И/ИЛИ разнообразие типов
  if (totalConnections >= 5 || uniqueConnections >= 4 || diversityScore >= 2)
  {
    isCentral = true;
    
    // 4. Создание результата
    ScStructure result = m_context.GenerateStructure();
    
    // Добавляем компанию
    result << company;
    
    // Создаем связь "является центральной компанией"
    ScAddr edge = m_context.GenerateConnector(
      ScType::ConstPermPosArc,
      Keynodes::concept_central_company,
      company
    );
    
    result << edge << Keynodes::concept_central_company;
    
    // Добавляем метрики как атрибуты
    ScAddr metrics = m_context.GenerateNode(ScType::ConstNode);
    
    m_context.GenerateConnector(ScType::ConstPermPosArc, metrics, totalConnections);
    m_context.GenerateConnector(ScType::ConstPermPosArc, metrics, uniqueConnections);
    m_context.GenerateConnector(ScType::ConstPermPosArc, metrics, diversityScore);
    m_context.GenerateConnector(ScType::ConstPermPosArc, company, metrics);
    
    result << metrics << totalConnections << uniqueConnections << diversityScore;
    
    action.SetResult(result);
    
    SC_LOG_INFO("Company identified as central: " 
                << m_context.GetElementSystemIdentifier(company)
                << " | Total: " << totalConnections
                << " | Unique: " << uniqueConnections
                << " | Diversity: " << diversityScore);
  }
  else
  {
    SC_LOG_DEBUG("Company is not central: " 
                 << m_context.GetElementSystemIdentifier(company)
                 << " | Total: " << totalConnections
                 << " | Unique: " << uniqueConnections);
  }
  
  return action.FinishSuccessfully();
}