#include "StudentManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

void StudentManager::AddStudent(const Student& student) {
    int id = student.GetId();
    if (students_.find(id) != students_.end()) {
        std::cerr << "学号重复，添加失败！" << std::endl;
        return;
    }
    students_.emplace(id, student);  
    std::cout << "添加成功！" << std::endl;
}

Student* StudentManager::FindStudentById(int id) {
    auto it = students_.find(id);
    return (it != students_.end()) ? &it->second : nullptr;
}

Student* StudentManager::FindStudentByName(const std::string& name) {
    for (auto& pair : students_) {
        if (pair.second.GetName() == name) return &pair.second;
    }
    return nullptr;
}

void StudentManager::ModifyStudent(int id, const std::string& name, const std::unordered_map<std::string, int>& scores) {
    auto it = students_.find(id);
    if (it != students_.end()) {
        it->second.ModifyInfo(name, scores);
        std::cout << "修改成功！" << std::endl;
    } else {
        std::cerr << "未找到该学生。" << std::endl;
    }
}

void StudentManager::DeleteStudent(int id) {
    if (students_.erase(id)) {
        std::cout << "删除成功！" << std::endl;
    } else {
        std::cerr << "未找到该学生。" << std::endl;
    }
}

void StudentManager::DisplayAllStudents(bool sortById) {
    SortAndDisplay(sortById);
}

void StudentManager::SortAndDisplay(bool sortById) {
    std::vector<Student> sortedStudents;
    for (const auto& pair : students_) sortedStudents.push_back(pair.second);

    if (sortById) {
        std::sort(sortedStudents.begin(), sortedStudents.end(),
            [](const Student& a, const Student& b) { return a.GetId() < b.GetId(); });
    } else {
        std::sort(sortedStudents.begin(), sortedStudents.end(),
            [](const Student& a, const Student& b) {
                int sumA = 0, sumB = 0;
                for (const auto& score : a.GetScores()) sumA += score.second;
                for (const auto& score : b.GetScores()) sumB += score.second;
                return sumA > sumB; 
            });
    }

    for (const auto& student : sortedStudents) {
        std::cout << student.ToString() << std::endl;
    }
}

void StudentManager::CalculateStatistics() {
    if (students_.empty()) {
        std::cerr << "无学生数据！\n";
        return;
    }

    double total = 0;
    int maxScore = INT_MIN, minScore = INT_MAX;
    int count = 0;

    for (const auto& pair : students_) {
        for (const auto& score : pair.second.GetScores()) {
            int s = score.second;
            total += s;
            maxScore = std::max(maxScore, s);
            minScore = std::min(minScore, s);
            count++;
        }
    }

    if (count == 0) {
        std::cerr << "无成绩数据！\n";
        return;
    }

    std::cout << "全班平均成绩：" << (total / count) << "\n";
    std::cout << "最高分：" << maxScore << "\n";
    std::cout << "最低分：" << minScore << "\n";
}

void StudentManager::SaveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& pair : students_) {
        const Student& s = pair.second;
        file << s.GetId() << "," << s.GetName();
        for (const auto& score : s.GetScores()) {
            file << "," << score.first << ":" << score.second;
        }
        file << "\n";
    }
}

void StudentManager::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件！\n";
        return;
    }

    students_.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        std::string name;
        std::unordered_map<std::string, int> scores;

        std::string token;
        std::getline(iss, token, ',');
        id = std::stoi(token);
        std::getline(iss, name, ',');

        while (std::getline(iss, token, ',')) {
            size_t colonPos = token.find(':');
            std::string subject = token.substr(0, colonPos);
            int score = std::stoi(token.substr(colonPos + 1));
            scores[subject] = score;
        }

        students_.emplace(id, Student(id, name, scores));
    }
    std::cout << "已加载 " << students_.size() << " 条学生记录。\n";
}
