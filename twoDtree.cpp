
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

// twoDtree destructor, given.
twoDtree::~twoDtree(){
	clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


// twoDtree assignment operator, given.
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){

	// YOUR CODE HERE
	height = imIn.height();
	width = imIn.width();
	pair<int, int> ul = make_pair(0,0);
	pair<int, int> lr = make_pair(width-1, height-1);
	stats stat = stats(imIn);
	bool v = true;
	root = buildTree(stat, ul, lr, v);

}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {

	// YOUR CODE HERE!!
	RGBAPixel pix = s.getAvg(ul, lr);
	Node* sub = new Node(ul, lr, pix);
	long score = LONG_MAX;
	pair<int,int> newlr, newul;

	if(ul == lr) {
		return sub;
	}

	for(int x = ul.first; x < lr.first; x++) {
		pair<int,int> firstPair = make_pair(x, lr.second);
		pair<int, int> secPair = make_pair(x + 1, ul.second);
		long firstScore = s.getScore(ul, firstPair);
		long secScore = s.getScore(secPair, lr);
		long total = firstScore + secScore;
		if(total < score) {
			score = total;
			newlr = firstPair;
			newul = secPair;
		}
	}

	for(int y = ul.second; y < lr.second; y++) {
		pair<int,int> firstPair = make_pair(lr.first, y);
		pair<int,int> secPair = make_pair(ul.first, y+1);
		long firstScore = s.getScore(ul, firstPair);
		long secScore = s.getScore(secPair, lr);
		long total = firstScore + secScore;
		if(total < score) {
			score = total;
			newlr = firstPair;
			newul = secPair;
		}
	}

	sub->left = buildTree(s, ul, newlr, vert);
	sub->right = buildTree(s, newul, lr, vert);
	return sub;
}

PNG twoDtree::render(){

	// YOUR CODE HERE!!
	PNG img(width, height);
	render(root, img);
	return img;

}

void twoDtree::render(const Node* sub, PNG &img) {

	if(sub == NULL) {
		return;
	} 
	else if (sub->left == NULL && sub->right == NULL) {
		int ulf = sub->upLeft.first;
		int lrf = sub->lowRight.first;
		int uls = sub->upLeft.second;
		int lrs = sub->lowRight.second;
		for(int x = ulf; x <= lrf; x++) {
			for(int y = uls; y <= lrs; y++) {
				RGBAPixel *pix = img.getPixel(x,y);
				*pix = sub->avg;
			}
		}
		return;
	}
	render(sub->left, img);
	render(sub->right, img);
}

int twoDtree::idealPrune(int leaves){

// YOUR CODE HERE!!
}

int twoDtree::pruneSize(int tol){

// YOUR CODE HERE!!

}

void twoDtree::prune(int tol){
// YOUR CODE HERE!!

}

void twoDtree::clear() {
// YOUR CODE HERE!!
	clear(root);
}

void twoDtree::clear(Node* subRoot) {
	if (subRoot == NULL) {
		return;
	}
	clear(subRoot->left);
	clear(subRoot->right);
	delete subRoot;
}

void twoDtree::copy(const twoDtree & orig){
// YOUR CODE HERE!!
	root = copy(orig.root);
	this->height = orig.height;
	this->width = orig.width;
}

twoDtree::Node* twoDtree::copy(const Node* sub) {

	if(sub == NULL) {
		return NULL;
	}
	Node* newNode = new Node(sub->upLeft, sub->lowRight, sub->avg);
	newNode->left = copy(sub->left);
	newNode->right = copy(sub->right);
	return newNode;

}
