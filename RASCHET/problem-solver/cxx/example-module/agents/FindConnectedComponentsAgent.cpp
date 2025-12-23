#include "FindConnectedComponentsAgent.hpp"
#include "keynodes/Keynodes2.hpp"
#include "utils/utils.hpp"
#include <sc-memory/sc_memory.hpp>
#include <queue>
#include <set>
#include <vector>

using namespace economic_ecosystem;

ScAddr FindConnectedComponentsAgent::GetActionClass() const
{
  return Keynodes::action_find_connected_components;
}

ScResult FindConnectedComponentsAgent::DoProgram(ScAction & action)
{
  // 1. Извлечение аргументов
  auto const & [argsAddr] = action.GetArguments<1>();
  
  if (!m_context.IsElement(argsAddr))
  {
    SC_LOG_ERROR("Action has no arguments structure");
    return action.FinishWithError();
  }
  
  ScAddr const startCompany = resolve_arg(m_context, argsAddr, Keynodes::rrel_1);
  
  if (!startCompany.IsValid())
  {
    SC_LOG_ERROR("Start company argument is invalid");
    return action.FinishWithError();
  }
  
  // 2. BFS для поиска компоненты связности
  std::set<ScAddr, ScAddrLessFunc> visited;
  std::queue<ScAddr> queue;
  std::vector<ScAddr> component;
  
  queue.push(startCompany);
  visited.insert(startCompany);
  
  SC_LOG_DEBUG("Starting BFS from company: " 
               << m_context.GetElementSystemIdentifier(startCompany));
  
  // 3. Обход графа
  while (!queue.empty())
  {
    ScAddr current = queue.front();
    queue.pop();
    component.push_back(current);
    
    // Перечень типов отношений для анализа
    ScAddrVector relationTypes = {
      Keynodes::nrel_agreement_contract,
      Keynodes::nrel_agreement_supplies,
      Keynodes::nrel_agreement_credit
    };
    
    // 4. Поиск соседей по всем типам отношений
    for (const auto& relType : relationTypes)
    {
      // Исходящие связи
      ScIterator5Ptr itOut = m_context.CreateIterator5(
        current,
        ScType::ConstCommonArc,
        ScType::ConstNode,
        ScType::ConstPermPosArc,
        relType
      );
      
      while (itOut->Next())
      {
        ScAddr neighbor = itOut->Get(2);
        if (visited.find(neighbor) == visited.end())
        {
          visited.insert(neighbor);
          queue.push(neighbor);
          SC_LOG_DEBUG("Found outgoing connection to: " 
                       << m_context.GetElementSystemIdentifier(neighbor));
        }
      }
      
      // Входящие связи
      ScIterator5Ptr itIn = m_context.CreateIterator5(
        ScType::ConstNode,
        ScType::ConstCommonArc,
        current,
        ScType::ConstPermPosArc,
        relType
      );
      
      while (itIn->Next())
      {
        ScAddr neighbor = itIn->Get(0);
        if (visited.find(neighbor) == visited.end())
        {
          visited.insert(neighbor);
          queue.push(neighbor);
          SC_LOG_DEBUG("Found incoming connection from: " 
                       << m_context.GetElementSystemIdentifier(neighbor));
        }
      }
    }
  }
  
  // 5. Формирование результата
  ScStructure result = m_context.GenerateStructure();
  
  // Добавляем все компании компоненты в результат
  for (const auto& company : component)
  {
    result << company;
    
    // Помечаем, что компания принадлежит компоненте связности
    ScAddr edge = m_context.GenerateConnector(
      ScType::ConstPermPosArc,
      Keynodes::concept_connected_component,
      company
    );
    result << edge << Keynodes::concept_connected_component;
  }
  

  ScAddr componentInfo = m_context.GenerateNode(ScType::ConstNode);

  
  m_context.GenerateConnector(ScType::ConstPermPosArc, componentInfo, component.size());
  m_context.GenerateConnector(ScType::ConstPermPosArc, 
                             Keynodes::concept_component_info, 
                             componentInfo);
  
  result << componentInfo << component.size() << Keynodes::concept_component_info;
  
  action.SetResult(result);
  
  SC_LOG_INFO("Found connected component of size " 
              << component.size() 
              << " starting from " 
              << m_context.GetElementSystemIdentifier(startCompany));
  
  return action.FinishSuccessfully();
}