#include "StudentManager.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>

void ClearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::unordered_map<std::string, int> InputScores() {
    std::unordered_map<std::string, int> scores;
    std::string subject;
    int score;

    while (true) {
        std::cout << "请输入课程名（输入'end'结束）：";
        std::cin >> subject;
        if (subject == "end") break;

        std::cout << "请输入成绩：";
        while (!(std::cin >> score)) {
            std::cerr << "输入无效，请重新输入成绩：";
            ClearInputBuffer();
        }
        scores[subject] = score;
        ClearInputBuffer(); 
    }
    return scores;
}

int main() {
    StudentManager manager;
    int choice;

    while (true) {
        std::cout << "\n学生成绩管理系统\n";
        std::cout << "1. 添加学生信息\n2. 查询学生信息\n3. 修改学生信息\n4. 删除学生信息\n"
                     "5. 显示所有学生信息\n6. 计算统计信息\n7. 保存到文件\n8. 从文件加载\n0. 退出\n请输入选项：";
        
        if (!(std::cin >> choice)) {
            ClearInputBuffer();
            std::cerr << "输入无效，请重新输入！\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                std::string name;
                std::unordered_map<std::string, int> scores;

                std::cout << "请输入学号：";
                while (!(std::cin >> id)) {
                    std::cerr << "输入无效，请重新输入学号：";
                    ClearInputBuffer();
                }

                ClearInputBuffer();
                std::cout << "请输入姓名：";
                std::getline(std::cin, name);

                scores = InputScores();
                manager.AddStudent(Student(id, name, scores));
                break;
            }
            case 2: {  
                int searchChoice;
                std::cout << "1. 按学号查询\n2. 按姓名查询\n请选择查询方式：";
                std::cin >> searchChoice;
                ClearInputBuffer();

                if (searchChoice == 1) {
                    int id;
                    std::cout << "请输入学号：";
                    std::cin >> id;
                    Student* student = manager.FindStudentById(id);
                    if (student) {
                        std::cout << student->ToString() << std::endl;
                    } else {
                        std::cerr << "未找到该学生！\n";
                    }
                } else if (searchChoice == 2) {
                    std::string name;
                    std::cout << "请输入姓名：";
                    std::getline(std::cin, name);
                    Student* student = manager.FindStudentByName(name);
                    if (student) {
                        std::cout << student->ToString() << std::endl;
                    } else {
                        std::cerr << "未找到该学生！\n";
                    }
                } else {
                    std::cerr << "无效选项！\n";
                }
                break;
            }
            case 3: { 
                int id;
                std::string name;
                std::unordered_map<std::string, int> scores;

                std::cout << "请输入要修改的学生学号：";
                while (!(std::cin >> id)) {
                    std::cerr << "输入无效，请重新输入学号：";
                    ClearInputBuffer();
                }

                ClearInputBuffer();
                std::cout << "请输入新的姓名：";
                std::getline(std::cin, name);

                scores = InputScores();
                manager.ModifyStudent(id, name, scores);
                break;
            }
            case 4: {  
                int id;
                std::cout << "请输入要删除的学生学号：";
                while (!(std::cin >> id)) {
                    std::cerr << "输入无效，请重新输入学号：";
                    ClearInputBuffer();
                }
                manager.DeleteStudent(id);
                break;
            }
            case 5: { 
                int sortChoice;
                std::cout << "1. 按学号排序\n2. 按总成绩排序\n请选择排序方式：";
                std::cin >> sortChoice;
                manager.DisplayAllStudents(sortChoice == 1);
                break;
            }
            case 6: {  
                manager.CalculateStatistics();
                break;
            }
            case 7: {  
                std::string filename;
                std::cout << "请输入保存文件名：";
                ClearInputBuffer();
                std::getline(std::cin, filename);
                manager.SaveToFile(filename);
                std::cout << "保存成功！\n";
                break;
            }
            case 8: {  
                std::string filename;
                std::cout << "请输入加载文件名：";
                ClearInputBuffer();
                std::getline(std::cin, filename);
                manager.LoadFromFile(filename);
                std::cout << "加载成功！\n";
                break;
            }
            case 0: {  
                std::cout << "退出系统。\n";
                return 0;
            }
            default: {
                std::cerr << "无效选项！\n";
                break;
            }
        }
    }
    return 0;
}
