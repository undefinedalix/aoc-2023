#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Count = unsigned int;

class Set {
	Count _reds;
	Count _greens;
	Count _blues;

	void parseColors(const std::string& str) {
		std::stringstream stream(str);
		Count number;
		std::string color;
		stream >> number >> color;
		if (color == "red")
			_reds = number;
		else if (color == "blue")
			_blues = number;
		else if (color == "green")
			_greens = number;
	}
	public:
	  Set(const std::string& description) : _reds(0u), _greens(0u), _blues(0u) {
			size_t start = 0u;
			size_t end = description.find(',');
			while (end != description.npos) {
				parseColors(description.substr(start, end-start));
				start = end+1;
				end = description.find(',', start);
			}
			parseColors(description.substr(start));
		}
		Count reds() const {
			return _reds;
		}
		Count blues() const {
			return _blues;
		}
		Count greens() const {
			return _greens;
		}
};

class Game {
	Count _reds;
	Count _greens;
	Count _blues;
	public:
	  Game(const std::string& description) : _reds(0u), _greens(0u), _blues(0u) {
			std::cout << "Parsing game: " << description << "\n";
			size_t start = 0u;
			size_t end = description.find(';');
			while (end != description.npos) {
				Set set(description.substr(start, end-start));
				_reds = std::max(_reds, set.reds());
				_greens = std::max(_greens, set.greens());
				_blues= std::max(_blues, set.blues());
				start = end+1;
				end = description.find(';', start);
			}
			Set set(description.substr(start));
			_reds = std::max(_reds, set.reds());
			_greens = std::max(_greens, set.greens());
			_blues= std::max(_blues, set.blues());
		}
		Count red() const {
			return _reds;
		}
		Count green() const {
			return _greens;
		}
		Count blue() const {
			return _blues;
		}
		unsigned int power() const {
			return _reds * _greens * _blues;
		}
		friend std::ostream& operator<<(std::ostream& stream, const Game& game) {
			stream << game._reds << "R, " << game._greens << "G, " << game._blues << "B";
			return stream;
		}
};

using ID = unsigned int;
ID parseLine(const std::string& line) {
	size_t pos = line.find(":");
	auto identifier = line.substr(0, pos);
	Game game(line.substr(pos+1));
	std::cout << identifier << " -> " << game << "\n";
	if (game.red() <= 12 && game.blue() <= 14 && game.green() <= 13) {
		std::stringstream stream(identifier);
		std::string ignore;
		ID id;
		stream >> ignore >> id;
		return id;
	}
	return 0u;
}

unsigned parsePower(const std::string& line) {
	size_t pos = line.find(":");
	Game game(line.substr(pos+1));
	return game.power();
}

int main() {
	const char *inputPath{"resources/input_02.txt"};

	std::ifstream file{inputPath};
	if (!file) {
		std::cerr << "Could not open " << inputPath << "\n";
		return -1;
	}

	Count sum = 0u;
	unsigned int power = 0u;
	for (std::string line; std::getline(file, line);) {
		sum += parseLine(line);
		power += parsePower(line);
	}
	std::cout << "sum: " << sum << "\n";
	std::cout << "power: " << power << "\n";
}
