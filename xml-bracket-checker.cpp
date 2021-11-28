#include <iostream>
#include <fstream>
using namespace std;

template<class T>
class Stack {
private:
	class Node {
	public:
		T data;
		Node * next;

		Node()
		{
			data = 0;
			next = nullptr;
		}
		Node(T d)
		{
			data = d;
			next = nullptr;
		}
	};
	Node * top;
public:
	Stack()
	{
		top = nullptr;
	}
	~Stack()
	{
		if (top != nullptr)
		{
			Node * ptr = top->next;
			while (top->next != nullptr)
			{
				delete top;
				top = ptr;
				ptr = ptr->next;
			}
		}
	}
	bool IsEmpty()
	{
		if (top == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool push(const T& val)
	{
		Node *temp=new Node(val);
		if (top == nullptr)
		{
			top = temp;
		}
		else
		{
			temp->next = top;
			top = temp;	
		}
		return true;

	}
	bool pop(T& val)
	{
		if (IsEmpty())
		{
			return false;
		}
		else
		{
			Node* ptr = top->next;
			val = top->data;
			delete top;
			top = ptr;
			return true;
		}
	}
	bool Top(T& val)
	{
		if (IsEmpty())
		{
			return false;
		}
		else
		{
			val = top->data;
			return true;
		}
	}
	void print()
	{
		Node* ptr = top;
		while (ptr != nullptr)
		{
			cout << ptr->data << "\n";
			ptr = ptr->next;
		}
		cout << "----------------------------------------------\n";
	}
	
};

class xml {
public:
	string tag;
	int line;

	xml()
	{
		tag = "";
		line = 0;
	}

	xml(string s,int l)
	{
		tag = s;
		line = l;
	}

	void print()
	{
		cout << '"' << tag << '"' << " mismatch at line no. " << line << "\n";
	}
};

int main()
{
	Stack<xml>stack; 
	
	
	int Line = 0;                             
	ifstream read; char str[100];
	read.open("input.xml");        //reading the xml file
	if (read.is_open())
	{
		while (!read.eof())
		{
			
			Line++; string tag;
			Stack<char> stc_tag;
			Stack<char> stc_quo;
			string temp;
			read.getline(str,100);
			for (int i = 0; i < strlen(str); i++)   // checking for brackets and quotations
			{
				char c;
				if (Line == 1)            //checking for prolog errors
				{
					if (str[1] != '?')
					{
						xml data("?", Line);
						cout << "opening ";
						data.print();
						break;
					}
					if (str[strlen(str) - 2] != '?')
					{
						xml data("?", Line);
						cout << "closing ";
						data.print();
						break;
					}
				}              //
				if (str[i] == '<')
				{
					
					stc_tag.push(str[i]);
					continue;
				}
				if (str[i] == '>')
				{
					
					 stc_tag.Top(c);
					if (c == '<')
					{
						stc_tag.pop(c);
						continue;
					}
					else
					{
						stc_tag.push(str[i]);
						continue;
					}
				}
				if (str[i] == '"'|| int(str[i])==39 )
				{
					
					stc_quo.Top(c);
					if (c == '"')
					{
						
						stc_quo.pop(c);
					}
					else
					{
						
						stc_quo.push('"');
						if (str[i - 1] != '=')
						{
							xml data( "=", Line);
							data.print();
						}

					}

				}
				if (str[i] == '=')
				{
					if (str[i + 1]=='"'|| int(str[i + 1]) == 39  )
					{
						
					}
					else
					{
						xml data("", Line);
						data.print();
					}
					
				}


			}   

			bool flag = false;
			bool flag2 = false;
			bool tag_read = false;

			if (Line>1)
			{
				for (int i = 0; i < strlen(str); i++)   //isolating tags from lines to check thier balance
				{

					if (str[i] == '<')
					{
						
						flag = true;
						flag2 = false;
					}

					if (str[i] == ' ')
					{
						flag2 = true;

					}
					if (str[i] == '>')
					{
						flag = false;
						flag2 = false;
						temp = temp + '>';
						tag_read = true;
					}
					if (tag_read)
					{
						if (temp[1] != '/') //checking for closing tag
						{

							xml data(temp, Line);
							stack.push(data);
							
						}
						else
						{
							
							xml data; string s;
							stack.Top(data);
							for (int i = 0; i < temp.size(); i++)
							{ 
								if (i == 1)
								{
									continue;
								}
								s += temp[i];
							}
							
							if (data.tag == s)
							{
								stack.pop(data);
								
							}
							else
							{
								//stack.push(data);
								
							}
						}
						
						tag_read = false;
						temp = "";
					}

					if (flag == true && flag2 == false)
					{
						temp = temp + str[i];
					}
				}
			}

			
		
		
			if (!stc_tag.IsEmpty())         //brackets mismatches
			{
				xml data("<,>", Line);
				data.print();
			}
			if (!stc_quo.IsEmpty())         //quotation mismatches
			{
				xml data("", Line);
				data.print();
			}
		}
	}
	
	if (!stack.IsEmpty())              //tag mismatch
	{
		while (!stack.IsEmpty())
		{
			xml data;
			stack.Top(data);
			cout <<'"' << data.tag <<'"' << " tag mismatch at line no." << data.line << endl;
			stack.pop(data);
		
		}
	}

	
	return 0;
}

