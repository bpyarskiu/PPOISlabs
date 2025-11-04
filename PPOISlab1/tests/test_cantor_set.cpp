#include <UnitTest++/UnitTest++.h>
#include "../include/cantor_set.hpp"

#include <string>
#include <vector>


SUITE(CantorSetTest) {
    TEST(ConstructorFromString) {
        CantorSet set(std::string("{1,2,3}"));
        CHECK(!set.isEmpty());
        CHECK_EQUAL(3, set.cardinality());
        CHECK(set.contains(std::string("1")));
        CHECK(set.contains(std::string("2")));
        CHECK(set.contains(std::string("3")));
    }

    TEST(EmptySet) {
        CantorSet set(std::string("{}"));
        CHECK(set.isEmpty());
        CHECK_EQUAL(0, set.cardinality());
        
        CantorSet defaultSet;
        CHECK(defaultSet.isEmpty());
    }

    TEST(ContainsOperator) {
        CantorSet set(std::string("{a,b,c}"));
        CHECK(set[std::string("a")]);
        CHECK(set[std::string("b")]);
        CHECK(set[std::string("c")]);
        CHECK(!set[std::string("d")]);
    }

    TEST(AddElement) {
        CantorSet set;
        set.addElement(std::string("test"));
        CHECK(set.contains(std::string("test")));
        CHECK_EQUAL(1, set.cardinality());
    }

    TEST(AddSubset) {
        CantorSet parent;
        auto child = std::make_unique<CantorSet>();
        child->addElement(std::string("child_element"));
        
        parent.addSubset(std::move(child));
        CHECK_EQUAL(1, parent.cardinality());
    }

    TEST(Union) {
        CantorSet set1(std::string("{1,2,3}"));
        CantorSet set2(std::string("{2,3,4}"));
        
        CantorSet result = set1 + set2;
        CHECK(result.contains(std::string("1")));
        CHECK(result.contains(std::string("2")));
        CHECK(result.contains(std::string("3")));
        CHECK(result.contains(std::string("4")));
        CHECK_EQUAL(4, result.cardinality());
    }

    TEST(Intersection) {
        CantorSet set1(std::string("{1,2,3}"));
        CantorSet set2(std::string("{2,3,4}"));
        
        CantorSet result = set1 * set2;
        CHECK(!result.contains(std::string("1")));
        CHECK(result.contains(std::string("2")));
        CHECK(result.contains(std::string("3")));
        CHECK(!result.contains(std::string("4")));
        CHECK_EQUAL(2, result.cardinality());
    }

    TEST(Difference) {
        CantorSet set1(std::string("{1,2,3}"));
        CantorSet set2(std::string("{2,3,4}"));
        
        CantorSet result = set1 - set2;
        CHECK(result.contains(std::string("1")));
        CHECK(!result.contains(std::string("2")));
        CHECK(!result.contains(std::string("3")));
        CHECK(!result.contains(std::string("4")));
        CHECK_EQUAL(1, result.cardinality());
    }

    TEST(CompoundAssignment) {
        CantorSet set1(std::string("{1,2,3}"));
        CantorSet set2(std::string("{3,4,5}"));
        
        set1 += set2;
        CHECK(set1.contains(std::string("1")));
        CHECK(set1.contains(std::string("2")));
        CHECK(set1.contains(std::string("3")));
        CHECK(set1.contains(std::string("4")));
        CHECK(set1.contains(std::string("5")));
        
        set1 -= CantorSet(std::string("{2,4}"));
        CHECK(set1.contains(std::string("1")));
        CHECK(!set1.contains(std::string("2")));
        CHECK(set1.contains(std::string("3")));
        CHECK(!set1.contains(std::string("4")));
        CHECK(set1.contains(std::string("5")));
    }

    TEST(Comparison) {
        CantorSet set1(std::string("{1,2,3}"));
        CantorSet set2(std::string("{1,2,3}"));
        CantorSet set3(std::string("{4,5,6}"));
        
        CHECK(set1 == set2);
        CHECK(!(set1 == set3));
        CHECK(set1 < set3 || set3 < set1);
    }

    TEST(ToString) {
        CantorSet set(std::string("{a,b,c}"));
        std::string str = set.toString();
        CHECK(!str.empty());
        CHECK(str.find(std::string("a")) != std::string::npos);
        CHECK(str.find(std::string("b")) != std::string::npos);
        CHECK(str.find(std::string("c")) != std::string::npos);
    }

    TEST(TotalElements) {
        CantorSet set(std::string("{1,2}"));
        CHECK_EQUAL(2, set.totalElements());
        
        // Тест с подмножествами
        CantorSet parent;
        parent.addElement(std::string("parent1"));
        
        auto child = std::make_unique<CantorSet>();
        child->addElement(std::string("child1"));
        child->addElement(std::string("child2"));
        parent.addSubset(std::move(child));
        
        CHECK_EQUAL(3, parent.totalElements());
    }

    TEST(CantorSetCreation) {
        CantorSet original(std::string("{1,2,3,4,5,6}"));
        CantorSet cantor = CantorSet::createCompleteCantorSet(original);
        
        CHECK(!cantor.isEmpty());
        // Проверяем, что содержит исходные элементы
        CHECK(cantor.contains(std::string("1")));
        CHECK(cantor.contains(std::string("2")));
        CHECK(!cantor.contains(std::string("3")));
        CHECK(!cantor.contains(std::string("4")));
        CHECK(cantor.contains(std::string("5")));
        CHECK(cantor.contains(std::string("6")));
        
        // Проверяем структуру канторова множества
        std::string cantorStr = cantor.toString();
        CHECK(!cantorStr.empty());
    }

    TEST(GetLevel) {
        CantorSet original(std::string("{1,2,3,4,5,6}"));
        CantorSet cantor = CantorSet::createCompleteCantorSet(original);
        
        CantorSet level0 = cantor.getLevel(0);
        CHECK(!level0.isEmpty());
        
        // Последующие уровни могут быть пустыми в зависимости от реализации
        CantorSet level1 = cantor.getLevel(1);
    }
    TEST(CheckMax){
        CantorSet original("1,2,3,4,5,6,7,8,9");
        CantorSet complete =CantorSet::createCompleteCantorSet(original);
        CHECK_EQUAL(4,complete.getMaxDepth());
    }
    // TEST(DetailedString){
    //     std::string check="CantorSet: {1, 2, 3, 4, 5, 6, 7, 8, 9}\nCardinality: 91\nTotal elements: 9\nSubsets:\n";
    //     CantorSet original("1,2,3,4,5,6,7,8,9");
    //     CHECK(original.toDetailedString() == check);
    // }

    TEST(RemoveElement) {
        CantorSet set(std::string("{1,2,3}"));
        CHECK(set.remove(std::string("2")));
        CHECK(!set.contains(std::string("2")));
        CHECK(set.contains(std::string("1")));
        CHECK(set.contains(std::string("3")));
        CHECK_EQUAL(2, set.cardinality());
        
        CHECK(!set.remove(std::string("5"))); // Несуществующий элемент
    }

    TEST(ForEachMethods) {
        CantorSet set(std::string("{a,b,c}"));
        
        std::vector<std::string> elements;
        set.forEachElement([&](const std::string& elem) {
            elements.push_back(elem);
        });
        
        CHECK_EQUAL(3, elements.size());
        CHECK(std::find(elements.begin(), elements.end(), std::string("a")) != elements.end());
        CHECK(std::find(elements.begin(), elements.end(), std::string("b")) != elements.end());
        CHECK(std::find(elements.begin(), elements.end(), std::string("c")) != elements.end());
        
        // Тест forEachSubset с пустыми подмножествами
        int subsetCount = 0;
        set.forEachSubset([&](const CantorSet& subset) {
            subsetCount++;
        });
        // Может быть 0 если нет подмножеств
    }
    TEST(Empty){
        CantorSet set;
        CHECK(set.toCantorString()=="{}");
    }
    TEST(ToCantorString){
        CantorSet set="{1,2,3,4,5,6,7,8,9}";
        CHECK(set.toCantorString()=="{1,2,3,4,5,6,7,8,9}");
    }

    TEST(SortingMethodsAndContruction){
        std::vector<std::string> instance;
        instance.push_back("6");
        instance.push_back("1");
        instance.push_back("2");
        instance.push_back("4");
        instance.push_back("3");
        instance.push_back("5");
        std::vector<std::string> etalon;
        etalon.push_back("1");
        etalon.push_back("2");
        etalon.push_back("3");
        etalon.push_back("4");
        etalon.push_back("5");
        etalon.push_back("6");

        MySet<std::string> SetInstance;
        SetInstance.insert("1");
        SetInstance.insert("2");
        SetInstance.insert("3");
        SetInstance.insert("4");
        SetInstance.insert("5");
        SetInstance.insert("6");
        CantorSet original( instance);
        CantorSet originalSet( SetInstance);
        CHECK_EQUAL(true,original.sorting(etalon));
        

        CHECK_EQUAL(true,originalSet.sorting(etalon));
        // CHECK_EQUAL(etalon.subsets, original.getSortedSubsets());
    }


    TEST(CopyConstructor) {
        CantorSet original(std::string("{1,2,3}"));
        CantorSet copy(original);
        
        CHECK(copy.contains(std::string("1")));
        CHECK(copy.contains(std::string("2")));
        CHECK(copy.contains(std::string("3")));
        CHECK_EQUAL(3, copy.cardinality());
    }

    TEST(AssignmentOperator) {
        CantorSet set1(std::string("{1,2,3}"));
        CantorSet set2;
        
        set2 = set1;
        CHECK(set2.contains(std::string("1")));
        CHECK(set2.contains(std::string("2")));
        CHECK(set2.contains(std::string("3")));
        CHECK_EQUAL(3, set2.cardinality());
    }
}

