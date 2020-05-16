#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

using byte = signed char;

struct point {
	byte x;
	byte y;

	point& operator=(const point& pnt) {
		this->x = pnt.x;
		this->y = pnt.y;
		return *this;
	}

	point up() const {
		return point{ x + 1, y };
	}

	point down() const {
		return point{ x - 1, y };
	}

	point left() const {
		return point{ x, y - 1 };
	}

	point right() const {
		return point{ x, y + 1 };
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
};

ostream& operator<<(ostream& out, const point& pnt) {
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

vector<point> find_finish(const int(&map)[9][9], int player_number) {
	byte x = (player_number == 1 ? 8 : 0);
	vector<point> res;
	byte min_val = byte(min_element(&(map[x][0]), &(map[x][9])));
	for (byte y = 0; y < 9; y++) {
		if (map[x][y] == min_val)
			res.push_back(point{ x, y });
	}
	return res;
}

byte foo(const way& player_1, const way& player_2) {
	byte size_1 = player_1.size();
	byte size_2 = player_2.size();
	for (size_t i = 0; i < min(size_1, size_2) - 1; i++) {
		if (player_1[i + 1] == player_2[i + 1]) {
			size_2--;
			break;
		}
		else if (player_1[i + 1] == player_2[i]) {
			size_1--;
			break;
		}
	}
	return size_1 - size_2;
}

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

int main() {

	cout << setw(2) << 1 << endl;

	vector<border> arr;
	arr.push_back({ {3,3}, {3,5} });
	arr.push_back({ {1,5}, {3,5} });
	arr.push_back({ {2,5}, {2,7} });
	arr.push_back({ {3,6}, {3,8} });
	arr.push_back({ {1,8}, {3,8} });
	arr.push_back({ {3,5}, {5,5} });
	arr.push_back({ {5,5}, {7,5} });
	arr.push_back({ {7,5}, {7,7} });
	arr.push_back({ {7,7}, {5,7} });
	arr.push_back({ {5,7}, {5,9} });
	arr.push_back({ {5,9}, {3,9} });


	auto beg = chrono::steady_clock::now();
	// CODE
	auto end = chrono::steady_clock::now();
	int time = chrono::duration_cast<chrono::milliseconds> (end - beg).count();
	cout <<"Elapsed time: "<< time << endl;
	return 0;
}
