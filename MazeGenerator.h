#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include <vector>
#include "tbb/tbb.h"
#include "tbb/mutex.h"

using namespace tbb;

struct Node{
	unsigned int x;
	unsigned int y;
	int *direction;
	unsigned int current;
	unsigned int root;
};

template<typename T>
class Graph{
private:
	unsigned int height;
	unsigned int width;
	T *array;

public:
	//2 dimensional array
	Graph(unsigned int _height, unsigned int _width);
	T& operator()(unsigned int from, unsigned int to) {
		return array[from * width + to];
	}
	inline unsigned int getHeight() const { return height; }
	inline unsigned int getWidth() const { return width; }
};

class Maze{
private:
	unsigned int height;
	unsigned int width;

	bool CheckChildren(unsigned int x, unsigned int y, int root, Graph<int> &g);

public:
	Maze(unsigned int height, unsigned int width);
	~Maze();
	Graph<int>& GenerateMaze();


};
#endif