#include "SortingVisualized.h"
#include <algorithm>

SortingVisualized::SortingVisualized(int windowWidth, int windowHeight, int numRectangles) : window(sf::VideoMode(windowWidth, 
	windowHeight), "Sorting", sf::Style::Close | sf::Style::Titlebar), currentState(states::MENU){

	if (!font.loadFromFile("C:\\Users\\Darien Miller\\Desktop\\fonts\\times-new-roman.ttf"))
		std::cout << "font file could not be found!";
	
	//x position of each rectangle in the vector of rectangles. 
	float xPosition = 0;
	for (size_t i = 0; i < numRectangles; i++){
		float width = static_cast<float>(windowWidth) / numRectangles;

		//in order to ensure that every single rectangle fits on the screen perfectly, we need to divide the width of the window
		//by the number of rectangles. Doing this will get the width each rectangle must be to ensure that numRectangles * width
		//of each rectangle = windowWidth. The height can be any random number between 50 and the size of the window. These values
		//are abritarely chosen, the bounds can technically be any value possible.
		sf::RectangleShape rect(sf::Vector2f(width , rand.getDoubleInRange(50, window.getSize().y)));
		
		//each rectangle will have their x position set at "xPosition", and their y position set at the window height minus the 
		//rectangle height. This will allow the entire length of the rectangle to be printed onto the screen. For example, in order
		//to print the whole body of a rectangle that is 400 pixels high in a 700 pixel high window, 700 - 400 = 300. Therefore, this
		//retangle will need to printed at y = 300.
		rect.setPosition(xPosition, window.getSize().y - rect.getSize().y);

		//choose three random RGB values for a color object. This will randomize the color of each rectangle object.
		rect.setFillColor(sf::Color(rand.getIntInRange(0, 256), rand.getIntInRange(0, 256), rand.getIntInRange(0, 256)));

		//add the rectangle to the vector
		rectangles.emplace_back(rect);

		//increment the xPosition by the width of each rectangle. This will ensure that each rectangle is printed next to each other 
		//with no space inbetween.
		xPosition += width;
	}

	createMenu();
}

void SortingVisualized::run(){
	showSorting();
}

void SortingVisualized::showSorting(){
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
		}

		switch (currentState){
			case states::MENU:
				drawMenu();
				break;
			case states::BUBBLE_SORT:
				bubbleSort();
				break;
			case states::MERGE_SORT:
				;
				break;
			case states::QUICK_SORT:
				;
				break;
			case states::SELECTION_SORT:
				selectionSort();
				break;
			case states::INSERTION_SORT:
				insertionSort();
				break;
			case states::COCKTAIL_SORT:
				cockTailSort();
				break;
			case states::EXIT:
				window.close();
			default:
				break;
		}
		
		stateManager();


	}
	
}

sf::Text SortingVisualized::createText(const std::string &word, int textSize, const sf::Text::Style &style, const sf::Vector2f &position){
	sf::Text text(word, font, textSize);

	text.setStyle(style), text.setPosition(position);
	return text;
}


//Returns the y position of lower bound of the rectangle surrounding the text
float SortingVisualized::getTextBottomEdge(const sf::Text &text){
	return text.getPosition().y + text.getGlobalBounds().height;
}

void SortingVisualized::drawMenu(){
	window.clear();

	sf::Text title = createText("SORTING ALGORITHMS VISUALIZED", 80, sf::Text::Bold, sf::Vector2f(0, 0));
	sf::Text directions = createText("CLICK AN OPTION!", 40, sf::Text::Bold, sf::Vector2f(window.getSize().x / 3, 
		getTextBottomEdge(title) * 1.5));
	sf::Text controls = createText("ONCE SORTING, YOU CAN PRESS \"ESC\" TO RETURN TO HOME", 40, sf::Text::Bold,
		sf::Vector2f(window.getSize().x / 10, getTextBottomEdge(directions) * 1.5));

	window.draw(title);
	window.draw(directions);
	window.draw(controls);
	for (auto& asset : menuAssets)
		window.draw(asset.second);

	window.display();
}

