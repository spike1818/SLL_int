/*
 * SLLSet.cpp
 *
 *  Created on: Nov. 17, 2021
 *      Author: moham
 */


#include "SLLSet.h"
#include <iostream>

SLLSet::SLLSet()
{
	size = 0;
	head = NULL;
}
SLLSet::SLLSet(int sortedArray[], int arrSize)
{
	size = arrSize;
	SLLNode* point = new SLLNode(sortedArray[arrSize-1],NULL); //Creates a pointer for the tail of the list
	for (int i = arrSize -2; i>=0; i--){  //Loops backwards through the array creating nodes
		SLLNode* element = new SLLNode(sortedArray[i],point);
		point = element;
	}
	head = point;
}
int SLLSet::getSize()
{
	return size;
}

SLLSet SLLSet::copy()
{
	int nums[size];
	SLLNode* current = head;


	for(int i = 0; i < size; i++){ //loops through the list and creates an array of the values
		nums[i] = current->value;
		current = current->next;
	}
	return *(new SLLSet(nums, size)); //creates a new list using the values from the array
}

bool SLLSet::isIn(int v)
{
	bool in = false;
	SLLNode* current = head;
    while (current != NULL){ // loops through the list and sets in to true if the current element == v
    	if (current->value == v){
    		in = true;
    		current = NULL;
    	}
    	else{
    		current = current->next;
    	}
    }
	return in;
}
void SLLSet::add(int v)
{
	SLLNode* current = head;
	SLLNode* last;
	bool in = isIn(v);

	if (size == 0){ //accounts for an empty list where head will be equal to the only element
		SLLNode* ins = new SLLNode(v,NULL);
		head = ins;
		size++;
		in = true;
	}

	while (!in){ // loops until the position where node will be inserted
		if (current->value > v || current->next == NULL){
			if (current == head && current->next != NULL){ // accounts for element becoming the head
				SLLNode* ins = new SLLNode(v,head);
				head = ins;
				size++;
				in = true;

			}
			else if(current->next == NULL){ // accounts for element at the end of the list
				SLLNode* ins = new SLLNode(v,NULL);
				current->next = ins;
				size++;
				in = true;
			}
			else{
				SLLNode* ins = new SLLNode(v,current); // accounts for an element inserted into the middle of the list
				last->next = ins;
				size++;
				in = true;
			}
		}
		else{
			last = current;
			current = current->next;
		}


	}

}
void SLLSet::remove(int v)
{
	SLLNode* current = head;
	SLLNode* last;
	bool in = isIn(v);

	if (head->value == v){ // removes the head if head == v
		current = head->next;
		delete(&head);
		head = current;
		size--;
		in = false;
	}

	while(in){ // loops until current == v and removes current
		if (current->value == v){
			delete(&last->next);
			last->next = current->next;
			size--;
			in = false;
		}
		else{
			last = current;
			current = current->next;
		}
	}
}
SLLSet SLLSet::setUnion(SLLSet s)
{
	SLLSet unionSet = s.copy(); // creates a copy of s to add nodes to
	SLLNode *point = head;



	for (int i = 0; i < size; i++){ //loops through the set and adds each element in the set to unionSet
		unionSet.add(point->value);// counts on the add function to determine which elements to add or not
		point = point->next;
	}

	return unionSet;
}

SLLSet SLLSet::intersection(SLLSet s)
{
	SLLNode *point1 = head;
	SLLSet intersect = s.copy(); // creates a copy of s to remove nodes from
	SLLNode *point2 = intersect.head;

	bool in;

	if (intersect.getSize() != 0){
		while (point2 != NULL){// loops through each element in the intersect set

			in = false;
			point1 = head;
			for (int j = 0; j < size; j++){ //checks to see if the element is also in the current set
				if (point1->value == point2->value){
					in = true;
				}
				point1 = point1->next;
			}
			if (!in){// if the element is not in the current set it is removed from the intersection
				intersect.remove(point2->value);
			}
			point2 = point2->next;
		}
	}

	return intersect;
}

SLLSet SLLSet::difference(SLLSet s)
{

	SLLSet a = this->copy(); // creates a copy of the current set
	SLLNode *point;

	if (s.getSize() == 0){// if s is empty returns the current set
		return a;
	}
	else{
		point = a.head;
	}

	while(point != NULL){//loops through the list
		if (s.isIn(point->value)){
			a.remove(point->value);//removes the node from the copy of the current set if it is also in s
		}
		point = point->next;
	}

	return a;
}

SLLSet SLLSet::setUnion(SLLSet sArray[],int size)
{
	SLLSet set1 = sArray[0];
	SLLSet set2;

	for (int i = 1; i < size; i++){//repeats the union function for each set in sArray
		set2 = sArray[i];

		set1 = set1.setUnion(set2);
	}

	return set1;
}


string SLLSet::toString()
{
   string output = "";
   SLLNode* pointer = head;
   if (head != NULL){
	   for (int i = 0; i < size ; i++){
		   if (pointer->next != NULL){
			   output = output + to_string(pointer->value) + ", ";
			   pointer = pointer->next;
		   }
		   else{
			   output = output + to_string(pointer->value);
		   }
	   }
   }

   return output;
}

