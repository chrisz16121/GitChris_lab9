// Lab9_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
// Example: g++ Lab9_vectors.cpp -o Lab9_vectors -std=c++11
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	/*vector<int> ivec1(5), ivec2;
	vector<double> dvec1{5.1}, dvec2(5,1.5);
	vector<string> svec1 = {"hello", "world"};
	// vector<myClass> myCvec;	// you can have vectors of objects
	// in general: vector<Type> vec;	// vector is a template

	for(int i = 0; i < ivec1.size(); i++)
		cout << ivec1[i] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:ivec1)	// This is equivalent to the above for loop
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec2)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:svec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
	cout << "Original size: " << ivec2.size() << endl;
	ivec2.push_back(50);
	cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	*/
// ***********************************************************************
// Try all the wasy to initializa a vector shown in Table 3.4. Use the
// vectors above and/or declare new vectors.
// Some of those operations have already been used, but write your
// own examples.

// Do exercises 3.14 and 3.15 from Lippman (page 102)

// Try all the vector operations shown in table 3.5. Use the vectors above
// or define new ones. Try different types.
// ***********************************************************************
	vector<int> v1;//declares an empty vector v1
	vector<int> v2(v1);//declares a vector v2, which contains a copy of all elements in v1
	vector<int> v3 = v1;//declares vector v3, which contains a copy of all elements in v1
	vector<int> v4 (5,0);//new vector v4 that contains 5 elements, all initialized to zero
	vector<int> v5 (5);//new vector that contains 5 integers
	vector<int> v6 {1,2,3,4,5,6,7,8};//vector that contains characters a through g
	vector<int> v7 = {1,2,3,4,5,6,7,8};// equivalent to the above statement 
	
	int temp;
	int i = 0;
	while(i<5){
		cout << "Enter a number" << endl;
		cin>>temp;
		v5[i] = temp;
		i++;
		cout << "Vector[" << i << "]: " << v5[i-1] << endl;
	}
	vector<string> v8(5);
	string tempString;
	i = 0;
	while(i<5){
		cout << "Enter a atring" << endl;
		cin>>tempString;
		v8[i] = tempString;
		i++;
		cout << "Vector[" << i << "] " << v8[i-1] << endl;
	}
	temp = v1.empty();
	cout << "Time for vector.empty(), 1 if empty and 0 if not empty.. 1: " << temp << endl;
	temp = v5.size();
	cout << "Time for vector.size(), returns number of elements.. 2: " << temp << endl;
	//cout << "Before push_back():\n" << v6 << endl;
	//v6.push_back(1);
	//cout << "After push_ back():\n" << v6 << endl
	temp = v4[1];//should store a zero into temp 
	cout << "The second element of array v4 is: " << temp << endl;
	v5 = v4;//using the = operator (confirmed to be working with the == operator
	v7 = {8,7,6,5,4,3,2,1};//replaces each element in v7 to be descending order now
	if(v4 == v5) cout << "The arrays are equal!! this is a good thing!" << endl;
	else cout << "Didnt work, go back" << endl;
	if(v4 != v5) cout << "Second check didnt work, need to go back" << endl;
	else  cout <<"still equal!! keep going!!!" << endl;

	return 0;
}
