#include <iostream>
#include <cmath>
using namespace std;

class Polynomial {
public:
	class Term {
	public:
		int exponent;
		int coefficient;
		Term *next;

		Term()
		{
			exponent = 0;
			coefficient = 0;
			next = nullptr;
		}
		Term(int c,int e)
		{
			exponent = e;
			coefficient = c;
			next = nullptr;
		}
		void input()
		{

				cout << "Coefficient: ";
				cin >> coefficient;
				cout << "Exponent: ";
				cin >> exponent;
				
				while (exponent < 0)
				{
					cout << "enter positive exponent : ";
					cin >> exponent;
				}
				

		}

	};

	int size;
	Term* head;

	Polynomial()
	{
		size = 0;
		head = nullptr;
	}

	void input()
	{
		//cout << "____________________________________________________________________________" << endl;
		cout << "Enter number of terms in the polynomial: ";
		cin >> size;
		Term* pre = head;

		for (int i = 0; i < size; i++)
		{
			cout << endl;
			Term* term = new Term;
			cout << "Term No." << i + 1 << " \n";
			term->input();
		

			//conditions to get sorted terms in polynomial
			if (i == 0)
			{
				head = term;
				
			}
			else {
				if (i == 1)
				{
					if (term->exponent >= pre->exponent)
					{
						term->next = pre;
						pre->next=nullptr;
						head = term;
					}
					else
					{
						pre->next = term;
						term->next = nullptr;
						head = pre;
					}

				}
				else
				{
				
					if (term->exponent > head->exponent || term->exponent == head->exponent)
					{
						term->next = head;
						head = term;
					}
					else {
						Term* ptr = head;
						Term* p = nullptr;
						while (ptr != nullptr)
						{
							if (ptr->exponent < term->exponent )
							{
								break;
							}
							p = ptr;
							ptr = ptr->next;
						}
						p->next = term;
						term->next = ptr;
					}
				}
			}
			pre = term;
		}

		// adding terms with same exponents
		

			Term* ptr = head;
			Term* post = head->next;

			while (post != nullptr)
			{
				bool flag = false;
				if (ptr->exponent == post->exponent)
				{
					ptr->coefficient = ptr->coefficient + post->coefficient;
					ptr->next = post->next;
					delete post;
					flag = true;
					size--;
					post = ptr->next;
				}
				if (flag == false)
				{
					ptr = ptr->next;
					post = ptr->next;
				}
			}
			// if there is any term with zero coeeficient after above addition
			ptr = head;
			pre = nullptr;
			while (ptr != nullptr)
			{
				if (ptr->coefficient == 0)
				{
					if (ptr == head)
					{
						Term* n = head->next;
						delete head;
						head = n;
					}
					else
					{
						pre->next = ptr->next;
						delete ptr;
						ptr = pre->next;
						continue;
					}
				}
				pre = ptr;
				ptr = ptr->next;
			}
	}

	void output()
	{
		Term* ptr = head;
		while (ptr != nullptr)
		{
			if (ptr == head) {
				if (ptr->exponent == 0)
				{
					cout << ptr->coefficient ;
				}
				else
				cout << ptr->coefficient << "n^" << ptr->exponent;
			
			}
			else
			{
			
				if (ptr->coefficient < 0)
				{
					if (ptr->exponent == 0)
					{
						cout <<" -" << ptr->coefficient ;
					}
					else
					cout <<" -" << ptr->coefficient << "n^" << ptr->exponent<<" ";
				}
				if (ptr->coefficient > 0)
				{
					if (ptr->exponent == 0)
					{
						cout<< " +" << ptr->coefficient ;
					}
					else
					cout << " +" << ptr->coefficient << "n^" << ptr->exponent << " ";
				}
			}
			ptr = ptr->next;
		}
		cout <<"\n----------------------------------------------------------------------------" << endl;
	}

	Polynomial(const Polynomial & obj)
	{
		Term* ptr = obj.head;
		Term* pre = nullptr;
		this->size = obj.size;


		for (int i = 0; i < obj.size; i++)
		{
			Term* temp = new Term(ptr->coefficient,ptr->exponent);
	
			if (i == 0)
			{
				this->head = temp;
				pre = temp;
			}
			else
			{
				pre->next = temp;
			}

				pre = temp;
				ptr = ptr->next;
			

		}
		
	}
	
	double Evaluate(double num)
	{
		double sum = 0;
		Term* ptr = head;
		for (int i = 0; i < size; i++)
		{
			sum = sum + ((ptr->coefficient)*(pow(num,ptr->exponent)));
			ptr = ptr->next;
		}

		return sum;
	}

