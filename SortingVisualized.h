#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Random.h"
#include <unordered_map>
#include <SFML/Graphics.hpp>

/*
* Class that will defined a an object containing the ability to print to the screen a series of rectangles with random lengths. 
* Once "showSorting()" is called, the sorting algortihm will then sort the rectangles from smallest to largest based on their heights.
*/
class SortingVisualized{
	public:

		//the user will pass in the height and width of the window, as well as the number of rectangles to be shown onto the screen.
		//If a variable is not given, the constructor will default to 100 rectangles.
		class SortingVisualized (int windowWidth, int windowHeight, int numRectangles = 100);

		//function to print the rectangles to the screen.
		void run();
		
	private:
		void showSorting();
		void stateManager();
		bool isTextClicked(const sf::Text &text);
		void randomizeRectangles();
		
		//Returns the y position of lower bound of the rectangle surrounding the text
		float getTextBottomEdge(const sf::Text &text);
		void drawMenu();
		void createMenu();
		void bubbleSort();
		void selectionSort();
		void insertionSort();
		void cockTailSort();
		void merge();
		void mergeSort(std::vector<sf::RectangleShape>::iterator begin, std::vector<sf::RectangleShape>::iterator end);
		int parition();
		void quickSort();
		void swapRectXPosition(sf::RectangleShape &rectOne, sf::RectangleShape &rectTwo);
		void drawRectangles();
		sf::Text createText(const std::string &word, int textSize, const sf::Text::Style &style, const sf::Vector2f &position);
	private:
		enum class states{MENU, QUICK_SORT, MERGE_SORT, BUBBLE_SORT, SELECTION_SORT, INSERTION_SORT, COCKTAIL_SORT, EXIT};
		states currentState;
		std::vector<sf::RectangleShape> rectangles;
		std::unordered_map<states, sf::Text> menuAssets;
		sf::RenderWindow window;
		sf::Font font;
		Random rand;

};

