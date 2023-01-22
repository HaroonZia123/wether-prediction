
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
#include<vector>
#include <cctype>
#include<iomanip>

int** cityLoc = NULL; int** clodCover = NULL; int** pressure = NULL;

int cloudindexconvert(int value) {
	if (value >= 0 && value < 10) {
		return 0;
	}

	else if (value >= 10 && value < 20)
	{
		return 1;
	}
	else if (value >= 20 && value < 30)
	{
		return 2;
	}
	else if (value >= 30 && value < 40)
	{
		return 3;
	}
	else if (value >= 40 && value < 50)
	{
		return 4;
	}
	else if (value >= 50 && value < 60)
	{
		return 5;
	}
	else if (value >= 60 && value < 70)
	{
		return 6;
	}
	else if (value >= 70 && value < 80)
	{
		return 7;
	}
	else if (value >= 80 && value < 90)
	{
		return 8;
	}
	else if (value >= 90 && value < 100)
	{
		return 9;
	}
	else
		return -1;
}

char cloudLMH(int v)
{
	if (v >= 0 && v < 35)
	{
		return 'L';
	}
	else if (v >= 35 && v < 65)
	{
		return 'M';
	}
	else 
	{
		return 'H';
	}
}
float probability(char p, char c,string&str)
{
	
	if (p == 'L' && c == 'H')
	{
		str = "~~~~\n~~~~~\n\\\\\\\\\\\n";

		return 90.00;
	}
	else if (p == 'L' && c == 'M')
	{
		str = "~~~~\n~~~~~\n  \\\\\\\\\n";
		return 80;
	}
	else if (p == 'L' && c == 'L')
	{
		str = "~~~~\n~~~~~\n  \\\\\\\n";

		return 70.00;
	}
	
	if (p == 'M' && c == 'H')
	{
		str = "~~~~\n~~~~~\n   \\\\\n";

		return 60;
	}
	else if (p == 'M' && c == 'M')
	{
		str = "~~~~\n~~~~~\n    \\\n";

		return 50.00;
	}
	else if (p == 'M' && c == 'L')
	{
		str = "~~~~\n~~~~~\n     \n";

		return 40.00;
	}

	if (p == 'H' && c == 'H')
	{
		str = "~~~\n~~~~\n     \n";
		return 30.00;
	}
	else if (p == 'H' && c == 'M')
	{
		str = "~~\n~~~\n     \n";

		return 20.00;
	}
	else if (p == 'H' && c == 'L')
	{
		str = "~\n~~\n     \n";

		return 10.00;
	}
	return 0;
}

void displayCoordinates(int rows, int cols, int** matrix,int ch)
{

	//loops the physical map for coordinates
	for (int i = cols-1;i >=0;i--)
	{
		//row
		if (i == cols-1)
		{
			cout <<setw(2)<< " ";
			for (int l = 0; l < rows + 2;l++)
				cout  << "#  ";

		}
		cout << endl;
		//end of row 
		cout << setw(2) << i << " # ";
		//col with matrix input
		for (int j = 0;j <rows ;j++)
		{
			//load the virtual matrix by checking non -1 value repalced by readfile function
			if (matrix[j][i] != -1)
			{
				if(ch==2)
				cout << setw(2) << (matrix[j][i]) << " ";
				else if(ch==3||ch==5)
					cout << setw(2) << cloudindexconvert(matrix[j][i]) << " ";
				else if(ch==4||ch==6)
					cout << setw(2) << cloudLMH(matrix[j][i]) << " ";

			}
			else
				cout << setw(3) << " ";
		}
		cout << setw(2) << "# ";

	}
	cout << endl;
	cout << setw(2) << " ";
	for (int l = rows+1; l >=0;l--)
		cout  << "#  ";
	cout << endl << "    ";
	for (int l = 0; l <rows;l++)
		cout << setw(2) << l << " ";
}

//simple tokenizer function to tokenize based on delimeter
//assumed to have fixed delimeter no user input required.
vector<string> getTokens(string s)
{
	string res = "";
	vector<string>vec;

	for (int a = 1;a < s.size();a++)
	{
		if (s[a] == ' ')
		{

		}
		else if (s[a] == '-' || s[a] == ',' || s[a] == ']' || s[a] == '=')
		{
			//append to vector
			vec.push_back(res);
			res = "";
			//skip if ]
			if (s[a] == ']') a++;

		}
		else
			res += s[a];
	}
	if (res.size() >= 1)
		vec.push_back(res);
	return vec;

}



