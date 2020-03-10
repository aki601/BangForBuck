#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#define INF 99999
using namespace std;
int source=0;
double initial_amt=0;
struct Edge {
	int u;
	int v;
	double w;
};
int c=0;
double max1=1.0;
double w[5][5]={{1,0.741,0.657,1.061,1.011},{1.35,1,0.889,1.433,1.366},{1.521,1.126,1,1.614,1.538},{0.943,0.698,0.62,1,0.953},{0.955,0.732,0.65,1.049,1}};
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
double calculateProfit(char a[])
{
    double profitRate=1;
    int i=0,j=1,k=0,l=0;
    while(a[i]!='\0') {
        k=int(a[i])-48;
        l=int(a[i+1])-48;
        profitRate*=w[l][k];
        i++;
        if(i==4) {
            k=int(a[4])-48;
            l=int(a[0])-48;
            profitRate*=w[k][l];
            if(profitRate >= 1.0)
                return profitRate;
            else
                return 0;
        }
    }
}
void findLargest(char *a, int l, int r)
{
   int i;
   double profit=1.0;
   if (l == r && a[0] == (48+source))
     {
         profit=calculateProfit(a);
         if(profit !=0)
         {
            cout << a[0]-47 <<"->" <<a[1]-47 <<"->" << a[2]-47 <<"->" <<a[3]-47 <<"->" <<a[4]-47 <<"    ";
            cout << profit*initial_amt <<"\n\n";
            if(profit*initial_amt > max1)
                max1=profit*initial_amt;
         }
     }
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          findLargest(a, l+1, r);
          swap((a+l), (a+i));
       }
   }
}
struct Graph {
	int V;
	int E;
	struct Edge *edge;
};
void bellmanford(struct Graph *g, int source);
void display(double arr[], int size);
int main() {
    int choice;
    char currs[6]={'0','1','2','3','4','\0'};
    char currencies[5][5]={{"USD\0"},{"EUR\0"},
                            {"GBP\0"},{"CHF\0"},
                                {"CAD\0"}};
    cout << "\t\t\t\t\tFOREX TRADER\n";
    cout <<"\n\n";
        cout << "The available currencies are:\n";
    for(int i=0;i<5;i++)
        cout << currencies[i] <<"\n";
    cout << "\nThe currency conversion rates are: \n";
    struct Graph *g = new Graph;
	g->V = 5;
    g->E = 20;
    g->edge = new Edge[(g->E) * sizeof(struct Edge)];
	ifstream myfile;
    double val;
    myfile.open("example.txt");
    int i=0,j=0,k=0;
    while(! myfile.eof())
    {
        myfile >> val;
        if (j == 5)
          {
            i++;
            j=0;
          }
        if(val != 1)
        {
        g->edge[k].u=i;
        g->edge[k].v=j;
        g->edge[k].w=-log(val);
        k++;
        }
        j++;

    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
            cout << w[i][j] <<" ";
        cout << endl;
    }
    cout << "\nEnter the start currency\n";
    cout << "1. USD 2. EUR 3. GBP 4. CHF 5. CAD\n";
    cin >>choice;
    source=choice-1;
    cout << "Enter your initial amount\t";
    cin >> initial_amt;
    int u1, v1;
	double w1;

	int tV = g->V;

	int tE = g->E;

	double d[tV];

	double p[tV];

	for (i = 0; i < tV; i++) {
		d[i] = INF;
	}
	d[source] = 0;
    cout << "\n";
    for(i = 1; i <= tV; i++) {
		for(j = 0; j < tE; j++) {
			u1 = g->edge[j].u;
			v1 = g->edge[j].v;
			w1 = g->edge[j].w;
            if(d[u1] != INF && d[v1] > d[u1] + w1) {
				d[v1] = d[u1] + w1;
				p[v1] = u1;
			}
		}
	}
	bool flag=0;
	for(i = 0; i < tE; i++) {
		u1 = g->edge[i].u;
		v1 = g->edge[i].v;
		w1 = g->edge[i].w;
		if(d[v1] > d[u1] + w1) {
			cout << "Negative weight cycle detected!\n" ;
			flag=1;
			findLargest(currs,0,strlen(currs)-1);
			break;
		}
	}
	if(flag == 0)
        cout << "No arbitrage possible\n";
    cout << "The maximum profit obtained is: " << max1 <<"\n";
	cout << "\n";
	return 0;
}
