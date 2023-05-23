#include "tasks_rk1.h"

#include <fstream> // ������������ ���� ��� ������ � �������
#include <iostream>
#include <sstream>

using namespace std;

WorkWithFile::WorkWithFile() { // ����������� �� ���������
    dataOfFile = nullptr;
}

WorkWithFile::~WorkWithFile() { // ����������
    if (dataOfFile != nullptr) {
        delete[] dataOfFile;
    }
}

void WorkWithFile::readFromFile(const char* fileName) {
    ifstream in(fileName, ios::in);

    if (in.is_open()) { // ���� �������� ����� �������� ���������
        // ����������� ������� �����
        in.seekg(0, in.end); // ������������� ��������� � ����� �����
        int fileSize = in.tellg(); // �������� �������� ������� �������
        in.seekg(0, in.beg); // ���������� ��������� � ������ �����

        // ��������� ������ ��� ���������� �����
        dataSize = fileSize;
        dataOfFile = new char[dataSize + 1];

        // ������ ����������� �����
        in.read(dataOfFile, fileSize);

        in.close(); // ��������� �������� �����
    }
}

void WorkWithFile::prepareTestFile(
    const char* fileName) { // �� �����, ��� ���� ����� ��� �������, ������� ������ ��������� �� ����� � ������� � ����� ����
    ofstream out(fileName, ios::out);

    if (out) { // ���� �������� ����� �������� ���������
        out.write(dataOfFile, dataSize);
        out.close();
    }
}

void WorkWithFile::countSymbolFrequency() {
    if (dataOfFile != nullptr) {
        char currentChar;

        for (int i = 0; i < dataSize; i++) { // �����������, ���� �� �������� ����-��������
            currentChar = dataOfFile[i];
            if (symbolsFrequency.find(currentChar) ==
                symbolsFrequency.end()) { // ���� �� �����. symbolsFrequency.find ���������� end(),
                // ���� ����� �������� �� �������
                symbolsFrequency[currentChar] = 1;
            }
            else {
                symbolsFrequency[currentChar]++; //  ���� ����� ������ �����, �� ���������� � ���� � ������� � �������������� ��� ��������
            }
        }
    }

}


void WorkWithFile::writeStatInfoToFile(const char* outFile) {
    readFromFile("sourceFile_task1.txt"); // ��������� ������ �� �����

    countSymbolFrequency(); // ������������ ����������� ��� ������� �������

    ofstream out(outFile, ios::out); //  ��������� �������� �����
    if (out) { // ���� �������� ����� �������� ���������
        for (auto it = symbolsFrequency.begin();
            it != symbolsFrequency.end(); it++) { // ����������� �� ������� � ������������ ��������
            out << it->first << "\t" << it->second << "\n"; // ������� ������ �� ���������� �������
        }
        out.close();
    }
}

char* convertDecToBin(int number) {
    bool isNegative = false; // ���� ��� ������������� �����
    if (number < 0) {
        isNegative = true;
        number = -number;
    }
    else if (number == 0) { // �������� ������������ ������, ����� ������� �������� ����� ����
        // ������ ������� ������ � �������� � ���� 0. ����� ������� 2, �.�. � ������ ������ ���� ������ ���� � ����-�������� "\0"
        char* res = new char[2];
        res[0] = '0';
        return res;
    }

    int binaryArray[32]; // ������ ��� �������� �������� ������ �����
    int i = 0;

    // ������� ����� � �������� �������
    while (number > 0) {
        binaryArray[i] = number % 2; //���������� � ��������������� ������� ������� �� ������� �� 2
        number /= 2;
        i++;
    }

    if (isNegative) { // ���� �������� ����� ������ ����
        for (int j = 0; j < i; j++) {
            binaryArray[j] = !binaryArray[j]; // ����������� ���� 0 => 1, 1 => 0
        }

        // �������� �������� ������������� �������������� �����
        int carry = 1;
        int k = 0;
        while (carry && k < 32) {
            int temp = binaryArray[k] + carry;
            binaryArray[k] = temp % 2;
            carry = temp / 2;
            k++;
        }
    }

    // ���������� ���� � �������� �������
    char* reversedBinaryArray = new char[32];
    int indexReversedArray = 0;
    for (int j = i - 1; j >= 0; j--) {
        reversedBinaryArray[indexReversedArray] = binaryArray[j] == 1 ? '1' : '0';
        ++indexReversedArray;
    }

    return reversedBinaryArray;
}

