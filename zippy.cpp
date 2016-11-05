#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

class File {
	int freq[256];

	typedef std::pair<int, char> pic;

public:
	std::ifstream file;

	File(std::string filePath) {
		file.open(filePath);

		getCharFreq();
		getCodification();
	}

	void getCharFreq() {
		memset(freq, 0, sizeof(freq));
		char c;
		while(file>>std::noskipws>>c) {
			++freq[c];
		}
	}

	pic extractFrom(std::queue<pic>& queue) {
		pic p = queue.front();
		queue.pop();
		return p;
	}

	pic getMin(std::queue<pic>& queue1, std::queue<pic>& queue2) {
		if(queue1.empty())
			return extractFrom(queue2);
		if(queue2.empty())
			return extractFrom(queue1);

		if(queue1.front().first <= queue2.front().first)
			return extractFrom(queue1);
		else
			return extractFrom(queue2);
	}

	void getCodification() {
		std::queue<pic> queue1, queue2;

		std::vector<pic> nonZeroFreq;

		for(int i = 0; i < 256; ++i) {
			if(freq[i]) {
				nonZeroFreq.push_back(std::make_pair(freq[i], (char)i));
			}
		}

		if(nonZeroFreq.size() > 1) {
			std::sort(nonZeroFreq.begin(), nonZeroFreq.end());

			for(auto it : nonZeroFreq) {
				queue1.push(it);
			}
		}
		else {
			queue2.push(nonZeroFreq[0]);
		}

		while(queue1.size() + queue2.size() > 1) {
			pic min1 = getMin(queue1, queue2);
			pic min2 = getMin(queue1, queue2);
			pic result = std::make_pair(min1.first + min2.first, 0);
			queue2.push(result);
		}
	}
};

int main(int argc, char** argv) {
	File f("testfile");

	return 0;
}
