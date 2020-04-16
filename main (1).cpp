#include <iostream>
using namespace std;

//created with love from atom

void test()
{


  //First let's create an empty network;
  Network x;
  //Now create a new network by reading the text file
  string name = "test1.txt";
  Network y(name); //this should configure the network equal to test file
  cout<<y; //confirm that the network is correctly read

  x = y; //assignment operator

  Network z = x+y; //+ will called and then the copy constructor
  cout<<z;
  //testing the intersection from now on
  Network a = x*y;
  cout<<a;

  //testing the unary operator - now
  /*
    Let's say a is following :
    0:1->Null
    1:0->2->Null;
    2:1->Null;

    a- will result in following

    0:2->Null
    1:Null;
    2:0->Null;


  */
  a = -a;
  cout<<a;
  //adding a new computer now
  /*
  Example of a++;
  let's say a is following:
             0:1->2->Null
             1:0->Null
             2:0->Null
             now i call a++;
             The result is following
             0:1->2->Null
             1:0->Null
             2:0->Null
             3:Null //3 is added now
  */
  a++;

  //testing the intersection operator now
  Network b("test2.txt");
  Network c = a-b;

  bool res = c.subNetwork(a);
  cout<<"The result is:"<<res<<endl;

  c.addConnection(1,2); //it may or may not exist lol
  c.addConnection(8,9);//for hard coders this will not work

  vector<int> neighbors = c.getNeighbors(5);
  for(int i=0;i<neighbors.size();i++)
  {
    cout<<neighbors[i]<<endl;
  }
  //what will you do if a neighbour does not exist
  neighbors = c.getNeighbors(100);
  for(int i=0;i<neighbors.size();i++)
  {
    cout<<neighbors[i]<<endl;
  }

  neighbors = c.getNeighborsOfNeighbors(5);
  for(int i=0;i<neighbors.size();i++)
  {
    cout<<neighbors[i]<<endl;
  }
  neighbors = c.getNeighborsOfNeighbors(1000);


  //change them to see if your code is robust or not
  int aa = 2;
  int bb = 3;
  if(a[aa][bb])
  {
    cout<<aa<<"and "<<bb<<"are connected "<<endl;
  }
//creating a local scope to check for destructor;
  {
    Network zz("test3.txt");
    cout<<zz<<endl;
  }
}
int main()
{
  test1();
}