SUITE(CantorSetEdgeCases) {
    TEST(SingleElement) {
        CantorSet set(std::string("{single}"));
        CHECK(!set.isEmpty());
        CHECK_EQUAL(1, set.cardinality());
        CHECK(set.contains(std::string("single")));
    }

    TEST(ComplexSet) {
        CantorSet set(std::string("{a,{b,c},d}"));
        // Этот тест может потребовать адаптации под вашу реализацию парсинга
        CHECK(!set.isEmpty());
    }

    TEST(EmptyString) {
        CantorSet set(std::string(""));
        CHECK(set.isEmpty());
    }
}
SUITE(MySetTest) {
    TEST(DefaultConstructor) {
        MySet<int> set;
        CHECK(set.empty());
        CHECK_EQUAL(0, set.size());
    }

    TEST(InsertAndContains) {
        MySet<int> set;
        CHECK(set.insert(10));
        CHECK(set.contains(10));
        CHECK(!set.insert(10)); // Дубликат
        CHECK_EQUAL(1, set.size());
    }

    TEST(Remove) {
        MySet<int> set;
        set.insert(10);
        set.insert(20);
        
        CHECK(set.remove(10));
        CHECK(!set.contains(10));
        CHECK(set.contains(20));
        CHECK(!set.remove(30)); // Несуществующий элемент
    }

    TEST(Union) {
        MySet<int> set1;
        set1.insert(1);
        set1.insert(2);
        set1.insert(3);
        
        MySet<int> set2;
        set2.insert(3);
        set2.insert(4);
        set2.insert(5);
        
        MySet<int> result = set1 + set2;
        CHECK(result.contains(1));
        CHECK(result.contains(2));
        CHECK(result.contains(3));
        CHECK(result.contains(4));
        CHECK(result.contains(5));
        CHECK_EQUAL(5, result.size());
    }

    TEST(Intersection) {
        MySet<int> set1;
        set1.insert(1);
        set1.insert(2);
        set1.insert(3);
        
        MySet<int> set2;
        set2.insert(3);
        set2.insert(4);
        set2.insert(5);
        
        MySet<int> result = set1 * set2;
        CHECK(!result.contains(1));
        CHECK(!result.contains(2));
        CHECK(result.contains(3));
        CHECK(!result.contains(4));
        CHECK(!result.contains(5));
        CHECK_EQUAL(1, result.size());
    }

    TEST(Difference) {
        MySet<int> set1;
        set1.insert(1);
        set1.insert(2);
        set1.insert(3);
        
        MySet<int> set2;
        set2.insert(3);
        set2.insert(4);
        set2.insert(5);
        
        MySet<int> result = set1 - set2;
        CHECK(result.contains(1));
        CHECK(result.contains(2));
        CHECK(!result.contains(3));
        CHECK_EQUAL(2, result.size());
    }

    TEST(Comparison) {
        MySet<int> set1;
        set1.insert(1);
        set1.insert(2);
        set1.insert(3);
        
        MySet<int> set2;
        set2.insert(1);
        set2.insert(2);
        set2.insert(3);
        
        MySet<int> set3;
        set3.insert(4);
        set3.insert(5);
        
        CHECK(set1 == set2);
        CHECK(!(set1 == set3));
        CHECK(set1 < set3 || set3 < set1); // Один должен быть меньше другого
    }

    TEST(ForEach) {
        MySet<int> set;
        set.insert(1);
        set.insert(2);
        set.insert(3);
        
        std::vector<int> elements;
        set.forEach([&](const int& value) {
            elements.push_back(value);
        });
        
        CHECK_EQUAL(3, elements.size());
        CHECK(std::find(elements.begin(), elements.end(), 1) != elements.end());
        CHECK(std::find(elements.begin(), elements.end(), 2) != elements.end());
        CHECK(std::find(elements.begin(), elements.end(), 3) != elements.end());
    }

    TEST(CopyConstructor) {
        MySet<int> original;
        original.insert(1);
        original.insert(2);
        MySet<int> copy(original);
        CHECK(copy.contains(1));
        CHECK(copy.contains(2));
        CHECK_EQUAL(2, copy.size());
    }

    TEST(MoveConstructor) {
        MySet<int> original;
        original.insert(1);
        original.insert(2);
        
        MySet<int> moved(std::move(original));
        CHECK(moved.contains(1));
        CHECK(moved.contains(2));
        CHECK(original.empty()); // original должен быть пустым после перемещения
    }

    TEST(AssignmentOperator) {
        MySet<int> set1;
        set1.insert(1);
        set1.insert(2);
        
        MySet<int> set2;
        set2 = set1;
        
        CHECK(set2.contains(1));
        CHECK(set2.contains(2));
        CHECK_EQUAL(2, set2.size());
    }

    TEST(Clear) {
        MySet<int> set;
        set.insert(1);
        set.insert(2);
        
        CHECK(!set.empty());
        set.clear();
        CHECK(set.empty());
        CHECK_EQUAL(0, set.size());
    }
}

SUITE(MySetStringTest) {
    TEST(StringOperations) {
        MySet<std::string> set;
        CHECK(set.insert("hello"));
        CHECK(set.insert("world"));
        CHECK(!set.insert("hello")); // Дубликат
        
        CHECK(set.contains("hello"));
        CHECK(set.contains("world"));
        CHECK(!set.contains("test"));
        
        CHECK(set.remove("hello"));
        CHECK(!set.contains("hello"));
        CHECK_EQUAL(1, set.size());
    }
}
int main(){
    return UnitTest::RunAllTests();
 }