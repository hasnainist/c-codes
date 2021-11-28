#include<iostream>
#include<string>
#include<cmath>
using namespace std;

class patientRecord {
public:

	int id;
	string name;
	string date;
	string disease;
	string status;

	patientRecord(int i = 0, string n = "\0", string dat = "\0", string dis = "\0", string s = "\0")
	{
		id = i;
		name = n;
		date = dat;
		disease = dis;
		status = s;
	}

	void print()
	{

		cout << "Patient's ID:  \t" << id << endl;
		cout << "Name:          \t" << name << endl;
		cout << "Date of Admit: \t" << date << endl;
		cout << "Disease:       \t" << disease << endl;
		cout << "Status:        \t" << status << endl;
		cout << "------------------------------------------------------------------------------" << endl << endl;
	}

	void editRecord()
	{
		string t;
		cout << "Enter name: ";
		cin >> t;
		name = t;

		cout << "Enter date: ";
		cin >> t;
		date = t;

		cout << "Enter disease: ";
		cin >> t;
		disease = t;

		cout << "Enter status: ";
		cin >> t;
		status = t;

	}


};

class hospitalData {
	class node {
	public:
		patientRecord record;
		node* left;
		node* right;
		int level;

		node()
		{
			level = 0;
			left = nullptr;
			right = nullptr;
		}
		node(patientRecord obj)
		{
			level = 0;
			record = obj;
			left = nullptr;
			right = nullptr;
		}

	};

public:
	node* root;
	int size;

	hospitalData()
	{
		root = nullptr;
		size = 0;
	}

	void insert(patientRecord p)
	{
		insert_rec(root, p);
		size++;

		moveToRoot(p.id);

	}


	void moveToRoot(int id)
	{
		shift(root, id);
	}
	void shift(node*& ptr, int id)
	{
		if (ptr->record.id == id)
		{
			return;
		}
		else if (ptr->record.id > id)
		{
			shift(ptr->left, id);
			rotateRight(ptr);
		}
		else if (ptr->record.id < id) 
		{
			shift(ptr->right, id);
			rotateLeft(ptr);
		}
	}

	void shiftDesired(node*& ptr,int id, int lev)
	{
		if (ptr->record.id == id)
		{
			return;
		}
		else if (ptr->record.id > id)
		{
			shiftDesired(ptr->left, id ,lev);
			rotateRight(ptr);
		}
		else if (ptr->record.id < id)
		{
			shiftDesired(ptr->right, id,lev);
			rotateLeft(ptr);
		}
	}

	void insert_rec(node*& r, patientRecord p)
	{

		if (r == nullptr)
		{
			r = new node(p);

		}
		else
		{
			if (r->record.id != p.id)
			{
				if (r->record.id < p.id)
				{
					insert_rec(r->right, p);
				}

				if (r->record.id > p.id)
				{
					insert_rec(r->left, p);
				}
			}
		}


	}


	int levelAssigner(int id)
	{
		int c = 0;
		node* curr = root;
		if (curr->record.id == id)
		{
			curr->level = c;
		}
		else
		{
			while (curr->record.id != id)
			{
				if (curr->record.id < id)
				{
					curr = curr->right;
					c++;
				}
				else
				{
					curr = curr->left;
					c++;
				}
			}

			curr->level = c;

		}

		return c;

	}

	void outputAdmitted()
	{
		print_rec(root);
	}

	void print_rec(node* r)
	{
		if (r != nullptr)
		{
			print_rec(r->left);
			if (r->record.status == "admitted")
			{
				r->record.print();
			}
			print_rec(r->right);
		}
	}

	bool  search(int id, int lev)
	{
		
		node *found=search_recN(root, id);
		if (found != nullptr)
		{
			int nodeLevel = levelAssigner(found->record.id);
			if (nodeLevel <= lev)
			{
				cout << "Current level of the node is already better or equal to entered level !" << endl;
			}
			else
			{
				shiftDesired(root, id, lev);
			}
			return true;
		}
		else
			return false;
	}

	bool search_rec(node* r, int id)
	{
		if (r == nullptr)
		{

			return false;
		}
		else
		{
			
			if (r->record.id == id)
			{

				return true;
			}
			else
			{
				if (r->record.id < id)
				{
					return search_rec(r->right, id);
				}
				if (r->record.id > id)
				{
					return search_rec(r->left, id);
				}
			}
		}

	}

	node* searchN(int id)
	{
		return search_recN(root, id);
	}

	node* search_recN(node* r, int id)
	{
		if (r == nullptr)
		{
			return nullptr;
		}
		else
		{
			if (r->record.id == id)
			{
				return r;
			}
			else
			{
				if (r->record.id < id)
				{
					return search_recN(r->right, id);
				}
				if (r->record.id > id)
				{
					return search_recN(r->left, id);
				}
			}
		}

	}

