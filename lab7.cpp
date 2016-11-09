#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <string>

using namespace std;
void helpFunction(void);


class signal{
	private://hands off, users!
	public:
		int file;
		vector<double> data;//pointer to data
		double mean;
		double maxVal;
		double meanFinder(int,vector<double>);
		int numEl;
		int i;
		void save_signal(const char*);//public methods
		void offset(double);//implemented them all pretty much the same way
		void scale(double);
		void normalize(void);
		void center(void);
		void display(void);
		void workWithData(signal);
		signal (void);//default constructor
		signal (int);//constructor for a file number being inputted 
		signal (const char*);//constructor for the file name
		~signal(void);//destructor
		double operator+(double);
		double operator*(double);
		
};
double signal::meanFinder(int numEl,vector<double> data)//this is the only private member function. simply calculates the mean of the data sent to it
{
	if(numEl ==0) return 0;
	double mean;
	i =0;
	double total;
	while(i < numEl)
	{
		total = total + data[i];
		i++;
	}
	mean = total / numEl;	
	return mean;
}
signal operator+(signal,signal);//function header for the non member operator

signal operator+(signal sig1, signal sig2){//heres the non member operator, it combines two signals of the same size (due to the style of our raw data files, the signal will just be doubled
	int j = 0;
	signal sig3(1);
	if(sig1.numEl != sig2.numEl){ cout << "ERROR" << endl; return sig3;}//cannot add them if different sizes
	else{
		sig3.numEl = sig1.numEl;
		if(sig1.maxVal > sig2.maxVal) sig3.maxVal = sig1.maxVal;//finds the maximum (even though they are the same) 
		else sig3.maxVal = sig2.maxVal;
		while(j < sig3.numEl){//adds each element in signal 1 and 2, stores them in signal 3
			sig3.data[j] = sig1.data[j] + sig2.data[j];
			j++;
		}
	}
	sig3.mean = sig3.meanFinder(sig3.numEl,sig3.data);
	return sig3;
}
double signal::operator+(double valueOff){//the addition member operator (i call this is in the offset method)
	double temp;
	temp = data[i] + valueOff;
	return temp;
}
double signal::operator*(double valueSca){//multiplication member operator (gets called in the scaling method)
	double temp;
	temp = data[i] * valueSca;
	return temp;
}
signal::~signal()
{	
	//delete data;//deletes the array which i allocated in the constructors 
}
signal::signal(void)//changed the dafault constructor to initialize an empty array now... note the methods will not work exactly right with an empty array... but oh well
{
	maxVal = 0;
	numEl = 0;
	i =0;
	data.resize(numEl,0);
	mean = meanFinder(numEl,data);
}
signal::signal(const char* fileName)
{
	char fileString[50];
	i = 0;
	sprintf(fileString,"%s",fileName);
	FILE* fp = fopen(fileString,"r");
	if(fp == NULL)
	{
		cout << "cant open file, terminating" << endl;
		return;
	}
	fscanf(fp,"%d %lf",&numEl,&maxVal);
	data.resize(numEl,0);
	while(i < numEl)
	{
		int temp;
		fscanf(fp,"%d\n",&temp);
		data[i] = temp;
		i++;
	}
	mean = meanFinder(numEl,data);
}
signal::signal(int fileNo)
{
	char fileString[50];
	i =0;
	if(fileNo > 10) sprintf(fileString,"Raw_data_%d.txt",fileNo);
	else sprintf(fileString,"Raw_data_0%d.txt",fileNo);
	FILE* fp = fopen(fileString,"r");
	if(fp == NULL)
	{
		cout << "cant open file, terminating" << endl;
		return	;
	}
	fscanf(fp,"%d %lf",&numEl,&maxVal);
	data.resize(numEl,0);
	while(i < numEl)
	{
		int temp;
		fscanf(fp,"%d\n",&temp);
		data[i] = temp;
		i++;
	}
	mean = meanFinder(numEl,data);
}
int main (int argc,char* argv[])
{
	int explicitFile = 0;//this is a truth value 
	int fileNo;
	int fileNum;
	int k =1;
	char* explicitFileName;
		while(k < argc)//this loops steps through each command line argument and checks its syntax
				//please note the truth value integers being set once a certain tag has been found
		{
			if((argv[k][0] == '-') && (argv[k][1] == 'h'))//checks to see if the help menu is needed, terminates program immediately
			{	
				helpFunction();
				return 1;
			}
			else if((argv[k][0] == '-') && (argv[k][1] == 'f'))
			{
				if(k >= (argc-1))
				{
					printf("WARNING: Please be sure to append a file name");
				}
				else
				{
					k++;
					if(argv[k][0] == '-')//checks to see if they forgot to append a number before the next tag
					{
						printf("WARNING: Need a value appended after tag -f\n");
						k--;
					}
					explicitFileName = argv[k];
					explicitFile = 1;
				}
			}	
			else if((argv[k][0] == '-') && (argv[k][1] == 'n'))//file number tag
			{
				if(k >= (argc-1))//ensures we dont run off the end of the argv[] array
				{
					printf("WARNING: Please be sure to append a file number\n");
				}
				else if(explicitFile ==1)
				{
					printf("WARNING: You cannot explicitly open two files at once, please dont try that again\n");
				}
				else
				{
					k++;
					if(argv[k][0] == '-')//checks to see if they forgot to append a number before the next tag
					{
						printf("WARNING: Need a value appended after tag -n\n");
						k--;
					}
					if(atoi(argv[k]) < 1 || atoi(argv[k]) > 11)//range for valid files
					{
						printf("WARNING: You did not enter a valid file number with your -n tag, program must terminate\n");
						return 1;//will seg fault if we try to open a data file that dont exist
					}	
					else
					{
						fileNo = atoi(argv[k]);
						fileNum = 1;
						printf("You want to work with file %d\n",fileNo);
					}
				}
			}
			else	//this error check basically says that the program did not find a tag, simply bumps past the argument and gives the user a warning
			{
				printf("WARNING: Your argument:\n %s\n has no valid context within the scope of the program, this error will be ignored and the program will continue\n",argv[k]);
			}
			k++;
		}

	if(argc == 1)//IF there were not command line arguments entered by the user 
	{
		signal sig1;//declares and calls using the default constructor
		sig1.workWithData(sig1);//calls the method that will contunue until program ends
	}
	else if(explicitFile == 1)//IF the user entered a file name to work with
	{
		signal sig1(explicitFileName);//calls using one of the parametric constructors 
		sig1.workWithData(sig1);
	}
	else if(fileNum == 1)//IF the user entered a file number to work with
	{
		signal sig1(fileNo);//calls the other parametric constructor
		sig1.workWithData(sig1);
	}
	else
	{
		cout << "No constructor was called!\n" << endl;
	}
	//*** heres where i use the non member operators, by declaring two new signals (both from the first raw data file since they will be the same length, and then add them together
	//NOTE THIS PART WILL NOT RUN ON NORMAL EXECUTION, NEED TO COMMENT OUT MOST OF MAIN TO GET IT TO RUN ITS JUST HERE TO DEMONSTRATE
	signal siga(1);//one operand
	siga.display();
	signal sigb(1);//the other
	sigb.display();
	signal sig3 = operator+(siga,sigb);//makes the last signal a combination of the other two
	sig3.display();
	sig3.save_signal("added_signals.txt");
	return 1;
}
void signal::workWithData(signal sig1)//this is the moethod that displays the menu to the user and handles its inputs
{
	int userInput = 1000;
	double offsetVal;//both of type double to allow manipulation
	double scaleVal;
	char saveFileString[50];
	cout << "Alrighty there user!!! We actually got your file open (believe it or not)\nWhat do you want to do with it now? there are several things to choose from" << endl;
	while(userInput != 0)//loops until 0
	{


		cout << "0: Exit the program\n1: Scale the data\n2: Offset the data\n3: Normalize the data\n4: Center the data\n5: Save the current signal to a file\n6: Display information on the current signal" <<endl;

		cin >> userInput;	
		switch(userInput)//switch decides what is done with the data
		{
			case 0:
				break;
			case 1: 
				cout<<"Enter a scale value" <<endl;
				cin>>scaleVal;
				cout<<"Scaling data..."<<endl;
				sig1.scale(scaleVal);
				break;
			case 2:
				cout<<"Enter an offset value"<<endl;
				cin>>offsetVal;
				cout<<"Offsetting data..."<<endl;
				sig1.offset(offsetVal);
				break;
			case 3: 
				cout<<"Normalizing data..."<<endl;
				sig1.normalize();
				break;
			case 4:
				cout<<"Centering data..."<<endl;
				sig1.center();
				break;
			case 5:
				cout << "where do you want to save this signal?" << endl;
				cin >> saveFileString;
				cout<<"Saving signal..."<<endl;
				sig1.save_signal(saveFileString);
				break;
			case 6: 
				sig1.display();
				break;
			default:
				break;
		}
	}
	return;
}
void signal::save_signal(const char* fileName)//NOTE: this method does not cause any issues
{
	i =0;
	FILE* fp = fopen(fileName,"w");//opens the file that the user wanted 
	fprintf(fp,"%d\t%lf\n",numEl,maxVal);//prints out the "heading" info
	while(i < numEl)
	{
		fprintf(fp,"%lf\n",data[i]);//prints each element into the file
		i++;
	}
	fclose(fp);
}
void signal::center(void)//NOTE: this is one of the methods causing issues 
{
	i = 0;
	while(i < numEl)
	{
		data[i] = data[i] - mean;
		i++;
	}
	maxVal = maxVal - mean;
	mean = meanFinder(numEl,data);
}
void signal::normalize(void)//NOTE: another one that IS causing issues
{
	i =0;
	while(i < numEl)
	{
		data[i] = data[i] / maxVal;
		i++;
	}
	maxVal = maxVal / maxVal;
	mean = meanFinder(numEl,data);
}
void signal::offset(double offsetVal)//NOTE: another one that IS causing issues
{
	i = 0;
	double temp;
	maxVal = maxVal + offsetVal;
	while(i < numEl)
	{
		data[i] = operator+(offsetVal);
		i++;
	}
	mean = meanFinder(numEl,data);
}
void signal::scale(double scaleVal)//NOTE: this one does not cause any issues
{
	i = 0;
	maxVal =  maxVal * scaleVal;
	while(i < numEl)
	{
		data[i] = operator*(scaleVal);
		i++;
	}
	mean = meanFinder(numEl,data);
}
void signal::display(void)
{
	cout << "Num of elements is currently: " << numEl << "\nMax value is currently: " << maxVal << "\nMean is currently: " << mean << endl;
}	
void helpFunction(void)//void function to print out a help menu
{ 
	printf("WELCOME!\nHere in lab5.c, we want to make it easy to access and manipulate the information located within these select files!\nTo execute this program correctly, run ./lab4 along with any arguments appended\nEXAMPLE:./lab4 -n 3 -o 5.3\nThe tags must be proceeded by a valid value in which to perform the operation.\n\n\n-n <file_choice>\tSelects the file in which you want to work with, note valid files range from 1 to 11\n-o <offset_value>\tOffsets each value in the file that you have selected, by the offset value proceeding the tag\n-s <scale_value>\tScales each value in the file that you have selected, by the scaling value proceeding the tag\n-S\t\t\tProvides a new file in which you will find the mean value of the data file you have selected, as well as the maximum value present in the file\n-C\t\t\tCenters the signal in the file you have chosen and writes an output file\n-N\t\t\tNormalizes the signal in the file you have chosen and writes an output file\n-r <new_file_name>\tRenames the current file you have chosen, be sure to proceed the tag with the NEW desired name of the file\n-h\t\t\tDisplays this help menu\n\n\n");
	return;
}

	
