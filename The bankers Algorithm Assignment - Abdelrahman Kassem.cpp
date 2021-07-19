
#include <iostream>
#include <vector>
using namespace std;


int safe_seq
(	int n,
	int m,
	vector<vector<int>> allocation,
	vector<vector<int>> max,
	vector<int> available,
	vector<vector<int>> need,
	vector<int> &finish_flag,
	vector<int> &result)
{
	int index = 0;

	fill(finish_flag.begin(), finish_flag.end(), 0);
	fill(result.begin(), result.end(), -1);

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			if (finish_flag[i] == 0)
			{

				int flag = 0;
				for (int j = 0; j < m; j++)
				{
					if (need[i][j] > available[j])
					{
						flag = 1;
						break;
					}
				}

				if (flag == 0)
				{
					result[index++] = i;
					for (int y = 0; y < m; y++)
						available[y] += allocation[i][y];
					finish_flag[i] = 1;
				}
			}
		}
	}

	int safe_flag=1;
	for(int i = 0; i < n;i++)
	{
		if(result[i] == -1 || finish_flag[i] == 0)
		{
			safe_flag=0;
		}
	}
	return safe_flag;
}

int request_grant
(	int n,
	int m,
	vector<vector<int>> &allocation,
	vector<vector<int>> max,
	vector<int> &available,
	vector<vector<int>> &need,
	vector<int> &finish_flag,
	vector<int> &result,
	int requested_process,
	vector<int> req_process)
{
	//test vectors so we not mess with the original data until we are sure that request is granted
	vector<vector<int>> alloc_test = allocation;
	vector<vector<int>> need_test = need;
	vector<int> avail_test = available;

	int grant_flag=1;
	for(int i = 0;i<m;i++)
	{
		if(req_process[i] > need_test[requested_process][i] || req_process[i] > avail_test[i] )
		{
			grant_flag=0;
		}
	}

	if(grant_flag == 0)
	{
		return grant_flag;
	}
	else
	{
		for(int i = 0;i<m;i++)
		{
			alloc_test[requested_process][i] = alloc_test[requested_process][i] + req_process[i];
			need_test[requested_process][i] = need_test[requested_process][i] - req_process[i];
			avail_test[i] = avail_test[i] - req_process[i];
		}
		int safe_flag = safe_seq(n,m,alloc_test,max,avail_test,need_test,finish_flag,result);
		if(safe_flag == 1) //Permenantly update the data
		{
			allocation = alloc_test;
			need = need_test;
			available = avail_test;
		}
		else
		{
			safe_flag = 2; //No safe state
		}
		return safe_flag;
	}
}

void print_need(int n, int r, vector<vector<int>> &need , int max_digits)
{
	cout<<"\nNeed Matrix:\n";
	cout<<"****************\n";
	for(int s = 0; s<max_digits+2 ; s++)
	{
		cout<<" ";
	}
	for(int i = 0; i < r ; i++)
	{
		cout<<char('A'+i);
		for(int s = 0; s<max_digits ; s++)
		{
			cout<<" ";
		}
	}
	cout<<endl;
	for(int i = 0; i < n ; i++)
	{
		cout<<"P"<<i;
		int p_num=i,p_digits=0;
		if(i!=0)
		{
			while(p_num != 0)
			{
				p_num = p_num/10;
				p_digits++;
			}
		}
		else
		{
			p_digits=1;
		}

		for(int s = 0; s<max_digits-p_digits+1 ; s++)
		{
			cout<<" ";
		}
		for(int j = 0; j < r; j++)
		{
			cout<<need[i][j];
			int m_num=need[i][j],m_digits=0;
			if(m_num != 0)
			{
				while(m_num != 0)
				{
					m_num = m_num/10;
					m_digits++;
				}
			}
			else
			{
				m_digits = 1;
			}

			for(int s = 0; s<max_digits-m_digits+1 ; s++)
			{
				cout<<" ";
			}
		}
		cout<<endl;
	}

}

