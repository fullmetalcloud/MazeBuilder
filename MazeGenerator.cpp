#include "stdafx.h"
#include "MazeGenerator.h"
#include "stdlib.h"
#include "time.h"
#include <stack>
#include "tbb/tbb.h"

using namespace std;
using namespace tbb;

//2 dimensional array
template <typename T>
Graph<T>::Graph(unsigned int _height, unsigned int _width) {
	height = _height;
	width = _width;
	array = new T[height * width];
}

Maze::Maze(unsigned int _height, unsigned int _width){
	srand((unsigned int)time(NULL));
	height = _height;
	width = _width;
}
Maze::~Maze(){

}

bool Maze::CheckChildren(unsigned int x, unsigned int y, int root, Graph<int> &maze){

	for (int t = 1; t <= 4; t++)
	{
		if (y <= 0 || y + 1 >= height
			|| x <= 0 || x + 1 >= width)
			return false;
		switch (t){
		case 1:
			//up
			if (t == root)
			{
				if (maze(x - 1, y + 1) > 0 || maze(x + 1, y + 1) > 0)
					return false;
				break;
			}
			else if (maze(x, y - 1) > 0)
				return false;
			break;
		case 2:
			//right
			if (t == root)
			{
				if (maze(x - 1, y - 1) > 0 || maze(x - 1, y + 1) > 0)
					return false;
				break;
			}
			else if(maze(x + 1, y) > 0)
				return false;
			break;
		case 3:
			//down
			if (t == root)
			{
				if (maze(x - 1, y - 1) > 0 || maze(x + 1, y - 1) > 0)
					return false;
				break;
			}
			else if(maze(x, y + 1) > 0)
				return false;
			break;
		case 4:
			//left
			if (t == root)
			{
				if (maze(x + 1, y - 1) > 0 || maze(x + 1, y + 1) > 0)
					return false;
				break;
			}
			else if(maze(x - 1, y) > 0)
				return false;
			break;
		}
	}
	return true;
}
Graph<int>& Maze::GenerateMaze(){
	unsigned int randX = 1, randY = 1, randDir, temp;
	bool check;
	stack<Node> s;
	Node currentNode, newNode;
	static Graph<int> maze(height, width);

	parallel_for(blocked_range<int>(0, height), [&](blocked_range<int> r){
		for (int i = r.begin(); i<r.end(); i++){
			parallel_for(blocked_range<int>(0, width), [&](blocked_range<int> q){
				for (int j = q.begin(); j<q.end(); j++){
					maze(i, j) = 0;
				}
			});
		}
	});
	
	randX = rand() % (width - 3) + 1;
	randY = rand() % (height - 3) + 1;
	maze(randX, randY) = 1;
	currentNode.direction = new int[4]{ 1, 2, 3, 4 };

	for (int i = 3; i >0; i--)
	{
		randDir = rand() % i;
		temp = currentNode.direction[i];
		currentNode.direction[i] = currentNode.direction[randDir];
		currentNode.direction[randDir] = temp;
	}
	
	currentNode.x = randX;
	currentNode.y = randY;
	currentNode.current = 0;
	currentNode.root = currentNode.direction[0];
	s.push(currentNode);

	while (!s.empty())
	{
		currentNode = s.top();
		s.pop();
		maze(currentNode.x, currentNode.y) = 1;
		newNode.direction = new int[4]{ 1, 2, 3, 4 };
		for (int i = 3; i >0; i--)
		{
			randDir = rand() % i;
			temp = newNode.direction[i];
			newNode.direction[i] = newNode.direction[randDir];
			newNode.direction[randDir] = temp;
		}

		switch (currentNode.direction[currentNode.current]){
		case 1:
			//up
			newNode.x = currentNode.x;
			newNode.y = currentNode.y-1;
			newNode.current = 0;
			newNode.root = 3;
			break;
		case 2:
			//right
			newNode.x = currentNode.x + 1;
			newNode.y = currentNode.y;
			newNode.current = 0;
			newNode.root = 4;
			break;
		case 3:
			//down
			newNode.x = currentNode.x;
			newNode.y = currentNode.y+1;
			newNode.current = 0;
			newNode.root = 1;
			break;
		case 4:
			//left
			newNode.x = currentNode.x-1;
			newNode.y = currentNode.y;
			newNode.current = 0;
			newNode.root = 2;
			break;
		}
		currentNode.current++;
		if (currentNode.current<4)
			s.push(currentNode);
		check = CheckChildren(newNode.x, newNode.y, newNode.root, maze);
		if (check)
			s.push(newNode);
	}
	return maze;
}