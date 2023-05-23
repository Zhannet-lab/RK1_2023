#pragma once
#include <map> // ������������ ���� � ����������� �������
#include <vector>
#include <string>
#include <list>

using namespace std;


class WorkWithFile {
private:
    char* dataOfFile;
    int dataSize;

    map<char, int> symbolsFrequency;  // ������� ��� �������� ����������� ��������. ���� ������, �������� - ��� �����������

    void readFromFile(const char* fileName);    //������� ������ �� �����
    void prepareTestFile(const char* fileName);    //������� ��� �������� ��������� �����

    void countSymbolFrequency();

public:
    WorkWithFile();

    ~WorkWithFile();

    void writeStatInfoToFile(const char* outFile);
};

char* convertDecToBin(int number);

char* convertBinToHex(const char* binNum);

void writeToFile(const char* fileName, int writeAppend, const char* hexNum, const char* binNum);

void writeToFile(const char* fileName, const char* strNum);

void buildTree(int height);

std::vector<std::pair<int/*����� ������*/, float /*������� ��������*/>>
averStr2DArray(float** ar, int colCount, int rowCount);

void randFill(float** arr, int colCount, int rowCount);

struct Node {
    Node* next;
    Node* prev;
    int nameNode;
    static int countNodes;
};

class LinkedList {
private:
    Node* Head;
    Node* Tail;

    int nodesAmount;
public:
    LinkedList();

    ~LinkedList();

    void push_back(int nameNode);

    void insert(int nameNode, int position);

    void writeToFileFromTail();

    void writeToFileFromHead();
};

class StudentInfo {
private:
    std::tuple<string /*�������*/, string /*���*/, char* /*� ���� ������*/> info;
    std::map<string/*�������� ��������*/, std::pair<std::list<int> /*������ ������*/, float /*������� ������*/>> subjMark;

    string buildMessageString();

public:
    StudentInfo(string fullName, string name, char* studentId) {
        info = { fullName, name, studentId };
    }

    /*	desription	:	���������� ������� �� ���������� ��������
        input		:	subjName - �������� ��������, mark -- ������
        output		:	0 - ������ ���������, 1 - ��� ������ ��������
        author		:
        date		:
    */
    int addMark(const string& subjName, int mark);

    /*	desription	:	���������� ������� �� ���������� ��������
        input		:	subjName - �������� ��������
        output		:	0 - ������� ��������, 1 - ����� ������� ��� ����
        author		:
        date		:

    */
    int addSubj(const string& subjName);

    /*	desription	:	���������� ������ ��������
        input		:	subjName - �������� ��������
        output		:	������� �������� ������
        author		:
        date		:
    */
    float getAverMark(const string& subjName);

    /*	desription	:	���������� ������� ������ �� ���������
        input		:	subjName - �������� ��������
        output		:	������� �������� ������
        author		:
        date		:
    */
    void printInfoStudent();

    /*	desription	:	������ ������ � ���� ������ �����
                            [�������] [���] : [����� ������]
                                [������� 1]	:	[������ 1], [������ 2],... [������ N] -- [������� ��������]
                                [������� 2]	:	[������ 1], [������ 2],... [������ N] -- [������� ��������]
        input		:	subjName - �������� ��������
        output		:	������� �������� ������
        author		:
        date		:
    */
    void writeAllInfoToFile();
};