char* convertBinToHex(const char* binNum) {
    string binary = string(binNum);

    int len = binary.length();
    string hex;
    int i = 0;

    // ���� ����� ��������� ����� �� ������ 4, ��������� ��� ����� ������ �� ��������� 4.
    if (len % 4 != 0) {
        while (i < (4 - len % 4)) {
            binary = "0" + binary;
            i++;
        }
    }

    len = binary.length();
    i = 0;

    // �������� �� ��������� ����� �� 4 ������� � ������������ �� � ����������������� �������������.
    while (i < len) {
        string nibble = binary.substr(i,
            4); // ����� ��������� 4 �������, ������������ �������� 1111 � ��������, ��� ��������� 15 � ����������
        int decimal = stoi(nibble, nullptr, 2); // ������������ �� ��������� ����� � ����������

        if (decimal <= 9) {
            hex += to_string(decimal);
        }
        else {
            hex += (char)(decimal - 10 +
                'A'); // ���� ����� ����������, �� ��������� ��� �������� ������������ ������� �.
            // � ascii ������� ����������� ���������������, ��� ��������� ����������� ������� � ��������� ������ ��������
        }

        i += 4; // 4 �.�. ����� ��������� ������� 4
    }

    char* result = new char[hex.size()]; // �������� � �� ������, ������ ��� string.c_str() ���������� ����������� ������,
    // ��� �� �������� ��� ��� ������������� �������� �������
    for (int i = 0; i < hex.size(); ++i) {
        result[i] = hex[i];
    }

    return result;
}

void writeToFile(const char* fileName, int writeAppend, const char* hexNum, const char* binNum) {
    ofstream out_file(fileName); // ��������� �������� ����� �� ������

    if (out_file) {
        out_file << binNum << "\t" << hexNum << endl;

        out_file.close();
    }
}

// ������� ������ ������ � ����
void writeToFile(const char* fileName, const char* strNum) {
    ofstream outFile(fileName); // ��������� ���� ��� ������

    if (outFile.is_open()) { // ���� ���� ������� ������
        outFile << strNum; // ���������� ������ � ����
        outFile.close(); // ��������� ����
        cout << "��������� ������� � ���� " << fileName << endl;
    }
    else { // ���� ��������� ������ ��� �������� �����
        cout << "�� ������� ������� ���� " << fileName << " ��� ������" << endl;
    }
}

void buildTree(int height) {
    for (int layer = height; layer > 0; --layer) { /* ���� � ���, ��� ��� ���� ��������� ������� �� ������ ���� ��� (�������_������_���� - 1)
 *    ����� �������, ������ ���� � �� ������� � �� ���������
        */
        for (int i = 0; i < layer; ++i) { // ���������� ������ ���������� ��������
            cout << " ";
        }

        for (int i = 0; i < (height - layer) * 2 + 1; i++) { // ���������� ��������� (height - layer) * 2 + 1 ��������
            // ���������� ��������
            cout << "*";
        }

        // ������� ������ ����� ������� ����
        cout << endl;
    }
}

std::vector<std::pair<int, float>> averStr2DArray(float** arr, int colCount, int rowCount) {
    vector<pair<int, float>> result; // ������, � ������� ����� ��������� ������� �������� ��������� ������ ������

    for (int row = 0; row < rowCount; ++row) { // ���� �� �������
        float row_sum = 0; // ���������� ��� �������� ����� ��������� ������

        for (int column = 0; column < colCount; ++column) { // ���� �� ��������
            row_sum += arr[row][column];
        }

        result.push_back(pair<int, float>(row, row_sum /
            (float)colCount)); // ��������� ���� "������"-"��������" � ������. ���������� ��� �������,������ ��� �� ��������� ��� �����
    }

    return result;
}

void randFill(float** arr, int colCount, int rowCount) {
    if (colCount == 0 || rowCount == 0) { // ������������ ������� ��������� ������
        cout << "Columns count and rows count must be greater than zero" << endl;
        return; // return ������, ������ ��� ������� ����� ��� ������������� ��������� - void
    }

    // ������������ ������, ����� ��� ������ �� ���� �������� ������. ��� ������������ - ����� �������� ������
    if (arr == nullptr) {
        cout << "Invalid array" << endl;
        return; // return ������, ������ ��� ������� ����� ��� ������������� ��������� - void
    }

    // ���������� �� �������, �������������� ���������� ���������� �� 1 �� 10
    for (int row = 0; row < rowCount; ++row) { // ���� �� �������
        for (int column = 0; column < colCount; ++column) { // ���� �� ��������
            arr[row][column] = rand() % 10 + 1;
        }
    }
}

LinkedList::LinkedList() {
    Head = Tail = nullptr;
    nodesAmount = 0;
}

LinkedList::~LinkedList() {
    Node* iter = Head;
    while (iter) {
        Node* temp = iter;
        iter = iter->next;

        delete temp;
    }
}

void LinkedList::push_back(int nameNode) {
    if (!Head) {
        Tail = Head = new Node{ nullptr, nullptr, ++nameNode };
    }
    else if (Head == Tail) {
        Tail = new Node{ nullptr, Head, ++nameNode };
        Head->next = Tail;
    }
    else {
        Tail = new Node{ nullptr, Tail, ++nameNode };
        Tail->prev->next = Tail;
    }

    ++nodesAmount;
}

void LinkedList::writeToFileFromHead() {
    ofstream out_file("fromHead.txt");

    if (out_file) {
        Node* iter = Head;
        while (iter) {
            out_file << iter->nameNode;

            if (iter->next) {
                out_file << ";";
            }

            iter = iter->next;
        }

        out_file.close();
    }
}

