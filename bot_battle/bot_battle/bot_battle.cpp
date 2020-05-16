#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using std::vector;
using byte = signed char;
using std::string;
using std::cout;
using std::cin;
using std::endl;



struct BoardState {
	vector<border> borders;
	point first_player;
	point second_player;
};

struct point {
	byte x;
	byte y;

	point up() const {
		return point{ x + 1, y };
	}

	point down() const {
		return point{ x - 1, y };
	}

	point left() const {
		return point{ x, y - 1};
	}

	point right() const {
		return point{ x, y + 1};
	}

	bool is_ok() const {
		if (x < 0 || y < 0) {
			return false;
		}
		if (x > 9 || y > 9) {
			return false;
		}

		return true;
	}

	point& operator=(const point& pnt) {
		this->x = pnt.x;
		this->y = pnt.y;
		return *this;
	}
};

std::ostream& operator<<(std::ostream& out, const point& pnt) {
	out << "(" << pnt.x << ", " << pnt.y << ")";
	return out;
}

bool operator==(const point& lhs, const point& rhs) {
	return(lhs.x == rhs.x && lhs.y == rhs.y);
}

struct border {
	point beg;
	point end;
};

using way = vector<point>;

bool is_neighbours(const point& first, const point& second, const vector<border>& borders) {
	byte dx{ 0 }, dy{ 0 };
	for (const border& bord : borders) {
		dx = bord.end.x - bord.beg.x;
		dy = bord.end.y - bord.beg.y;
		if (dx == 0 && dy == 2) {
			if (first.down() == second && (first == bord.beg || first == bord.beg.right()))
				return false;
			else if (second.down() == first && (second == bord.beg || second == bord.beg.right()))
				return false;
		}
		else if (dx == 0 && dy == -2) {
			if (first.down() == second && (first == bord.end || first == bord.end.right()))
				return false;
			else if (second.down() == first && (second == bord.end || second == bord.end.right()))
				return false;
		}
		else if (dx == 2 && dy == 0) {
			if (first.left() == second && (first == bord.beg || first == bord.beg.up()))
				return false;
			else if (second.left() == first && (second == bord.beg || second == bord.beg.up()))
				return false;
		}
		else if (dx == -2 && dy == 0) {
			if (first.left() == second && (first == bord.end || first == bord.end.up()))
				return false;
			else if (second.left() == first && (second == bord.end || second == bord.end.up()))
				return false;
		}
	}
	return true;
}

vector<point> find_finish(const int(&map)[9][9], int player_number) {
	byte x = (player_number == 1 ? 8 : 0);
	vector<point> res;
	byte min_val = std::min({ map[x][0], map[x][1], map[x][2], map[x][3], map[x][4], map[x][5], map[x][6], map[x][7], map[x][8] });;
	for (byte y = 0; y < 9; y++) {
		if (map[x][y] == min_val)
			res.push_back(point{ x + 1, y + 1 });
	}
	return res;
}

vector<way> shortest_way(vector<border> borders, point player_position, int player_number) {
	int field[9][9] = { 0 };
	field[player_position.x-1][player_position.y-1] = 1;

	vector<point> search{player_position};
	byte current = 0;

	while (current < search.size())
	{
		point now = search[current++];

		for (const auto& next : { now.up(), now.down(), now.left(), now.right() }) {

			if (next.is_ok() && field[next.x - 1][next.y - 1] == 0 && is_neighbours(now, next, borders)) {
				search.push_back(next);
				field[next.x - 1][next.y - 1] = field[now.x - 1][now.y - 1]+1;
			}

		}
	}
	
	for (int x = 9; x > 0; x--) {
		for (int y = 0; y < 9; y++)
			std::cout << std::setw(2) << field[x-1][y] << ' ';
		std::cout << std::endl;
	}

	vector<way> ways;
	for (auto& finish : find_finish(field, player_number)) {
		way my_way{ finish };
		while (field[finish.x - 1][finish.y - 1] != 1)
		{
			for (const auto& my_point : { finish.up(), finish.down(), finish.left(), finish.right() }) {
				if (field[my_point.x - 1][my_point.y - 1] == field[finish.x - 1][finish.y - 1] - 1) {
					my_way.push_back(my_point);
					finish = my_point;
					break;
				}
			}
		}
		ways.push_back(my_way);
	}
	return ways;
}


string our_move(BoardState& board_state, int player_number) {
	return " ";
}

void round(BoardState& board_state, int player_number)
{
	if (player_number == 1)
		cout << our_move(board_state, player_number) << endl;

	string opponents_move;
	cin >> opponents_move;

	if (opponents_move == "move") {

	}
	else {

	}

	if (player_number == 2)
		cout << our_move(board_state, player_number) << endl;

}

int main()
{
	int player_number;

	BoardState board_state;

	cin >> player_number;
	while (true) {
		round(board_state, player_number);
	}

}