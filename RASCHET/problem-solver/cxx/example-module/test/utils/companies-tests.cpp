#include <sc-memory/test/sc_test.hpp>
#include <sc-memory/sc_memory.hpp>
#include <vector>
#include <set>
#include "../../agents/FindConnectedComponentsAgent.hpp"
#include "../../agents/CalculateCentralityAgent.hpp"
#include "../../keynodes/Keynodes2.hpp"
#include "../../utils/utils.hpp"

using namespace economic_ecosystem;

class EconomicAgentsTest : public ScMemoryTest
{
protected:
    void SetUp() override
    {
        ScMemoryTest::SetUp();
        
        // Инициализация ключевых узлов в памяти
        
        // Регистрация агентов
        m_ctx->SubscribeAgent<FindConnectedComponentsAgent>();
        m_ctx->SubscribeAgent<CalculateCentralityAgent>();
    }
    
    // Вспомогательная функция для создания тестового графа компаний
    struct TestCompanyGraph {
        ScAddr companyA, companyB, companyC, companyD, companyE;
        std::vector<ScAddr> allCompanies;
        
        TestCompanyGraph(ScMemoryContext & ctx) {
            companyA = create_company_with_type(ctx, "Company_A");
            companyB = create_company_with_type(ctx, "Company_B");
            companyC = create_company_with_type(ctx, "Company_C");
            companyD = create_company_with_type(ctx, "Company_D");
            companyE = create_company_with_type(ctx, "Company_E");
            
            allCompanies = {companyA, companyB, companyC, companyD, companyE};
            
            // Создаем связи между компаниями
            // Компонента 1: A <-> B <-> C (сильно связанные)
            create_relationship(ctx, companyA, companyB, Keynodes::nrel_agreement_contract);
            create_relationship(ctx, companyB, companyA, Keynodes::nrel_agreement_supplies);
            create_relationship(ctx, companyB, companyC, Keynodes::nrel_agreement_contract);
            create_relationship(ctx, companyC, companyB, Keynodes::nrel_agreement_credit);
            
            // Дополнительные связи для центральности компании B
            create_relationship(ctx, companyB, companyD, Keynodes::nrel_agreement_supplies);
            create_relationship(ctx, companyE, companyB, Keynodes::nrel_agreement_credit);
            
            // Компонента 2: D -> E (однонаправленная связь)
            create_relationship(ctx, companyD, companyE, Keynodes::nrel_agreement_contract);
        }
    };
    
    // Функция для создания структуры аргументов
    ScAddr create_arguments_struct(ScMemoryContext & ctx, ScAddr arg1, ScAddr arg2 = ScAddr())
    {
        ScAddr args = ctx.GenerateNode(ScType::ConstNode);
        
        // Первый аргумент
        ScAddr arc1 = ctx.GenerateConnector(ScType::ConstPermPosArc, args, arg1);
        ctx.GenerateConnector(ScType::ConstPermPosArc, Keynodes::rrel_1, arc1);
        
        // Второй аргумент (если есть)
        if (arg2.IsValid())
        {
            ScAddr arc2 = ctx.GenerateConnector(ScType::ConstPermPosArc, args, arg2);
            ctx.GenerateConnector(ScType::ConstPermPosArc, Keynodes::rrel_2, arc2);
        }
        
        return args;
    }
};

// ----------------------------------------------------------------------------
// ТЕСТЫ ДЛЯ FindConnectedComponentsAgent
// ----------------------------------------------------------------------------

