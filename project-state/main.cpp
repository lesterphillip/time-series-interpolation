#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

double interpolate(vector <long double> y, long double t[],
  long double newt, int n);

int main(int argc, const char * argv[]) {
  //CHECK FOR AVAILABILITY OF FILE AND OPEN IT
  string inFileName;
  cout << "Filename: ";
  cin >> inFileName;
  fstream inFileStr(inFileName.c_str(), ios::in);
  vector <long double> Given_y;
    
  //CHECK IF FILE IS VALID
  if(inFileStr.fail())
  {
    cerr << "Unable to open " << inFileName << endl;
    return 0;
  }
    
  //CHECK IF FILE IS EMPTY
  if (inFileStr.peek() == EOF)
  {
    cout << "The file is empty. Exiting..." << endl;
    return (0);
  }
    
  //CHECK IF FILE HAS INTEGERS IN IT
  double data;
  if (isdigit(inFileStr.peek())|| inFileStr.peek() == '-')
  {
    while (inFileStr >> data)
    {
      Given_y.push_back(data);
    }
  }
    
  //CHECK IF FILE HAS NON-NUMERIC CHARACTERS IN IT
  else
  {
    cerr << "You inputted an invalid file. Enter a .txt file "
    << "containing numbers only." << endl;
    return 0;
  }
  
  /*  
  for( vector<long double>::iterator i = Given_y.begin(); i != Given_y.end(); i++)
  {
    cout << *i << endl;
  }
  */
  
  int Given_samplenumber = Given_y.size();
  cout << "Number of points: " << Given_samplenumber << endl << endl;
  
  int Given_Fs, New_Fs; 
  cout << "Enter the original sampling rate in Hz: " << endl;
  cin >> Given_Fs;
  cout << "Enter the new sampling rate in Hz: " << endl;
  cin >> New_Fs; 
    
  long double Given_Time[Given_samplenumber];
  for (int i = 0; i<Given_samplenumber; i++)
  {
    Given_Time[i]=(1.0000/Given_Fs)*i;
  }
    
  long double New_samplenumber = (1.0*New_Fs/Given_Fs)*Given_samplenumber;
  cout << endl << "New sampling size: " << int(New_samplenumber) << endl;
  long double New_Time[int(New_samplenumber)];
	
  for (int i = 0; i < New_samplenumber; i++)
  {
    New_Time[i] = (1.0000/New_Fs)*i;
    //cout << New_Time[i] << endl;
  }
	
  long double output[int(New_samplenumber)];
  for (int i=0; i < int(New_samplenumber); i++)
  { 
    output[i] = interpolate(Given_y, Given_Time, New_Time[i],
      Given_samplenumber);
    cout << "Value of f(" << New_Time[i] << ") is : " << output[i] << endl;
  }
  
  cout << "To save these results in a .txt file, ";
  system("pause");
	
  cout.precision(6);
  ofstream textFile;
  textFile.open("outputResults.txt");
  if(textFile.is_open())
  {
	for(int k=0; k<New_samplenumber; k++)
	{
	  textFile << fixed << output[k] << endl;
	}
  }
  textFile.close();
  return 0; 
}

double interpolate(vector <long double> y, long double t[],
  long double newt, int n)
{
  double result = 0;    
  for (int i=0; i<n; i++)
  {
    long double term = y.at(i);
    for (int j=0;j<n;j++)
    {
      if (j!=i)
        term = term*(newt - t[j])/(t[i] - t[j]);
    }
    result += term;
  }
  return result;
}
