
#include <iostream>
#include <exception> 
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
using std::vector;
using namespace std;

//Our base class Signal 
class Signal{
private:
	int length;
	vector <float> data;//Vector private member for storing the signal values
	float max,avg;
	void maximum();
	void average();

public:
	Signal();
	~Signal(){};
	Signal(int filenumber);
	Signal(string filename);
	void Sig_info();
	int menu() throw(string,int,char);
	void statistics();
	void center();
	void normalize();
	void save_file();
	void operator+(float offset);//Member operator 
	void operator*(float scale_num);//Member operator
	friend Signal operator+(const Signal &x,const Signal &y);//Non-member operator 
};


//Performs the same operations as the scale function did previously
void Signal::operator*(float scale_num)
{
	
	for(int i = 0;i<length;i++)
	{
		data[i] *= scale_num;
		cout<<data[i]<<endl;
	}
	
}

//Performs the same operations as the offset function did previously
void Signal::operator+(float offset)
{
	
	for(int i=0;i<length;i++)
	{
		data[i]+= offset;
		cout<<data[i]<<endl;
	}
	
}


//Saves the contents of the signal into a specified file
void Signal::save_file()
{
	string s1 = "Excluding the extension, what would you like to call the file? ";
	string file_name; 
	cout<<s1<<endl;
	cin>>file_name;
	
	file_name+=".txt";
	ofstream file;
	file.open(file_name);
	file<<length<<" "<<max;
	file<<endl;
	for(auto i: data)
	{
		file<<i<<endl;
	}
	file.close();
}

//using member operator to aid in the centering calculations
void Signal::center()
{
	average();
	cout<<endl;
	cout<<"*CENTERED SIGNAL*"<<endl;
	operator+(-avg);
	cout<<endl;
}

//second member operator is used in the normalization calculations
void Signal::normalize()
{
	maximum();
	cout<<endl;
	cout<<"*NORMALIZED SIGNAL*"<<endl;
	operator*(1/max);
	cout<<endl;
}



void Signal::statistics()
{
	maximum();
	average();
}


//Displays signal info
void Signal::Sig_info()
{
	string s1("Length: "),s2("\nMaximum: "),s3("\nAverage: ");
	maximum();
	average();
	cout<<endl<<endl<<s1<<length<<s2<<max<<s3<<avg<<endl;
}

//calculates average
void Signal::average()
{
	avg =0;
	
	for(auto i: data)
	{
		avg += i;
	}
	avg /= (float)length;
}


//calculates maximum
void Signal::maximum()
{
	float maximum; 
	for(auto i: data)
	{
		maximum = i-1;
		if(i>maximum)
		{
			max = i;
		}else{
			max=maximum;
		}	
		
	}
}


//construcotr accepting integer parameter
Signal::Signal(int filenumber)
{
	
	char new_file[25] = "Raw_data_";
	if(filenumber<10){
		strcat(new_file,"0");
	}
	char num[5];
	sprintf(num,"%d",filenumber);	
	strcat(new_file,num);
	strcat(new_file,".txt");
	ifstream file;
	file.open(new_file);
	if(file.is_open())
	{
		float swap;
		int num;
		file>>length>>num;
		for(int i=0;i<length;i++)
		{
			file>>swap;
			data.push_back(swap);
		}
	
	}else{
		cout<<"\n****************ERROR*******************\nFile Does Not Exist. Please Exit And Restart The Program"<<endl;
	}
	file.close();
}


//default constructor 
Signal::Signal()
{
	length = 0;
	maximum();
	average();
}


//constructor accepting string paramter 
Signal::Signal(string filename)
{
	ifstream file;
	file.open(filename);
	if(file.is_open())
	{
		float swap;
		file>>length>>max;
		for(int i=0;i<length;i++)
		{
			file>>swap;
			data.push_back(swap);
		}
		
		
	}
	file.close();
	
}