TEST_F(EconomicAgentsTest, FindConnectedComponents_FromCentralNode)
{
    TestCompanyGraph graph(*m_ctx);
    
    // Создаем действие для поиска компоненты связности
    ScAction action = m_ctx->GenerateAction(Keynodes::action_find_connected_components);
    ScAddr args = create_arguments_struct(*m_ctx, graph.companyB);
    action.SetArguments(args);
    
    // Запускаем агента
    EXPECT_TRUE(action.InitiateAndWait());
    EXPECT_TRUE(action.IsFinishedSuccessfully());
    
    // Проверяем результат
    ScStructure result = action.GetResult();
    EXPECT_FALSE(result.IsEmpty());
    // Компонента должна содержать A, B, C (сильно связанные)
    EXPECT_TRUE(m_ctx->CheckConnector(result,graph.companyA,ScType::ConstPermPosArc));
    EXPECT_TRUE(m_ctx->CheckConnector(result,graph.companyB,ScType::ConstPermPosArc));
    EXPECT_TRUE(m_ctx->CheckConnector(result,graph.companyC,ScType::ConstPermPosArc));
    
    // D и E не должны быть в этой компоненте (они в другой)
    EXPECT_FALSE(m_ctx->CheckConnector(result,graph.companyE,ScType::ConstPermPosArc));
    EXPECT_FALSE(m_ctx->CheckConnector(result,graph.companyD,ScType::ConstPermPosArc));
    
    // Проверяем, что все элементы помечены как принадлежащие компоненте
    ScIterator3Ptr it = m_ctx->CreateIterator3(
        result,
        ScType::ConstPermPosArc,
        Keynodes::concept_connected_component
    );
    
    int count = 0;
    while (it->Next()) count++;
    EXPECT_EQ(count, 3); // A, B, C
}

TEST_F(EconomicAgentsTest, FindConnectedComponents_IsolatedCompany)
{
    // Создаем изолированную компанию без связей
    ScAddr isolated = create_company_with_type(*m_ctx, "Isolated_Company");
    
    ScAction action = m_ctx->GenerateAction(Keynodes::action_find_connected_components);
    ScAddr args = create_arguments_struct(*m_ctx, isolated);
    action.SetArguments(args);
    
    EXPECT_TRUE(action.InitiateAndWait());
    EXPECT_TRUE(action.IsFinishedSuccessfully());
    
    ScStructure result = action.GetResult();
    // Должна содержать только саму компанию
    EXPECT_TRUE(m_ctx->CheckConnector(result,isolated,ScType::ConstPermPosArc));
    
    // Проверяем размер
    int elementCount = 0;
    ScIterator3Ptr it = m_ctx->CreateIterator3(
        result,
        ScType::ConstPermPosArc,
        ScType::ConstNode
    );
    while (it->Next()) elementCount++;
    
    EXPECT_EQ(elementCount, 1);
}

// ----------------------------------------------------------------------------
// ТЕСТЫ ДЛЯ CalculateCentralityAgent
// ----------------------------------------------------------------------------

TEST_F(EconomicAgentsTest, CalculateCentrality_CentralCompany)
{
    TestCompanyGraph graph(*m_ctx);
    
    // Компания B должна быть центральной (много связей, разные типы)
    ScAction action = m_ctx->GenerateAction(Keynodes::action_calculate_centrality);
    ScAddr args = create_arguments_struct(*m_ctx, graph.companyB);
    action.SetArguments(args);
    
    EXPECT_TRUE(action.InitiateAndWait());
    EXPECT_TRUE(action.IsFinishedSuccessfully());
    
    ScStructure result = action.GetResult();
    EXPECT_FALSE(result.IsEmpty());
    
    // Проверяем, что компания помечена как центральная
    ScIterator5Ptr it = m_ctx->CreateIterator5(
        Keynodes::concept_central_company,
        ScType::ConstPermPosArc,
        graph.companyB,
        ScType::ConstPermPosArc,
        ScType::Unknown
    );
    
    EXPECT_TRUE(it->Next());
}

TEST_F(EconomicAgentsTest, CalculateCentrality_NonCentralCompany)
{
    TestCompanyGraph graph(*m_ctx);
    
    // Компания A имеет мало связей (не центральная)
    ScAction action = m_ctx->GenerateAction(Keynodes::action_calculate_centrality);
    ScAddr args = create_arguments_struct(*m_ctx, graph.companyA);
    action.SetArguments(args);
    
    EXPECT_TRUE(action.InitiateAndWait());
    EXPECT_TRUE(action.IsFinishedSuccessfully());
    
    // Для нецентральной компании результат может быть пустым
    // или не содержать связи с concept_central_company
    
    ScIterator5Ptr it = m_ctx->CreateIterator5(
        Keynodes::concept_central_company,
        ScType::ConstPermPosArc,
        graph.companyA,
        ScType::ConstPermPosArc,
        ScType::Unknown
    );
    
    EXPECT_FALSE(it->Next());
}