	void output(int id)
	{
		node* curr = searchN(id);
		if (curr != nullptr)
			curr->record.print();

	}

	void edit(int id)
	{
		node* curr = searchN(id);
		if (curr != nullptr)
		{
			curr->record.editRecord();
		}
	}

	void remove(int id)
	{
		remove_rec(root, id);
	}

	void remove_rec(node*& r, int id)
	{
		if (r != nullptr)
		{
			if (r->record.id == id)
			{
				if (r->left == nullptr && r->right == nullptr)
				{
					delete r;
					r = nullptr;
				}

				else if (r->left != nullptr && r->right == nullptr)
				{
					node* temp = r->left;
					delete r;
					r = temp;
				}
				else if (r->left == nullptr && r->right != nullptr)
				{
					node* temp = r->right;
					delete r;
					r = temp;
				}
				else if (r->left != nullptr && r->right != nullptr)
				{
					r = findmax(r->left);
					remove_rec(r->left, id);

				}

			}
			else
			{
				if (id < r->record.id)
				{
					remove_rec(r->left, id);
				}
				if (id > r->record.id)
				{
					remove_rec(r->right, id);
				}
			}
		}
	}

	node* findmax(node*& n)
	{
		node* max = n;
		if (n != nullptr)
		{

			while (n != nullptr)
			{

				if (n->record.id > max->record.id)
				{
					max = n;

				}
				n = n->right;

			}
		}
		return max;
	}

	node* rotateRight(node*& X)
	{

		node* Y = X->left;
		X->left = Y->right;
		Y->right = X;

		X->level++;
		Y->level--;

		X = Y;

	

		return X;
	}

	node* rotateLeft(node*& X)
	{

		node* Y = X->right;
		X->right = Y->left;
		Y->left = X;

		X->level++;
		Y->level--;

		X = Y;
		

		return X;
	}

	void printRoot()
	{
		cout << "root node is :" << endl;
		root->record.print();
	}

	int Median()
	{
		int val=0;
		int median = 0;
		int counter = -1;

		median= medianFinder(root, val, counter);
	
		return median;

	}

	int medianFinder(node* r, int &val, int &counter)
	{
		int index = size / 2;
		if (r != nullptr)
		{
			
			medianFinder(r->left,val,counter);
			
			
			counter++;
			if (counter == index)
			{

				val = r->record.id;
			}
			medianFinder(r->right, val, counter);

		}
		
		return val;
	}

	void split()
	{
		int med = Median();
		moveToRoot(med);

	}


	void showBST()
	{
		leveler(root);
		int h = height(root);
		int spaces = h;

		cout << "_________________________________________________________________" << endl;
		for (int i = 0; i <h; i++)
		{
			printLevelWise(root, i,spaces);
			cout << endl;
			cout << endl;
		}
		cout << "_________________________________________________________________" << endl;



	}

	void printLevelWise(node *r, int l,int s)
	{
		if (r != nullptr)
		{
			printLevelWise(r->left,l,s);
			if (r->level == l)
			{
				for (int i = s; i > l-s; i--)
				{
					cout << "\t";
				}
				cout  << r->record.id << "  ";
			}
			printLevelWise(r->right,l,s);
		}
	}

	void leveler(node* r)
	{
		if (r != nullptr)
		{
			leveler(r->left);
			levelAssigner(r->record.id);
			leveler(r->right);
		}
	}

	int height(node* r)
	{
		int left = 0;
		int right = 0;
		if (r == nullptr)
		{
			return 0;
		}
		else
		{
			left = height(r->left) + 1;
			right = height(r->right) + 1;
		}

		if (left >= right)
			return left;
		else
			return right;
	}

	
};


int main()
{


	hospitalData hos;

	patientRecord has(3, "usman", "24-sep-2010", "flu", "admitted");
	patientRecord fai(1, "khalid", "14-jun-2015", "depression", "admitted");
	patientRecord mee(2, "ali", "07-sep-2020", "lukemea", "admitted");
	patientRecord akb(7, "hasnain", "28-feb-2014", "corona", "discharged");
	patientRecord qaz(4, "umer", "28-feb-2014", "corona", "admitted");


	hos.insert(has);
	hos.insert(fai);
	hos.insert(mee);
	hos.insert(akb);
	hos.insert(qaz);

	hos.outputAdmitted();

	hos.showBST();

	cout << "after searching 3" << endl;
		hos.search(3, 0);

		hos.showBST();

		cout << "after splitting" << endl;
		hos.split();

		hos.showBST();
	
		

	  
		cout << "after removing 2" << endl;
	   hos.remove(2);
	   hos.showBST();
	 

	   hos.output(7);


	system("pause");
	return 0;
}