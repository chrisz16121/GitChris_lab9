// Lab9_strings.cpp
// This program shows some simple string examples, and asks for simple tasks.
// Reference: Lippman, section 3.2

// Author: Luis Rivera

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

char changeCase(char c);
using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	/*string s1, s2("Hello"), s3 = "World";
	cout << "\nEnter a word:" << endl;
	cin >> s1;
	
	string s4(s1);
	
	cout << s1 << endl
		 << s2 << endl
		 << s3 << endl
		 << s4 << endl;
	
	s1 = s2 + s3;
	cout << s1 << endl;
	*/
	string s4 = "MYString";
	string s5;
	cout << "Use of the  << operator 1: " << s4 << endl; //use of the "<<" operator, which will write the string s4 into the output stream (in this case cout)
	cout << "Now the >> operator (even though i use << to output the string, enter a string" << endl;
	cin >> s5;//use of the ">>" operator which will read the white space seperated string from the standard input (cin) to the string (s5)
	cout << "2: " << s5 << endl; //demonstrating that the string s5 is now written to 
	cout << "Time for getline(), enter another string" << endl;
	getline(cin,s5);
	cout << "3: " << s5 << endl;
	string s6;
	int value;
	value = s5.empty();
	cout << "Testing the string.empty()... 4: " << value << endl;
	string s7 = "TESTFORSIZE";
	value = s7.size();
	cout << "Finding the size now... 5: " << value << endl;
	char value2;
	value2 = s7[1];
	cout << "Getting the nth element of the string using the string[n]... 6: " << value2 << endl;
	string s8;
	s8 = s4 + s7;
	cout << "Adding the string together... 7: " << s8 << endl;
	s4 = s7;
	cout << "Replacing one of the strings with another... 8: " << s4 << endl;
	string s9 = "SAMESTRING";
	string s10 = "SAMESTRING";
	cout << "Time for == operator.. zero if strings equal, 1 if not" << endl;
	if(s9 == s10) cout << "9: 0" << endl;
	else cout << "9: 1" << endl;
	cout << "Time for the != operator.. zero if string not equal, 1 if not" << endl;
	if(s9 != s10) cout << "9: 0" << endl;
	else cout << "9: 1" << endl;
	
	
	
	 
// ***********************************************************************
// Try all the operations in Table 3.2 using the strings above and
// using new strings that you may declare.
// Some of those operations have already been used, but write your
// own examples.
// ***********************************************************************

// -----------------------------------------------------------------------
	string line;
	cout << "\nEnter some text, finish it with an &" << endl;
	getline(cin, line, '&');
	cout << line << endl;
	transform(line.begin(),line.end(),line.begin(),changeCase);
	cout << line << endl;


// ***********************************************************************
// Use a "Range for" (Lippman, page 93) and operations in table 3.3 to:
// 1) change the case of the letters in your input line above (upper to
//    lowercase and vice-versa).
// 2) Replace any whitespace with a dot ('.').
// Print the converted text.
// ***********************************************************************
	
	return 0;
}
char changeCase(char c){
	 if (isupper(c)) return tolower(c); 
    	 else return toupper(c);
} 