void readFile(string fileNamePointer, int** matrix)
{
	vector<vector<vector<string>>>v;
	ifstream fp(fileNamePointer);
	if (!fp)
		exit(EXIT_FAILURE);
	string str;
	while (getline(fp, str))
	{
		if (str.size() > 1)
		{

			vector<string>tokens = getTokens(str);
			int r = stoi(tokens[0]);
			int c = stoi(tokens[1]);
			if (v.size() <= r)
				v.resize(r + 1);
			if (v[r].size() <= c)
				v[r].resize(c + 1);
			for (int a = 2;a < tokens.size();a++)
				v[r][c].push_back(tokens[a]);

		}
	}
	//loop the vector coordinates and input inside the virtual matrix repalcing -1 for each existing
	//coordinate ...
	for (int a = 0;a < v.size();a++)
	{
		for (int b = 0;b < v[a].size();b++)
		{

			if (v[a][b].size() > 0)
				matrix[a][b] = stoi(v[a][b][0]);
		}
	}
	fp.close();

}




void configuration(int& row, int& col) {

	cout << endl;
	cout << "Please enter filename: ";
	string inputfilename;

	vector<int> rowcol;

	//config file name input
	cin >> inputfilename;
	cout << "Reading in " << inputfilename << endl;
	//check if config file 
	if (inputfilename.find("config") == string::npos) {
		cout << "Invalid config file" << endl;
		cout << endl;
		return;
	}

	fstream inputFile(inputfilename.c_str(), fstream::in);
	//variable for reuse
	string aLine;
	int start = 0;
	int end = 0;
	int count = 0;

	vector<string>rowrange;
	cout << endl;
	while (getline(inputFile, aLine))
	{
		//find grix x and loop range append to vector
		if (aLine.find("GridX") != string::npos)
		{
			rowrange = getTokens(aLine);
			start = stoi(rowrange[1]);
			end = stoi(rowrange[2]);

			for (int c = start; c < end; c++)
			{
				count = count + 1;
			}
			row = count + 1;
			count = 0;
			cout << "Redaing in " << aLine << "...done!\n";
		}
		//find grix and do the same
		if (aLine.find("GridY") != string::npos)
		{
			rowrange = getTokens(aLine);
			start = stoi(rowrange[1]);
			end = stoi(rowrange[2]);

			for (int c = start; c < end; c++)
			{
				count = count + 1;
			}
			col = count + 1;
			count = 0;
			cout << "Redaing in " << aLine << "...done!\n";

		}
	}

	 cityLoc = new int* [row];
	 clodCover = new int* [row];
	 pressure = new int* [row];

	for (int i = 0; i < row; ++i)
	{
		cityLoc[i] = new int[col];
		clodCover[i] = new int[col];
		pressure[i] = new int[col];
	}
	for (int i = 0; i < row; ++i)

	for (int j = 0; j < col; ++j)
	{
		cityLoc[i][j]=-1;
		clodCover[i][j]=-1 ;
		pressure[i][j]=-1;
	}

	cout << "Storing data from file\n";
	readFile("citylocation.txt", cityLoc);
	readFile("cloudcover.txt", clodCover);
	readFile("pressure.txt", pressure);

	cout << "citylocation.txt done\n";
	  cout<<"cloudcover.txt done\n";
	  cout<<"pressure.txt done\n";

}		  


int menue()
{
	int select = 0;
	//create matrix row
	cout << "\n--------------------------------------------------------" << endl;
	cout << "Welcome to weather information processing system \n\n" << endl;
	cout << "1) Read in and process a configuration file" << endl;
	cout << "2) Dispaly city map" << endl;
	cout << "3) Display cloud coverage map (Cloudiness Index)" << endl;
	cout << "4) Display cloud coverage map (LMH Symbol)" << endl;
	cout << "5) Display atmosphereic pressure map (Pressure Index)" << endl;
	cout << "6) Display atmosphereic pressure map (LMH Symbol)" << endl;
	cout << "7) Show weather forecast summary report" << endl;
	cout << "8) Exit" << endl;
	cout << endl;

	cout << "Please enter your chioce: ";
	cin >> select;
	cout << endl;
	return select;
}
 