void SortingVisualized::stateManager(){
	if (isTextClicked(menuAssets.find(states::BUBBLE_SORT)->second))
		currentState = states::BUBBLE_SORT;
	else if (isTextClicked(menuAssets.find(states::MERGE_SORT)->second))
		currentState = states::MERGE_SORT;
	else if (isTextClicked(menuAssets.find(states::QUICK_SORT)->second))
		currentState = states::QUICK_SORT;
	else if (isTextClicked(menuAssets.find(states::INSERTION_SORT)->second))
		currentState = states::INSERTION_SORT;
	else if (isTextClicked(menuAssets.find(states::SELECTION_SORT)->second))
		currentState = states::SELECTION_SORT;
	else if (isTextClicked(menuAssets.find(states::COCKTAIL_SORT)->second))
		currentState = states::COCKTAIL_SORT;
	else if (isTextClicked(menuAssets.find(states::EXIT)->second))
		currentState = states::EXIT;
}

bool SortingVisualized::isTextClicked(const sf::Text& text) {
	//if the user clicks on the left mouse button while the mouse cursor is hovering over the text, return true and let the caller
	//function handle the click event.
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and text.getGlobalBounds().contains(mousePosition)) {
		std::cout << "button is clicked\n";
		return true;
	}
	return false;
}

void SortingVisualized::randomizeRectangles(){
	for (size_t i = 0; i < rectangles.size(); i++) {
		int indexOne = rand.getIntInRange(0, rectangles.size() - 1), indexTwo = rand.getIntInRange(0, rectangles.size() - 1);
		std::swap(rectangles[indexOne], rectangles[indexTwo]);
		swapRectXPosition(rectangles[indexOne], rectangles[indexTwo]);
	}
		
}

void SortingVisualized::createMenu(){
	menuAssets[states::BUBBLE_SORT] = createText("-VIEW BUBBLE SORT", 35, sf::Text::Bold, sf::Vector2f(window.getSize().x / 3,
		window.getSize().y / 3));
	menuAssets[states::MERGE_SORT] = createText("-VIEW MERGE SORT", 35, sf::Text::Bold, sf::Vector2f(window.getSize().x / 3,
		getTextBottomEdge(menuAssets.find(states::BUBBLE_SORT)->second) + 50));
	menuAssets[states::QUICK_SORT] = createText("-VIEW QUICK SORT", 35, sf::Text::Bold, sf::Vector2f(window.getSize().x / 3,
		getTextBottomEdge(menuAssets.find(states::MERGE_SORT)->second) + 50));
	menuAssets[states::SELECTION_SORT] = createText("-VIEW SELECTION SORT", 35, sf::Text::Bold, sf::Vector2f(window.getSize().x / 3,
		getTextBottomEdge(menuAssets.find(states::QUICK_SORT)->second) + 50));
	menuAssets[states::INSERTION_SORT] = createText("-VIEW INSERTION SORT", 35, sf::Text::Bold, sf::Vector2f(window.getSize().x / 3,
		getTextBottomEdge(menuAssets.find(states::SELECTION_SORT)->second) + 50));
	menuAssets[states::COCKTAIL_SORT] = createText("-VIEW COCKTAIL SORT", 35, sf::Text::Bold, sf::Vector2f(window.getSize().x / 3,
		getTextBottomEdge(menuAssets.find(states::INSERTION_SORT)->second) + 50));
	menuAssets[states::EXIT] = createText("-EXIT(GTFO)", 35, sf::Text::Bold, sf::Vector2f(window.getSize().x / 3,
		getTextBottomEdge(menuAssets.find(states::COCKTAIL_SORT)->second) + 50));
}

void SortingVisualized::bubbleSort(){
	
	for (size_t i = 0; i < rectangles.size() - 1; i++) {
		for (size_t j = 0; j < rectangles.size() - i - 1; j++) {
			if (rectangles[j].getSize().y > rectangles[j + 1].getSize().y) {
				std::swap(rectangles[j], rectangles[j + 1]);//swap the position of the rectangles being compared...

				//And afterwards, swap their x positions! Only their x positions have to be changed because simply swapping the position 
				//of each rectangle in the vector won't change where they're printed on the screen.
				swapRectXPosition(rectangles[j], rectangles[j + 1]);
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				currentState = states::MENU;
				randomizeRectangles();
				return;
			}

		}
		window.clear();//clear the window...
		drawRectangles();//draw the rectangles onto the screen...
		window.display();//and then display them!
	}	
}