int main()
{
	/**************Taking input from the user****************/
	int n, r;
	cout<<"Please Enter the number of processes:\n";
	cin >> n; //num of processes
	cout<<"Please Enter the number of resources:\n";
	cin >> r; //num of resources

	vector<vector<int>> allocation;
	vector<vector<int>> max;
	vector<int> resources;
	vector<int> available;
	vector<vector<int>> need;
	vector<int> finish_flag(n, 0);
	vector<int> result(n, -1);

	cout<<"\nAllocation Matrix \n";
	cout<<"**********************\n";

	for(int i=0;i<n;i++)
	{
		cout<<"\nEnter P"<<i<<" allocation sequence:\n";
		vector<int> v1;
		for(int j=0;j<r;j++)
		{
			int temp;
			cin >> temp;
			v1.push_back(temp);
		}
		allocation.push_back(v1);
	}

	cout<<"\nMaximum-Matrix \n";
	cout<<"************************\n";

	for(int i=0;i<n;i++)
	{
		cout<<"\nEnter P"<<i<<" max sequence:\n";
		vector<int> v1;
		for(int j=0;j<r;j++)
		{
			int temp;
			cin >> temp;
			v1.push_back(temp);
		}
		max.push_back(v1);
	}

	cout<<"\nAvailable Resources Matrix \n";
	cout<<"*****************************\n";

	cout<<"\nEnter available resources matrix:\n";
	for(int i=0;i<r;i++)
	{

		int temp;
		cin >> temp;
		available.push_back(temp);
	}


				//Fast input for testing
/********************************************************************
	int n = 5; // Number of processes
	int r = 4; // Number of resources
	vector<vector<int>> allocation {{ 0, 0, 1, 2}, // P0
									{ 1, 0, 0, 0}, // P1
									{ 1, 3, 5, 4}, // P2
									{ 0, 6, 3, 2}, // P3
									{ 0, 0, 1, 4}}; // P4

	vector<vector<int>> max   { { 0, 0, 1, 2}, // P0
								{ 1, 7, 5, 0}, // P1
								{ 2, 3, 5, 6}, // P2
								{ 0, 6, 5, 2}, // P3
								{ 0, 6, 5, 6} }; // P4

	vector<int> available { 1, 5, 2, 0 }; // Available Resources

	vector<int> finish_flag(n, 0);
	vector<vector<int>> need;
	vector<int> result(n, -1);
**********************************************************************/


	int max_num=0,max_digits=0;
	for (int i = 0; i < n; i++)
	{
		vector<int> v1;
		for (int j = 0; j < r; j++)
		{
			int temp = max[i][j] - allocation[i][j];
			v1.push_back(temp);
			if(max_num < temp)
			{
				max_num = temp;
			}
		}
		need.push_back(v1);
	}

	if(n-1>max_num)
	{
		max_num = n-1;
	}
	while(max_num != 0)
	{
		max_num=max_num/10;
		max_digits++;
	}

	while(1)
	{
		char input;
		cout<<"\nPress  -  Operation\n";
		cout <<"*******************************************************\n";
		cout<<"   S   -  Safe state check and the safe sequence.  \n";
		cout<<"   I   -  Immediate request by one of the processes.  \n";
		cout<<"   T   -  Terminate the program.  \n \n";

		cin>>input;
		if(input == 'S' || input == 's')
		{
			int safe_flag = safe_seq(n,r,allocation,max,available,need,finish_flag,result);
			print_need(n,r,need,max_digits);
			if(safe_flag == 0)
			{
				cout << "\nNo, System has no safe state." << endl;
				break;
			}
			else
			{
				cout << "\nYes, Safe state <";
				for (int i = 0; i < n; i++)
				{
					cout << "P" << result[i];
					if(i != n-1)
					{
						cout<<",";
					}
				}
				cout<<">."<<endl;
			}
		}
		else if(input == 'I' || input == 'i')
		{
			int requested_process=-1;
			do
			{
				cout<<"\nPlease enter the process number.\n";
				cin>>requested_process;
			}
			while(requested_process >= n || requested_process<0);
			cout<<"\nPlease enter the process request sequence. (Ex: 1 1 0 1 )\n";
			vector<int> req_process;
			for(int i = 0; i < r;i++)
			{
				int temp;
				cin>>temp;
				req_process.push_back(temp);
			}
			int grant_flag = request_grant(n,r,allocation,max,available,need,finish_flag,result,requested_process,req_process);
			print_need(n,r,need,max_digits);

			if(grant_flag == 0 || grant_flag == 2)
			{
				cout<<"\nNo, process request cannot be granted";
				if(grant_flag == 2)
				{
					cout<<" because there is no safe state";
				}
				cout<<".\n";
			}
			else
			{
				cout<<"\nYes, request can be granted with safe state, Safe state <P"<<requested_process<<"req,";
				for (int i = 0; i < n; i++)
				{
					cout << "P" << result[i];
					if(i != n-1)
					{
						cout<<",";
					}
				}
				cout<<">."<<endl;

			}
		}
		else if(input == 'T' || input == 't')
		{
			break;
		}
		else
		{
			cout<<"Wrong Character, Please try again.\n";
		}
	}

	cout<<"\nProgram will terminate...";
	int counter=10000000000;
	while(counter != 0)
	{
		counter--;
	}

	return (0);
}
