#include <iostream>
#include<queue>														//Library for Queue
using namespace::std;
int steps = 0;														//count the steps for solution
class Game													
{
private:
	char Initial[3][3] = { 'a','b','c','d','e','f','g','h','i' };				//The default initial condition
	char Final[3][3] = { ' ','1','2','3','4','5','6','7','8' };					//The goal state
	struct node																	//node structure
	{
		char data[3][3];
		node* parent;
		int x, y;
		bool equal;
	};														
public:
	void Board(char Initial[3][3])																	//to display the square box
	{
		cout << endl << endl << "__________________" << endl;
		cout << "|     |     |     |" << endl;
		cout << "|  " << Initial[0][0] << "  |  " << Initial[0][1] << "  |  " << Initial[0][2] << "  |" << endl;

		cout << "|_____|_____|_____|" << endl;
		cout << "|     |     |     |" << endl;

		cout << "|  " << Initial[1][0] << "  |  " << Initial[1][1] << "  |  " << Initial[1][2] << "  |" << endl;

		cout << "|_____|_____|_____|" << endl;
		cout << "|     |     |     |" << endl;

		cout << "|  " << Initial[2][0] << "  |  " << Initial[2][1] << "  |  " << Initial[2][2] << "  |" << endl;

		cout << "|_____|_____|_____|" << endl << endl;
	}											
	void Addvalues()																	//to add values from user.
	{
		int x, y;
		cout << "Please enter 0 in the place where you want empty feild. " << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//if (i == a && j == b)
					//continue;
				cout << "enter value for matrix place " << Initial[i][j] << " : ";
				cin >> Initial[i][j];
				if (Initial[i][j] == '0')
				{
					Initial[i][j] = ' ';
					x = i;
					y = j;
				}
			}
		}
		system("cls");
		cout << "YOUR MATRIX IS" << endl << endl;
		Board(Initial);
		cout << endl << endl;
		system("pause");
		system("cls");
		BFS(Initial, Final, x, y);
	}
	node* Addnewnode(char Initial[3][3], int x, int y, int newx, int newy, node* parent)				//to add new node
	{
		node* newnode = new node;
		newnode->parent = parent;
		memcpy(newnode->data, Initial, sizeof newnode->data);
		swap(newnode->data[x][y], newnode->data[newx][newy]);
		newnode->x = newx;
		newnode->y = newy;

		return newnode;
	}
	int Checkequality(char newmatrixnode[3][3], char Final[3][3])							//chech if the given node at final state are same
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (newmatrixnode[i][j] && newmatrixnode[i][j] != Final[i][j])
					return false;
			}
		}
		return true;
	}
	void Reachtoroot(node* temp)															//recursive function to reach root
	{
		if (temp == NULL)
		{
			return;
		}
		Reachtoroot(temp->parent);
		cout << " STEP NO. " << ++steps << endl << endl;
		Board(temp->data);
	}
	int row[4] = { 1, 0, -1, 0 };																	//the values for row addition
	int column[4] = { 0, -1, 0, 1 };																//the values for column addition			
	int Correct_Place(int x, int y)																	//check if the swap place is correct or not
	{
		return (x >= 0 && x < 3 && y >= 0 && y < 3);
	}
	void BFS(char Initial[3][3], char Final[3][3], int x, int y)									//Breath First Search Function
	{
		queue<node*>list;
		bool see;
		node* root = Addnewnode(Initial, x, y, x, y, NULL);
		root->equal = Checkequality(Initial, Final);
		list.push(root);

		while (!list.empty())
		{
			node* temp = list.front();
			list.pop();
			if (temp->equal)
			{
				Reachtoroot(temp);
				return;
			}
			for (int i = 0; i < 4; i++)
			{
				if (Correct_Place(temp->x + row[i], temp->y + column[i]))
				{
					node* child = Addnewnode(temp->data, temp->x, temp->y, temp->x + row[i], temp->y + column[i], temp);
					child->equal = Checkequality(child->data, Final);
					if (child->equal)
					{
						Reachtoroot(child);
						cout << "HURRAAAHHHH!! GOT THE FINAL STATE:" << endl;
						return;
					}
					list.push(child);
				}
			}
		}
	}
	void Instruction()																				// Instructions on how to play game
	{
		cout << "***************************WELCOME TO 8 PUZZLE SOLVER********************" << endl << endl;
		cout << "Please read the instructions carefully.\n1: Enter values from 1 to 8 anywhere you want." << endl;
		cout << "2: Enter 0 on that tile where you want blank space.\n3: PLEASE DO NOT ENTER DUBLICATE VALUES." << endl;
		cout << "4: The Final goal is set to be:\n0 1 2\n3 4 5\n6 7 8\n";
		cout << "5: The solution will be found by AI so don't worry it will be 100% correct.\nButthere are some matrixes for which the Final state will not be possible so for them the program will be terminated without given any solution.\n\n So Let's begin...\n\n" << endl;
		system("pause");
		system("cls");
		Board(Initial);
		Addvalues();
	}
};
int main()
{
	Game Call;															//instance of class game
	Call.Instruction();													//Call instructions function
}