	void insertAtEnd(int c, int e, Term* &tail)
	{
		Term* temp = new Term(c, e);
		if (this->head == nullptr)
		{
			this->head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		this->size++;
	}
	
	Polynomial Add(Polynomial &obj)
	{
		Term* ptr1 = this->head;
		Term* ptr2 = obj.head;
		Term* pre = nullptr;
		Polynomial sum;
		

		while (ptr1 != nullptr && ptr2!=nullptr )  //polynomial with less terms will exhaust and loop will end
		{
			if (ptr1->exponent == ptr2->exponent)
			{
				sum.insertAtEnd(ptr1->coefficient + ptr2->coefficient, ptr1->exponent, pre);
				ptr1 = ptr1->next;
				ptr2 = ptr2->next;
				continue;
			}

			if (ptr1->exponent < ptr2->exponent)
			{
				sum.insertAtEnd(ptr2->coefficient, ptr2->exponent, pre);
				ptr2 = ptr2->next;
				continue;
			}
			if (ptr1->exponent > ptr2->exponent)
			{
				sum.insertAtEnd(ptr1->coefficient, ptr1->exponent, pre);
				ptr1 = ptr1->next;
				continue;
			}

		}

		Term* rem = nullptr;
		if (ptr1 == nullptr)
		{
			rem = ptr2;
		}
		if (ptr2 == nullptr)
		{
			rem = ptr1;
		}
	
		//concatinating remaining terms

		while (rem != nullptr)
		{
			sum.insertAtEnd(rem->coefficient, rem->exponent, pre);
			rem = rem->next;
		}
		 
		
		return sum;
	
	}

	Polynomial Multiply(Polynomial& obj)
	{
		Term* ptr1 = this->head;
		Term* ptr2 = obj.head;
		Term* tail = nullptr;
		Polynomial mul;
		int count = 0;
		Polynomial* p = new Polynomial[this->size];
		while (ptr1 != nullptr)
		{
			ptr2 = obj.head;
			while (ptr2 != nullptr)
			{
				int c = ptr1->coefficient * ptr2->coefficient;
				int e = ptr1->exponent + ptr2->exponent;
				p[count].insertAtEnd(c, e, tail);

				ptr2 = ptr2->next;
			}
			ptr1 = ptr1->next;
			tail = nullptr;
			count++;
		}

		
		for (int i = 0; i < this->size; i++)
		{
			mul = mul + p[i];
		}
		return mul;
	}

	Polynomial operator =(const Polynomial& obj)
	{

		Term* ptr = obj.head;
		Term* pre = nullptr;
		this->size = obj.size;
	
		for (int i = 0; i < obj.size; i++)
		{

			Term* temp = new Term(ptr->coefficient, ptr->exponent);

			if (i == 0)
			{
				this->head = temp;
				pre = temp;
			}
			else
			{
				pre->next = temp;
			}
				pre = temp;
				ptr = ptr->next;
			
			
		}
		
		return *this;
	}

	Polynomial operator+(Polynomial &obj)
	{
		
		Polynomial sum = this->Add(obj);
		return sum;
		
	}

	Polynomial operator *(Polynomial& obj)
	{
		Polynomial mul = this->Multiply(obj);
		return mul;
	}

	double operator[](double num)
	{
		double sum = 0;
		Term* ptr = head;
		for (int i = 0; i < size; i++)
		{
			sum = sum + ((ptr->coefficient) * (pow(num, ptr->exponent)));
			ptr = ptr->next;
		}

		return sum;
	}

	~Polynomial()
	{
		bool flag = false;
		if (head != nullptr)
		{
			flag = true;
		}

		if (flag) {
			Term* pre = this->head;

			Term* post = this->head->next;
			for (int i = 0; i < size; i++)
			{
				if (post == nullptr)
				{
					break;
				}
				delete pre;
				pre = post;
				post = post->next;
			}
		}
		
	}

}; 




int main()
{
	Polynomial p;
	p.input();
	p.output();

	Polynomial p2;
	p2.input();
	p2.output();

	cout << "Enter real number to evaluate value in first polynomial: ";
	int n;
	cin >> n;
	cout << p[n] << endl;


	cout << "Adding both polynomials\n";
	Polynomial p3;
	p3 = p+p2;
	p3.output();
	
	cout << "Multiplying both polynomials\n";
	Polynomial p4 = p*p2;
	p4.output();
	system("pause");
	return 0;
} 