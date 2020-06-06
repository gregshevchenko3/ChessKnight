// ChessKnight.cpp : Defines the entry point for the application.
//

#include "ChessKnight.h"
#include <vector>


const int BOARD_SIZE = 4;
using coord_t = struct {
	int x, y;
};
using path_t = std::vector<coord_t>;
using board_t = int[BOARD_SIZE][BOARD_SIZE];

path_t move(path_t prev, int move_count = BOARD_SIZE * BOARD_SIZE);
inline bool check_board_border(path_t& path);
bool check_cell(path_t& path);

int main()
{
	path_t path;
	coord_t start = {1, 0};
	path.push_back(start);
	path = move(path);


	auto it = path.begin();
	while (it != path.cend()) {
		std::cout << (char)(it->x + 'a') << it->y +1 << "->";
		it++;
	}
	std::cout << std::endl;
	std::system("pause");
	return 0;
}
// Чи не вийшли за границі шахової дошки
inline bool check_board_border(path_t& path) {
	return path.back().x >= 0 && path.back().x < BOARD_SIZE &&
		path.back().y >= 0 && path.back().y< BOARD_SIZE;
}
// Чи була клітина занята раніше.
bool check_cell(path_t& path) {
	coord_t coord = path.back();
	auto it = path.begin(), end = path.end(); end--;
	while (it != end) {
		if (it->x == coord.x && it->y == coord.y) 
			return false;
		it++;
	}
	return true;
}

path_t move(path_t prev, int move_count)
{
	path_t res = path_t();
	for (int x = -2; x <= 2; x ++) 
	{
		if (x == 0) continue;					// Кінь по горизонталі не ходе
		for (int y = -2; y <= 2; y++)
		{
			if (x == y || x == -y || y == 0) continue; // Кінь не ходе по вертикалі та по діагоналям.
			path_t new_branch(prev), res1;
			new_branch.push_back({new_branch.back().x + x, new_branch.back().y+y});

			if (!check_board_border(new_branch) || !check_cell(new_branch)) {
				new_branch.pop_back();
				continue;
			}
			res1 = move(new_branch, move_count - 1);
			if (res1.size() > res.size()) res = res1;
		}
	}
	if (res.empty())
		res.push_back(prev.back());
	else
		res.insert(res.begin(), prev.back());
	return res;
}