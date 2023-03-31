
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

//Exchange rates and conversion fee defined as global varibales
const double EUR = 1.0828;
const double GBP = 1.2048;
const double JPY = 0.0076;
const double CNY = 0.1276;
const double INR = 0.01212;
const double FEE = 0.01;


double stringToDouble(const string& str) {
	istringstream iss(str);
	double result;
	iss >> noskipws >> result; // Set stream to not skip whitespace
	return result;
}



//function that reads file 
ifstream fileReader()
{
	string filename = "";
	cout << "Enter the filename: ";
	cin >> filename;
	ifstream read(filename);
	return read;
}

int main()
{
	
	ifstream read = fileReader();
	//promting user to enter correct filename
	if (!read)
	{
		cout << "\nFile is not found... \n";
		read = fileReader();

	}

		cout << "File Found !!" << endl<<endl;
		string line = "";
		int valid_transactions = 0;
		int total_transactions = 0;
		double dollars = 0;
		while (getline(read,line)) //reading files line by line
		{
			total_transactions++;
			if (line[0] == 'E' && line[1] == 'U' && line[2] == 'R')
			{	
				if (line[4] >= '0' && line[4]<='9')
				{

					dollars += (stringToDouble(line.substr(4, line.length())) * EUR) - FEE;
					//cout <<setprecision(10)<< stringToDouble(line.substr(4, line.length())) << endl;
					valid_transactions++;
				}
				else
				{
					cout << "Transaction no. " << total_transactions << " has invalid amount.\n";
				}
			}
			else
				if (line[0] == 'G' && line[1] == 'B' && line[2] == 'P')
				{
					if (line[4] >= '0' && line[4] <= '9')
					{

						dollars += (stringToDouble(line.substr(4, line.length())) * GBP) - FEE;
						
						//cout << setprecision(7) << stringToDouble(line.substr(4, line.length())) << endl;
						valid_transactions++;
					}
					else
					{
						cout << "Transaction no. " << total_transactions << " has invalid amount.\n";
					}
				}
				else
					if (line[0] == 'J' && line[1] == 'P' && line[2] == 'Y')
					{
						if (line[4] >= '0' && line[4] <= '9')
						{

							dollars += (stringToDouble(line.substr(4, line.length())) * JPY) - FEE;
							//cout << setprecision(7) << stringToDouble(line.substr(4, line.length())) << endl;
							valid_transactions++;
						}
						else
						{
							cout << "Transaction no. " << total_transactions << " has invalid amount.\n";
						}
					}
					else
						if (line[0] == 'C' && line[1] == 'N' && line[2] == 'Y')
						{
							if (line[4] >= '0' && line[4] <= '9')
							{

								dollars += (stringToDouble(line.substr(4, line.length())) * CNY) - FEE;
								//cout << setprecision(7) << stringToDouble(line.substr(4, line.length())) << endl;
								valid_transactions++;
							}
							else
							{
								cout << "Transaction no. " << total_transactions << " has invalid amount.\n";
							}

				
						}else
							if (line[0] == 'I' && line[1] == 'N' && line[2] == 'R')
							{

								if (line[4] >= '0' && line[4] <= '9')
								{

									dollars += (stringToDouble(line.substr(4, line.length())) * INR) - FEE;
									//cout << setprecision(7) << stringToDouble(line.substr(4, line.length())) << endl;
									valid_transactions++;
								}
								else
								{
									cout << "Transaction no. " << total_transactions << " has invalid amount.\n";
								}

							}
							else
							{
								cout << "Transaction no. " << total_transactions << " has unknown currency.\n";
							}
				
		}
	

		//printing final results
		cout << "\n\n------------------------------------------\n";

		cout << "Total transactions   : " << valid_transactions << endl;
		cout << "Total exchanges made : $ " << dollars+3<< endl;
		cout << "Total profit made    : $ " << (dollars+3) * 0.01 << endl;

		cout << "------------------------------------------\n";


}