void SortingVisualized::selectionSort(){
	window.setFramerateLimit(30);

	for (size_t i = 0; i < rectangles.size() - 1; i++){
		int minIndex = i;
		for (size_t j = i + 1; j < rectangles.size(); j++){
			if (rectangles[minIndex].getSize().y > rectangles[j].getSize().y) {
				minIndex = j;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				currentState = states::MENU;
				randomizeRectangles();
				return;
			}
		}
		std::swap(rectangles[i], rectangles[minIndex]);//swap the rectangles being compared
		swapRectXPosition(rectangles[i], rectangles[minIndex]);
		window.clear();
		drawRectangles();
		window.display();
	}

	window.setFramerateLimit(0);
}

void SortingVisualized::insertionSort(){
	for (int i = 1; i < rectangles.size(); i++) {
		sf::RectangleShape rect = rectangles[i];
		int location = i - 1;
		while (location >= 0 and rect.getSize().y < rectangles[location].getSize().y) {
			sf::Vector2f temp = rectangles[location + 1].getPosition();
			rectangles[location + 1] = rectangles[location];
			rectangles[location + 1].setPosition(sf::Vector2f(temp.x, rectangles[location + 1].getPosition().y));
			location--;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				currentState = states::MENU;
				randomizeRectangles();
				return;
			}
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			currentState = states::MENU;
			randomizeRectangles();
			return;
		}

		rect.setPosition(sf::Vector2f(rectangles[location + 1].getPosition().x, rect.getPosition().y));
		rectangles[location + 1] = rect;
		window.clear();
		drawRectangles();
		window.display();
	}
}

//Interesting name for a sort! It's essentially a modified bubble sort that works in both directions.
void SortingVisualized::cockTailSort(){
	//window.setFramerateLimit(20);

	int backIndex = rectangles.size() - 1;
	for (int i = 0; i < rectangles.size() - 1; i++) {

		for (int j = i; j < backIndex - i; j++) {
			if (rectangles[j].getSize().y > rectangles[j + 1].getSize().y) {
				std::swap(rectangles[j], rectangles[j + 1]);
				swapRectXPosition(rectangles[j], rectangles[j + 1]);
			}
			//if the user presses the escape key in the MIDDLE of the sorting, go back to the main menu. This is the best place to put
			//this check as putting it in the outer loop will result in the user having to wait until both inner loops finish running
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				currentState = states::MENU;
				randomizeRectangles();
				return;
			}
		}
				

		backIndex--;
		for (int k = backIndex; k > i; k--) {
			if (rectangles[k].getSize().y < rectangles[k - 1].getSize().y) {
				std::swap(rectangles[k], rectangles[k - 1]);
				swapRectXPosition(rectangles[k], rectangles[k - 1]);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				currentState = states::MENU;
				randomizeRectangles();
				return;
			}
			
		}

		window.clear();//clear the window...
		drawRectangles();//draw the rectangles onto the screen...
		window.display();//and then display them!
	}

	//window.setFramerateLimit(0);
}

/*
void SortingVisualized::mergeSort(std::vector<sf::RectangleShape>::iterator begin, std::vector<sf::RectangleShape>::iterator end){
	if (end - begin <= 1)
		return;

	auto mid = begin + ((end - begin) / 2);
	mergeSort(begin, mid);
	mergeSort(mid, end);
	std::inplace_merge(begin, mid, end);
}
*/
void SortingVisualized::swapRectXPosition(sf::RectangleShape &rectOne, sf::RectangleShape &rectTwo){
	float tempX = rectOne.getPosition().x;//save the x position of rectOne

	//Give rectOne a new Vector2f that contains the x position of rectTwo, and its own y position.
	rectOne.setPosition(sf::Vector2f(rectTwo.getPosition().x, rectOne.getPosition().y));

	//Give rectTwo a new Vector2f that contains the tempX variable, and its own y position.
	rectTwo.setPosition(sf::Vector2f(tempX, rectTwo.getPosition().y));
}

void SortingVisualized::drawRectangles(){
	for (auto &rect : rectangles)
		window.draw(rect);
}
