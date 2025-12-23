#pragma once
#include <sc-memory/sc_keynodes.hpp>

namespace economic_ecosystem
{

class Keynodes : public ScKeynodes
{
public:
  // Actions
  static inline ScKeynode const action_find_connected_components { 
    "action_find_connected_components", ScType::ConstNodeClass };
  static inline ScKeynode const action_calculate_centrality { 
    "action_calculate_centrality", ScType::ConstNodeClass };
  
  // Relation types (edges)
  static inline ScKeynode const nrel_agreement_contract { 
    "nrel_agreement_contract", ScType::ConstNodeNonRole };
  static inline ScKeynode const nrel_agreement_supplies { 
    "nrel_agreement_supplies", ScType::ConstNodeNonRole };
  static inline ScKeynode const nrel_agreement_credit { 
    "nrel_agreement_credit", ScType::ConstNodeNonRole };
  
  // Concepts (nodes)
  static inline ScKeynode const concept_company { 
    "concept_company", ScType::ConstNodeClass };
  static inline ScKeynode const concept_central_company { 
    "concept_central_company", ScType::ConstNodeClass };
  static inline ScKeynode const concept_connected_component { 
    "concept_connected_component", ScType::ConstNodeClass };
  static inline ScKeynode const concept_component_info { 
    "concept_component_info", ScType::ConstNodeClass };
  
  // Role relations for argument ordering
  static inline ScKeynode const rrel_1 { "rrel_1", ScType::ConstNodeRole };
  static inline ScKeynode const rrel_2 { "rrel_2", ScType::ConstNodeRole };
  
  // Optional: Result relations
  static inline ScKeynode const nrel_total_connections { 
    "nrel_total_connections", ScType::ConstNodeNonRole };
  static inline ScKeynode const nrel_unique_partners { 
    "nrel_unique_partners", ScType::ConstNodeNonRole };
  static inline ScKeynode const nrel_diversity_score { 
    "nrel_diversity_score", ScType::ConstNodeNonRole };
};

}