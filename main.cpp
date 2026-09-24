// Yusuf Arik
 
#include <iostream>
#include <string>
#include <stdexcept>
 
using namespace std;
 
//pass in space-delimited arguments when you call the executable
//Example: ./a.out 1 2 3.3
int main( int argc, char * argv[] )
{
 
	// VARIABLE INITIALIZATION
	double loan_amount = 0;
	double yearly_interest_rate = 0;
	double interestRate = 0;
	double interestRateC = 0;
	double monthly_payment = 0;
	double interestTotal = 0;
	double interest = 0;
	double principal = 0;
	double payment = 0; 
	int currentMonth = 0;
 
	if (argc > 4) 
	{
		cout << "Too many arguments. Cannot pass in more than three." << endl;
		return -1;
	}
 
	int i = 1;
	double arguments [3] = {0, 0, 0};
 
	if (argc > 1)
	{
		while ( i < argc )
		{
 
			try
			{
				arguments[i-1] = stod(argv[i]);
			}
			catch(const std::invalid_argument&)
			{
				if(i==1)
					cout << "(Invalid loan amount): " << argv[i] << endl;
				else if (i==2)
					cout << "(Invalid interest rate): " << argv[i-1] << " " << argv[i] << endl;
				else
					cout << "(Invalid payment): " << argv[i-2] << " " << argv[i-1] << " " << argv[i] << endl;
				return -2;
			}
			i++;
		}
	}
 
	// CURRENCY FORMATTING
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
 
	loan_amount = arguments[0];
	yearly_interest_rate = arguments[1];
	monthly_payment = arguments[2];
 
//User input (don't need cin since Sardinas added in the main)
// need positive loan
	if (argc < 2 || loan_amount <= 0)
	{
		cout << "(Invalid loan amount): " << (argc > 1 ? argv[1] : "missing")
		     << " -- the loan must be positive." << endl;
		return -2;
	}
	cout << "\nLoan Amount: " << argv[1] << endl;

	if (argc < 3 || yearly_interest_rate < 0)
	{
		cout << "(Invalid interest rate): " << argv[1] << " " << (argc > 2 ? argv[2] : "missing")
		     << " -- the interest rate cannot be negative." << endl;
		return -2;
	}
	cout << "Interest Rate (% per year): " << argv[2] << endl;
 
	// GET PROPER INTEREST RATES FOR CALCULATIONS
	interestRate = yearly_interest_rate / 12;
	interestRateC = interestRate / 100;
 
	// need make sure monthly payment is sufficient
	if (argc < 4 || monthly_payment <= 0)
	{
		cout << "(Invalid payment): " << argv[1] << " " << argv[2] << " "
		     << (argc > 3 ? argv[3] : "missing")
		     << " -- the monthly payment must be positive." << endl;
		return -2;
	}
	cout << "Monthly Payments: " << argv[3] << endl;
 
	// MAke sure furst regular payment must is larger than the first month's interest
	// or else the loan never gets paid off unless one payment covers it all
	if (monthly_payment <= loan_amount * interestRateC && loan_amount * (1 + interestRateC) > monthly_payment)
	{
		cout << "(Insufficient payment): the monthly payment $" << monthly_payment
		     << " must be larger than the monthly interest $" << loan_amount * interestRateC
		     << "." << endl;
		return -3;
	}
 
	cout << endl;
 
	// AMORTIZATION TABLE
	cout << "***************************************************************\n"
	     << "\tAmortization Table\n"
	     << "***************************************************************\n"
	     << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";
 
	// LOOP TO FILL TABLE
	while (loan_amount > 0) {
		if (currentMonth == 0) {
			cout << currentMonth++ << "\t$" << loan_amount;
			if (loan_amount < 1000) cout << "\t"; // Formatting MAGIC
			cout << "\t" << "N/A\tN/A\tN/A\t\tN/A\n";
		}
		else {
 
			// Properly Calculate and display monthly payment and principal
			interest = loan_amount * interestRateC;
 
			if (loan_amount * (1 + interestRateC) <= monthly_payment) {
				payment = loan_amount * (1 + interestRateC);
				principal = loan_amount;
				loan_amount = 0;
			}
			else {
				payment = monthly_payment;
				principal = monthly_payment - interest;
				loan_amount -= principal;
			}
			interestTotal += interest;
 
			cout << currentMonth++ << "\t$" << loan_amount;
 
			//adding this fully from the hint
			if (loan_amount < 1000) cout << "\t"; // Formatting MAGIC
			cout << "\t$" << payment << "\t";
 
			cout.unsetf(ios::fixed | ios::showpoint);
			cout << interestRate;
			cout.setf(ios::fixed | ios::showpoint);
 
			cout << "\t$" << interest << "\t\t$" << principal << "\n";
		}
	}
	cout << "***************************************************************\n";
	cout << "\nIt takes " << --currentMonth << " months to pay off "
	     << "the loan.\n"
	     << "Total interest paid is: $" << interestTotal;
	cout << endl << endl;
	return 0;
}
