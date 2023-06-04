#include "../NativeClasses/pch.h"
#include "../NativeClasses/MException.h"
#include "../NativeClasses/CMap.h"
#include "../NativeClasses/parseOut.h"
#include "Task8.h"

std::pair <int, int> INF (10000, 10000); //����, ������������,��� ���� � ��� ������� �� �� ��������
const int IINF = 100000; //���� � ������������ ������

Task8::Task8(int argc, char** argv) {
	this->keys();
	if (!this->parseFlags(argc, argv)) {
		throw MException("�� ������� ��������� �����!");
	}
	else {
		/* ������� ���� ��� ������ ���� �� ���� */
		if (this->getOutputFlag()) {
			std::ofstream output;
			output.open(this->getCurrentOutputPath());
			output.close();
		}

		CMap MyMap(this->getCurrentPath());

		for (int i = 0; i < MyMap.getMap().size(); i++) {
			for (int j = 0; j < MyMap.getMap()[i].size(); j++) {
				std::cout << MyMap.getMap()[i][j] << " ";
			}
			std::cout << std::endl;
		}

		this->findPath(MyMap);
	}
}

/* ����� ���� */
void Task8::findPath(CMap & MyMap) {

	/* ���������� ������� �� ������� ������ � ���� ������� */
	std::vector < std::pair <int, std::pair <int, int> > > frontier;

	/* ��������� � ������� ��������� �������*/
	frontier.push_back(std::make_pair(0, this->beginCell));

	/* ����� ������ � �������������� �����, ���������� ��, ������ �� ������ � ��� ������ */
	std::map <std::pair <int, int>, std::pair <int, int> > came_from;
	came_from[this->beginCell] = this->beginCell;

	/* ����� ������ � ��� ���������, ������������ ���. ���������� �� ���� ������ */
	std::map <std::pair <int, int>, int> distancies;
	distancies[this->beginCell] = 0;

	while (!frontier.empty()) {
		auto currentCellAndPriority = frontier.front();
		frontier.erase(frontier.begin());

		auto currentCell = currentCellAndPriority.second;

		if (currentCell == this->endCell) {
			break;
		}

		for (int p = 0; p < MyMap.neighbors(currentCell).size(); p++) {
			auto neighbor = MyMap.neighbors(currentCell)[p];
			int newDistance = distancies[currentCell] + this->getRange(MyMap, currentCell, neighbor);
			if (!came_from.count(neighbor)) {
				int priority = newDistance + this->hManhatton(neighbor, this->endCell);
				distancies[neighbor] = newDistance;
				came_from[neighbor] = currentCell;
				frontier.push_back(std::make_pair(priority, neighbor));
				std::sort(frontier.begin(), frontier.end());
			}
		}
	}

	auto from = this->endCell;
	std::vector < std::pair <int, int> > path;
	path.push_back(from);
	while (from != this->beginCell) {
		from = came_from[from];
		path.push_back(from);
	}

	std::reverse(path.begin(), path.end());

	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i].first << " - " << path[i].second << std::endl;
	}

	std::cout << "\n\n" << distancies[this->endCell];
}

int Task8::getRange(CMap& MyMap, std::pair <int, int> start, std::pair <int, int> end) {
	int startHeight = MyMap.getMap()[start.first][start.second];
	int endHeight = MyMap.getMap()[end.first][end.second];
	int range = abs(end.first - start.first) + abs(end.second - start.second) + abs(endHeight - startHeight);
	return range;
}

/* ������������� ���������� */
int Task8::hManhatton(std::pair <int, int> start, std::pair <int, int> end) {
	int distance = abs(start.first - end.first) + abs(start.second - end.second);
	return distance;
}

/* ��������������� ������*/
void Task8::keys() {
	this->TaskKeys.insert(std::pair < std::string, std::string>("-m", "matrix_file_path"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-n", "begin_coordinate"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-d", "end_coordinate"));
	this->TaskKeys.insert(std::pair < std::string, std::string>("-o", "output_file_path (NOT REQUIRED)"));
}

/* ������� ������ */
bool Task8::parseFlags(int argc, char** argv) {
	if (argc >= 3) {
		int mainFlagsC = 0;
		int BEFlags = 0;
		for (int i = 1; i < argc; i++) {
			if (i != argc - 1) {
				if (strcmp(argv[i], "-m") == 0) {
					this->currentPath = argv[i + 1];
					mainFlagsC++;
				}
				else if (strcmp(argv[i], "-n") == 0) {
					this->beginCell.first = atoi(argv[i + 1]);
					this->beginCell.second = atoi(argv[i + 2]);
					BEFlags++;
				}
				else if (strcmp(argv[i], "-d") == 0) {
					this->endCell.first = atoi(argv[i + 1]);
					this->endCell.second = atoi(argv[i + 2]);
					BEFlags++;
				}
			}

			if (strcmp(argv[i], "-h") == 0) {
				this->Help();
				return false;
			}
		}

		if (mainFlagsC != 1 || this->currentPath == "" || BEFlags != 2) {
			return false;
		}

		return true;
	}
	else {
		return false;
	}
}