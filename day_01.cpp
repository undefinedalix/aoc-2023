#include <fstream>
#include <iostream>
#include <map>
#include <vector>

std::map<size_t, unsigned int> lineDigits(const std::string& line) {
	const std::map<std::string, unsigned int> lettersToDigit = {
	  {"one", 1}, {"two", 2}, {"three", 3},
	  {"four", 4}, {"five", 5}, {"six", 6},
	  {"seven", 7}, {"eight", 8}, {"nine", 9},
	  {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4},
	  {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}
	};

	std::map<size_t, unsigned int> digits;
	for (const auto& key : lettersToDigit) {
		size_t pos = line.find(key.first);
		while (pos != line.npos) {
			digits.insert({pos, key.second});
			pos = line.find(key.first, pos+1);
		}
	}
	return digits;
}

int lineValue(const std::string& line) {
	auto digits = lineDigits(line);
	return digits.begin()->second * 10 + digits.rbegin()->second;
}

int main() {
	const char *inputPath{"resources/input_01.txt"};

	std::ifstream file{inputPath};
	if (!file) {
		std::cerr << "Could not open " << inputPath << "\n";
		return -1;
	}

	unsigned int sum = 0u;
	std::string line;
	while (file >> line) {
		sum += lineValue(line);
	}
	std::cout << "Sum: " << sum << "\n";

	return 0;
}