int isValidIndex(int row, int col, int r, int c)
{
	return r >= 0 && c >= 0 && r < row&& c < col;
}
void setNegbour(int row,int col,int cityId,int val)
{
	for (int a = 0;a < row;a++)
	{
		for (int b = 0;b < col;b++)
		{
			if (cityLoc[a][b] == cityId)
			{
				
				for (int c = 0;c <3;c++)
				{
					for (int d = 0;d < 3;d++)
					{
						{
							if (isValidIndex(row, col, c + a - 1, d + b - 1)&& cityLoc[c + a - 1][d + b - 1] != cityId)
								cityLoc[c + a - 1][d + b - 1] = val;
						}
					}
				}
				
			}
		}
	}
}
void summary(int rows,int cols)
{


	

	int arr[3][3] = { 0 };
	setNegbour(rows, cols, 1, -2);
	for (int a = 0;a < rows;a++)
	{
		for (int b = 0;b < cols;b++)
		{
			if (cityLoc[a][b] == 1|| cityLoc[a][b] == -2)
			{
				//count      
				arr[0][0]++;                 //small city
				//cloud sum
				arr[0][1] += clodCover[a][b];
				//pressure sum
				arr[0][2] += pressure[a][b];

			}
		}
	}
	setNegbour(rows, cols, 2, -3);
	for (int a = 0;a < rows;a++)
	{
		for (int b = 0;b < cols;b++)
		{
			if (cityLoc[a][b] == 2 || cityLoc[a][b] == -3)
			{
				//count      
				arr[1][0]++;                 //small city
				//cloud sum
				arr[1][1] += clodCover[a][b];
				//pressure sum
				arr[1][2] += pressure[a][b];

			}
		}
	}
	setNegbour(rows, cols, 3, -4);

	for (int a = 0;a < rows;a++)
	{
		for (int b = 0;b < cols;b++)
		{
			if (cityLoc[a][b] == 3 || cityLoc[a][b] == -4)
			{
				//count      
				arr[2][0]++;                 
				//cloud sum
				arr[2][1] += clodCover[a][b];
				//pressure sum
				arr[2][2] += pressure[a][b];

			}
		}
	}
	for (int a = 0;a < rows;a++)
	{
		for (int b = 0;b < cols;b++)
		{
			if (cityLoc[a][b] <-1)
			{
				cityLoc[a][b] = -1;
			}
		}
	}
	string str;
	cout << "Weather Forecast Summary Report\n";
	cout << "City Name : Big_City\n";
	cout<<"City ID     : 3\n";
	cout << "Ave.Cloud Cover(ACC)    :" <<fixed<< setprecision(2) << arr[2][1] / (float)arr[2][0] << "(" << cloudLMH(arr[2][1] / (float)arr[2][0]) << ")\n";
	cout << "Ave.Pressure(AP)        :" <<fixed<<setprecision(2)<< arr[2][2] / (float)arr[2][0] << "(" << cloudLMH(arr[2][2] / (float)arr[2][0]) << ")\n";
	cout << "Probability of Rain(%)  :" <<fixed<<setprecision(2)<< probability(cloudLMH(arr[2][2] / (float)arr[2][0]), cloudLMH(arr[2][1] / (float)arr[2][0]),str)<<"\n";
	cout << str;

	cout << "City Name : Mid_City\n";
	cout << "City ID     : 2\n";
	cout << "Ave.Cloud Cover(ACC)    :" << fixed << setprecision(2) << arr[1][1] / (float)arr[1][0] << "(" << cloudLMH(arr[1][1] / (float)arr[1][0]) << ")\n";
	cout << "Ave.Pressure(AP)        :" << fixed << setprecision(2) << arr[1][2] / (float)arr[1][0] << "(" << cloudLMH(arr[1][2] / (float)arr[1][0]) << ")\n";
	cout << "Probability of Rain(%)  :" << fixed << setprecision(2) << probability(cloudLMH(arr[1][2] / (float)arr[1][0]), cloudLMH(arr[1][1] / (float)arr[1][0]), str) << "\n";
	cout << str;

	cout << "City Name : Small_City\n";
	cout << "City ID     : 1\n";
	cout << "Ave.Cloud Cover(ACC)    :" << fixed << setprecision(2) << arr[0][1] / (float)arr[0][0] << "(" << cloudLMH(arr[0][1] / (float)arr[0][0]) << ")\n";
	cout << "Ave.Pressure(AP)        :" << fixed << setprecision(2) << arr[0][2] / (float)arr[0][0] << "(" << cloudLMH(arr[0][2] / (float)arr[0][0]) << ")\n";
	cout << "Probability of Rain(%)  :" << fixed << setprecision(2) << probability(cloudLMH(arr[0][2] / (float)arr[0][0]), cloudLMH(arr[0][1] / (float)arr[0][0]), str) << "\n";
	cout << str;
}

int main()
{
	int rows = 0, cols = 0;

	while (true)
	{


		int choice = menue();
		
		switch (choice) {

		case 1:
		{

			configuration(rows, cols);
			break;
		}
		case 2:
		{
			if (rows != 0 && cols != 0)
				displayCoordinates(rows, cols, cityLoc,choice);
			break;

		}

		case 3:
		{
			if (rows != 0 && cols != 0)
				displayCoordinates(rows, cols, clodCover,choice);
			break;


		 }

		case 4:
		{
			if (rows != 0 && cols != 0)
				displayCoordinates(rows, cols, clodCover, choice);
			break;

		}
		case 5:
		{
			if (rows != 0 && cols != 0)
				displayCoordinates(rows, cols, pressure, choice);
			break;

		}case 6:
		{
			if (rows != 0 && cols != 0)
				displayCoordinates(rows, cols, pressure, choice);
			break;

		}
		case 7:
		{
			summary( rows,  cols);
			break;
		}
		case 8:
		{
			cout << "Exiting" << endl;
			exit(0);
		}
		default:
		{
			cout << "invalid chioce" << endl;
			
		}



		}

	}


	return 0;
}
