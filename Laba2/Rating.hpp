#pragma once

class Rating {
private:
    double value;
    int votesCount;

public:
    Rating();
    Rating(double value, int totalVotes);
    
    // Геттеры
    double getValue() const;
    int getVotesCount() const;
    
    // Единственный метод для изменения состояния
    void addVote(double vote);
    
    // Вспомогательные методы (не изменяют состояние)
    bool isValid() const;
    void display() const;

private:
    bool validateVote(double vote) const;
};