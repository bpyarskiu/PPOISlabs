#pragma once
#include <sc-memory/sc_memory.hpp>
#include "keynodes/Keynodes2.hpp"

namespace economic_ecosystem
{

inline ScAddr resolve_arg(ScMemoryContext & context, 
                         const ScAddr & setAddr, 
                         const ScAddr & rrelAddr)
{
    ScIterator5Ptr it = context.CreateIterator5(
        setAddr,
        ScType::ConstPermPosArc,
        ScType::Unknown,
        ScType::ConstPermPosArc,
        rrelAddr
    );

    if (it->Next())
        return it->Get(2);
        
    return ScAddr();
}

inline void create_relationship(ScMemoryContext & context,
                               ScAddr from,
                               ScAddr to,
                               ScAddr relation)
{
    ScAddr edge = context.GenerateConnector(ScType::ConstCommonArc, from, to);
    context.GenerateConnector(ScType::ConstPermPosArc, relation, edge);
}

inline ScAddr create_company_with_type(ScMemoryContext & context,
                                      const std::string & idtf)
{
    ScAddr company = context.GenerateNode(ScType::ConstNode);
    context.SetElementSystemIdentifier(idtf, company);
    
    // Помечаем как компанию
    ScAddr edge = context.GenerateConnector(
        ScType::ConstPermPosArc,
        Keynodes::concept_company,
        company
    );
    
    return company;
}

}