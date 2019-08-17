#include <SFML/Graphics.hpp>
#include <string>
#include "SortingVisualized.h"
using namespace std;

void quickSort(vector<int>::iterator begin, vector<int>::iterator end) {
	if (end == begin) 
		return;
	
	//int pivot = *next(begin, distance(end, begin)/2);
	//+Random().getIntInRange(0, (end - begin - 1))
	int pivot =  Random().getIntInRange(0, end - begin - 1);
	auto bound = partition(begin, end, [&](int value) {return value < *(begin+pivot); });
	quickSort(begin, bound);
	quickSort(bound + 1, end);
}

int main() {
	SortingVisualized sort(1500, 900, 1000);
	/*vector<int> nums{ 5, 3, 7, 1, 8, 9 , 3, -1, -5 };
	vector<string> names{ "Darien", "Lissa", "Xiang", "Mermelstein", "Moses", "Denise", "Dalton" };
	vector<RectangleShape> rects{ RectangleShape(Vector2f(20, 170)), RectangleShape(Vector2f(20, 100)), RectangleShape(Vector2f(20, 80)) };

	mergeSort(rects.begin(), rects.end());
	for (auto &i : rects){cout<<  "width: " << i.getSize().x << " and height: " << i.getSize().y << " ";}*/
	sort.run();
	
}