//menu function with the exception specifications included in the function definition
int Signal::menu() throw(string,int,char)
{
	string s1("\nChoice must be greater than zero and less than seven");
	int choice = -1;
	cout<<"\nChoose An Option:\n1. Scale\n2. Offset\n3. Normalize\n4. Center\n5. Statistics\n6. Signal Info\n7. Save File\n0. Exit\n: "<<endl;
	cin>>choice;
	if(choice < 0 || choice > 7)
	{
		throw(s1);//throw a string if choice is less than zero and greater than 7
	}
	
		
	
	switch(choice)
	{
	case 0:
	{
		return 0;

	}
	case 1:
	{
		float num=0;
		
		cout<<"\nEnter a number to scale the data: "<<endl;
		cin>>num;
		if(num == 0)
		{
			throw(0);//throw an int if num = 0
		}
		
		cout<<endl;
		cout<<"*SCALED SIGNAL*"<<endl;
		
		operator*(num);
		
		break;
	}
	case 2:
	{
		
		float offset_num=0;
		cout<<"Enter an offset number: "<<endl;
		cin>>offset_num;
		if(offset_num ==0){
			throw((char)offset_num);
		}	
		cout<<endl;
		cout<<"*OFFSET SIGNAL*"<<endl;
		operator+(offset_num);
		
		break;
	}
	case 3:
	{
		normalize();
		
		break;
	}
	case 4:
	{
		center();
		break;
	}
	case 5:
	{
		statistics();
		break;
	}
	case 6:
	{
		Sig_info();
		break;
	}
	case 7:
	{
		save_file();
		break;
	}
	default:
	{
	
		cout<<"\nIncorrect Input for choice"<<endl;
		menu();
		break;
	}

	}
	
	
	
	return 0;
}

Signal operator+(const Signal &x,const Signal &y)
{
	Signal ret_obj;
	string s1("\nSizes of the vectors did not match"),s2("\nSizes matched");
	try
	{
	if(x.length == y.length)
	{
		cout<<s2<<endl;
		for(int i =0;i<x.length;i++)
		{
			ret_obj.data[i] = y.data[i] + x.data[i];
		}
	}
	else
	{
		throw(y); //throw a Signal if the vector lengths do not match
	}
	}
	catch(Signal)
	{//catch the thrown Signal and print out the error message
	cout<<"\nSizes of vectors did not match"<<endl;
	}

	return ret_obj;
}

int main(int argc,char** argv)
{
	
	
	if(argc==1)
	{
		Signal sig;
		sig.statistics();
		try
		{
			try
			{
				sig.menu();
			}
			catch(int)
			{
				cout<<"\nCaugt INT in main() function\nCannot scale by zero"<<endl;
			}
			catch(char)
			{
				cout<<"\nCaught char from menu() function\nCannot offset by zero"<<endl;
			}
			catch(string)
			{
				cout<<"\nCaught STRING from menu() function\nChoice Must be between 0 and 7"<<endl;
				throw;
			}
			catch(...)
			{
				cout<<"\nGeneral Exception"<<endl;
				
			}
		}
		catch(...)
		{
			cout<<"\nEnding Program"<<endl;
		}
		
	}else if(argv[1][1]=='n'){
		
		if(argc==2)
		{
			cout<<"\n***********ERROR************\nCorrect Formats: ./a.out -n <file number> OR ./a.out -f <file name>\n"<<endl;
			return 0;
			
		}		
		Signal sig(atoi(argv[2]));
		sig.statistics();
		sig.menu();
	}else if(argv[1][1] == 'f'){
		if(argc==2)
		{
			cout<<"\n***********ERROR************\nCorrect Formats: ./a.out -n <file number> OR ./a.out -f <file name>\n"<<endl;
			return 0;		
		}
		Signal sig(argv[2]);
		sig.statistics();
		sig.menu();
	}else if(argv[1][1] == 'o'){
		Signal sig1(argv[2]),sig2(argv[3]);
		operator+(sig1,sig2);
	}else{
		cout<<"\n***********ERROR************\nCorrect Formats: ./a.out -n <file number> OR ./a.out -f <file name>\n"<<endl;
	}
	return 0;
}
