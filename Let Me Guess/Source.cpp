#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <stdlib.h>

struct Node
{
	std::string data;
	std::shared_ptr<Node> noPtr;
	std::shared_ptr<Node> yesPtr;
	Node(std::string d) : data(d), noPtr(nullptr), yesPtr(nullptr){};
};

void insert(std::shared_ptr<Node>& current, std::string answer, std::string newQuestion)
{
	current->yesPtr = std::make_shared<Node>(answer);
	current->noPtr = std::make_shared<Node>(current->data);
	current->data = newQuestion;
}

void main()
{
	auto root = std::make_shared<Node>("Elephant");
	std::string response;
	std::string newQuestion;
	std::string answer;
	bool isPlaying = true;
	while (isPlaying == true)
	{
		std::shared_ptr<Node> current = root;
		
		while (current->noPtr != nullptr && current->yesPtr != nullptr)
		{
			std::cout << current->data << '?' << std::endl;
			std::cin >> response;
			if (current->yesPtr != nullptr && response == "yes")
			{
				current = current->yesPtr;
			}
			else if (current->noPtr != nullptr && response == "no")
			{
				current = current->noPtr;
			}
		}
		if (current->noPtr == nullptr && current->yesPtr == nullptr)
		{
			std::cout << "Are you thinking of a(n) " << current->data << '?' << std::endl;
			std::cin >> response;
			std::cin.ignore();
			if (current->yesPtr == nullptr && response == "yes")
			{
				std::cout << "I win!" << std::endl;
			}
			else if (current->noPtr == nullptr && response == "no")
			{
				std::cout << "What were you thinking of?" << std::endl;
				std::getline(std::cin, answer);
				std::cout << "What could I have asked to find you were thinking of a(n) " << answer << '?' << std::endl;
				std::getline(std::cin, newQuestion);
				insert(current, answer, newQuestion);
			}
		}
		
		std::cout << "Do you want to play again?" << std::endl;
		std::cin >> response;
		if (response == "yes")
		{
			isPlaying = true;
		}
		else if (response == "no")
		{
			isPlaying = false;
		}
	}
}