void LinkedList::writeToFileFromTail() {
    ofstream out_file("fromTail.txt");

    if (out_file) {
        Node* iter = Tail;

        while (iter) {
            out_file << iter->nameNode;

            if (iter->prev) {
                out_file << ";";
            }

            iter = iter->prev;
        }

        out_file.close();
    }
}

void LinkedList::insert(int nameNode, int position) {
    if (position >= 0 && position <= nodesAmount) {
        Node* newNode = new Node{ nullptr, nullptr, nameNode };

        if (position == 0) { // ���������� � ������ ������
            newNode->next = Head;

            if (Head) {
                Head->prev = newNode;
            }

            Head = newNode;
            if (!Tail) {
                Tail = newNode;
            }
        }
        else if (position == nodesAmount) { // ���������� � ����� ������
            Tail->next = newNode;
            newNode->prev = Tail;
            Tail = newNode;
        }
        else { // ���������� � �������� ������
            int index = 0;
            Node* iter = Head;

            while (iter && index < position) {
                iter = iter->next;
                index++;
            }

            newNode->prev = iter->prev;
            newNode->next = iter;
            iter->prev->next = newNode;
            iter->prev = newNode;
        }

        ++nodesAmount;
    }
}

/*	desription	:	���������� ������� �� ���������� ��������
    input		:	subjName - �������� ��������, mark -- ������
    output		:	0 - ������ ���������, 1 - ��� ������ ��������
    author		:
    date		:
*/
int StudentInfo::addMark(const string& subjName, int mark) {
    if (subjMark.find(subjName) != subjMark.end()) { // ���� ����� ������� ����������
        pair<list<int>, float>& pair = subjMark.at(subjName); // �������� ������ �� ���� "������ ������" - "������� ������"

        pair.first.push_back(mark); // ��������� ����� ������ � ������ ������

        // �������� ������
        int sum = 0;
        for (auto& val : pair.first) {
            sum += val;
        }

        pair.second = (float)sum / (float)pair.first.size();

        return 1;
    }

    return 0;
}

/*	desription	:	���������� ������� �� ���������� ��������
    input		:	subjName - �������� ��������
    output		:	0 - ������� ��������, 1 - ����� ������� ��� ����
    author		:
    date		:

*/
int StudentInfo::addSubj(const string& subjName) {
    if (subjMark.find(subjName) == subjMark.end()) { // ���� ������ �������� ���
        subjMark.insert({ subjName, {{}, 0} }); // ������� ���� "�������� ��������" - "���� "������ ������ ������" - "������� ������""

        return 1;
    }

    return 0;
}

/*	desription	:	���������� ������ ��������
    input		:	subjName - �������� ��������
    output		:	������� �������� ������
    author		:
    date		:
*/
float StudentInfo::getAverMark(const string& subjName) {
    if (subjMark.find(subjName) != subjMark.end()) { // ���� ����� ����� �������
        return subjMark.at(subjName).second; // ���������� ������� �������� ������
    }

    return 0;
}

string StudentInfo::buildMessageString() { // ��������� �������, ����� ���������������� � � printInfoStudent � � writeAllInfoToFile
    // ��������� ��������� �� ������ �������
    stringstream sstream; // ����� ��� ����������� ������

    sstream << '[' << get<0>(info) << "] [" << get<1>(info) << "] : " << get<2>(info) << "\n"; // �������� �������� �� ����� (�������, ���, �������)

    for (auto iter = subjMark.begin(); iter != subjMark.end(); ++iter) { // ����������� �� �������
        sstream << "\t" << iter->first << " : "; // �������� �������� �������� ������ � �������

        list<int>& marks = iter->second.first; // ������� ���������� - ������ �� ������ ������, ��� ��������
        for (auto marksIter = marks.begin(); marksIter != marks.end(); ++marksIter) { // ����������� �� ������ ������
            sstream << *marksIter;

            if (next(marksIter) != marks.end()) { // �������, ����� ����� ��������� ������ �� ���� �������
                sstream << ", ";
            }
            else {
                sstream << " -- "; // �������, ����� ����� ��������� ������ ��������� �������������� ������� "--" (��� � �������)
            }
        }

        sstream << iter->second.second << endl; // ���������� ������� ������ �� �������� � ������� �� ����� ������
    }

    return sstream.str(); // ���������� ������
}

/*	desription	:	���������� ������� ������ �� ���������
    input		:	subjName - �������� ��������
    output		:	������� �������� ������
    author		:
    date		:
*/
void StudentInfo::printInfoStudent() {
    cout << buildMessageString();
}


/*	desription	:	������ ������ � ���� ������ �����
                        [�������] [���] : [����� ������]
                            [������� 1]	:	[������ 1], [������ 2],... [������ N] -- [������� ��������]
                            [������� 2]	:	[������ 1], [������ 2],... [������ N] -- [������� ��������]
    input		:	subjName - �������� ��������
    output		:	������� �������� ������
    author		:
    date		:
*/
void StudentInfo::writeAllInfoToFile() {
    ofstream out_file("student_data.txt");

    if (out_file) {
        out_file << buildMessageString();

        out_file.close();
    }
}