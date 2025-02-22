#include "Student.h"
#include <sstream>

Student::Student(int id, const std::string& name, const std::unordered_map<std::string, int>& scores)
    : id_(id), name_(name), scores_(scores) {}

int Student::GetId() const { return id_; }
std::string Student::GetName() const { return name_; }
std::unordered_map<std::string, int> Student::GetScores() const { return scores_; }

void Student::ModifyInfo(const std::string& name, const std::unordered_map<std::string, int>& scores) {
    name_ = name;
    scores_ = scores;
}

std::string Student::ToString() const {
    std::ostringstream oss;
    oss << "ѧ�ţ�" << id_ << "��������" << name_ << "���ɼ���[";
    for (const auto& pair : scores_) {
        oss << pair.first << "��" << pair.second << "��";
    }
    std::string result = oss.str();
    if (!scores_.empty()) result.pop_back();
    result += "]";
    return result;
}
