#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <vector>
#include <unordered_map>

class StudentManager {
public:
    void AddStudent(const Student& student);
    Student* FindStudentById(int id);
    Student* FindStudentByName(const std::string& name);
    void ModifyStudent(int id, const std::string& name, const std::unordered_map<std::string, int>& scores);
    void DeleteStudent(int id);
    void DisplayAllStudents(bool sortById = true);
    void CalculateStatistics();
    void SaveToFile(const std::string& filename);
    void LoadFromFile(const std::string& filename);

private:
    std::unordered_map<int, Student> students_;
    void SortAndDisplay(bool sortById);
};

#endif //
