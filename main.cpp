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
        std::cout << "������γ���������'end'��������";
        std::cin >> subject;
        if (subject == "end") break;

        std::cout << "������ɼ���";
        while (!(std::cin >> score)) {
            std::cerr << "������Ч������������ɼ���";
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
        std::cout << "\nѧ���ɼ�����ϵͳ\n";
        std::cout << "1. ���ѧ����Ϣ\n2. ��ѯѧ����Ϣ\n3. �޸�ѧ����Ϣ\n4. ɾ��ѧ����Ϣ\n"
                     "5. ��ʾ����ѧ����Ϣ\n6. ����ͳ����Ϣ\n7. ���浽�ļ�\n8. ���ļ�����\n0. �˳�\n������ѡ�";
        
        if (!(std::cin >> choice)) {
            ClearInputBuffer();
            std::cerr << "������Ч�����������룡\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                std::string name;
                std::unordered_map<std::string, int> scores;

                std::cout << "������ѧ�ţ�";
                while (!(std::cin >> id)) {
                    std::cerr << "������Ч������������ѧ�ţ�";
                    ClearInputBuffer();
                }

                ClearInputBuffer();
                std::cout << "������������";
                std::getline(std::cin, name);

                scores = InputScores();
                manager.AddStudent(Student(id, name, scores));
                break;
            }
            case 2: {  
                int searchChoice;
                std::cout << "1. ��ѧ�Ų�ѯ\n2. ��������ѯ\n��ѡ���ѯ��ʽ��";
                std::cin >> searchChoice;
                ClearInputBuffer();

                if (searchChoice == 1) {
                    int id;
                    std::cout << "������ѧ�ţ�";
                    std::cin >> id;
                    Student* student = manager.FindStudentById(id);
                    if (student) {
                        std::cout << student->ToString() << std::endl;
                    } else {
                        std::cerr << "δ�ҵ���ѧ����\n";
                    }
                } else if (searchChoice == 2) {
                    std::string name;
                    std::cout << "������������";
                    std::getline(std::cin, name);
                    Student* student = manager.FindStudentByName(name);
                    if (student) {
                        std::cout << student->ToString() << std::endl;
                    } else {
                        std::cerr << "δ�ҵ���ѧ����\n";
                    }
                } else {
                    std::cerr << "��Чѡ�\n";
                }
                break;
            }
            case 3: { 
                int id;
                std::string name;
                std::unordered_map<std::string, int> scores;

                std::cout << "������Ҫ�޸ĵ�ѧ��ѧ�ţ�";
                while (!(std::cin >> id)) {
                    std::cerr << "������Ч������������ѧ�ţ�";
                    ClearInputBuffer();
                }

                ClearInputBuffer();
                std::cout << "�������µ�������";
                std::getline(std::cin, name);

                scores = InputScores();
                manager.ModifyStudent(id, name, scores);
                break;
            }
            case 4: {  
                int id;
                std::cout << "������Ҫɾ����ѧ��ѧ�ţ�";
                while (!(std::cin >> id)) {
                    std::cerr << "������Ч������������ѧ�ţ�";
                    ClearInputBuffer();
                }
                manager.DeleteStudent(id);
                break;
            }
            case 5: { 
                int sortChoice;
                std::cout << "1. ��ѧ������\n2. ���ܳɼ�����\n��ѡ������ʽ��";
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
                std::cout << "�����뱣���ļ�����";
                ClearInputBuffer();
                std::getline(std::cin, filename);
                manager.SaveToFile(filename);
                std::cout << "����ɹ���\n";
                break;
            }
            case 8: {  
                std::string filename;
                std::cout << "����������ļ�����";
                ClearInputBuffer();
                std::getline(std::cin, filename);
                manager.LoadFromFile(filename);
                std::cout << "���سɹ���\n";
                break;
            }
            case 0: {  
                std::cout << "�˳�ϵͳ��\n";
                return 0;
            }
            default: {
                std::cerr << "��Чѡ�\n";
                break;
            }
        }
    }
    return 0;
}
