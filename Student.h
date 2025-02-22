#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <unordered_map>

class Student {
public:
    Student(int id, const std::string& name, const std::unordered_map<std::string, int>& scores);
    int GetId() const;
    std::string GetName() const;
    std::unordered_map<std::string, int> GetScores() const;
    void ModifyInfo(const std::string& name, const std::unordered_map<std::string, int>& scores);
    std::string ToString() const;

private:
    int id_;
    std::string name_;
    std::unordered_map<std::string, int> scores_;
};

#endif 