TEST_F(EconomicAgentsTest, CalculateCentrality_InvalidArguments)
{
    // Тест с неверными аргументами
    ScAction action = m_ctx->GenerateAction(Keynodes::action_calculate_centrality);
    
    // Не устанавливаем аргументы вообще
    EXPECT_TRUE(action.InitiateAndWait());
    // В зависимости от реализации, может завершиться с ошибкой или успешно с пустым результатом
    // Проверяем хотя бы что не падает
    EXPECT_TRUE(action.IsFinishedSuccessfully() || action.IsFinishedWithError());
}

TEST_F(EconomicAgentsTest, CalculateCentrality_CompanyWithDiverseRelations)
{
    // Создаем компанию с разнообразными связями (должна быть центральной)
    ScAddr diverseCompany = create_company_with_type(*m_ctx, "Diverse_Company");
    
    // Создаем несколько партнеров с разными типами отношений
    ScAddr partner1 = m_ctx->GenerateNode(ScType::ConstNode);
    ScAddr partner2 = m_ctx->GenerateNode(ScType::ConstNode);
    ScAddr partner3 = m_ctx->GenerateNode(ScType::ConstNode);
    
    create_relationship(*m_ctx, diverseCompany, partner1, Keynodes::nrel_agreement_contract);
    create_relationship(*m_ctx, diverseCompany, partner2, Keynodes::nrel_agreement_supplies);
    create_relationship(*m_ctx, partner3, diverseCompany, Keynodes::nrel_agreement_credit);
    
    ScAction action = m_ctx->GenerateAction(Keynodes::action_calculate_centrality);
    ScAddr args = create_arguments_struct(*m_ctx, diverseCompany);
    action.SetArguments(args);
    
    EXPECT_TRUE(action.InitiateAndWait());
    EXPECT_TRUE(action.IsFinishedSuccessfully());
    
    // Проверяем, что компания признана центральной из-за разнообразия связей
    ScIterator5Ptr it = m_ctx->CreateIterator5(
        Keynodes::concept_central_company,
        ScType::ConstPermPosArc,
        diverseCompany,
        ScType::ConstPermPosArc,
        ScType::Unknown
    );
    
    EXPECT_TRUE(it->Next());
}

// ----------------------------------------------------------------------------
// ИНТЕГРАЦИОННЫЙ ТЕСТ
// ----------------------------------------------------------------------------

TEST_F(EconomicAgentsTest, Integration_FindCentralCompaniesInComponent)
{
    TestCompanyGraph graph(*m_ctx);
    
    // 1. Находим компоненту связности
    ScAction findComponentAction = m_ctx->GenerateAction(
        Keynodes::action_find_connected_components
    );
    ScAddr componentArgs = create_arguments_struct(*m_ctx, graph.companyA);
    findComponentAction.SetArguments(componentArgs);
    
    EXPECT_TRUE(findComponentAction.InitiateAndWait());
    EXPECT_TRUE(findComponentAction.IsFinishedSuccessfully());
    
    ScStructure component = findComponentAction.GetResult();
    
    // 2. Для каждой компании в компоненте проверяем центральность
    std::vector<ScAddr> centralCompanies;
    
    ScIterator3Ptr it = m_ctx->CreateIterator3(
        component,
        ScType::ConstPermPosArc,
        ScType::ConstNode
    );
    
    while (it->Next())
    {
        ScAddr company = it->Get(2);
        
        // Пропускаем, если это не компания (могут быть служебные узлы)
        if (!m_ctx->CheckConnector(Keynodes::concept_company, company, ScType::ConstPermPosArc))
            continue;
        
        ScAction centralityAction = m_ctx->GenerateAction(
            Keynodes::action_calculate_centrality
        );
        ScAddr centralityArgs = create_arguments_struct(*m_ctx, company);
        centralityAction.SetArguments(centralityArgs);
        
        centralityAction.InitiateAndWait();
        
        if (centralityAction.IsFinishedSuccessfully())
        {
            // Проверяем, является ли компания центральной
            ScIterator5Ptr checkCentral = m_ctx->CreateIterator5(
                Keynodes::concept_central_company,
                ScType::ConstPermPosArc,
                company,
                ScType::ConstPermPosArc,
                ScType::Unknown
            );
            
            if (checkCentral->Next())
            {
                centralCompanies.push_back(company);
            }
        }
    }
    
    // В нашей тестовой структуре центральной должна быть компания B
    ASSERT_EQ(centralCompanies.size(), 1);
    EXPECT_EQ(centralCompanies[0], graph.companyB);
}