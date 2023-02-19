#include <iostream>
#include <cmath>
using namespace std;



struct Point
{
int x;
int y;
    Point()
{
x = 0;
y = 0;
}
Point(int x, int y)
{
this->x = x;
this->y = y;
}

};


struct Node
{
Point position;
    public:
string name;
    Node()
{
name="\0";
}
Node(Point pos,string name)
{
this->position = pos;
this->name = name;
}

};

// The main quadtree class
class Quad
{
// Hold details of the boundary of this node
Point topLeft;
Point botRight;

// Contains details of node
Node *n;

// Children of this tree
Quad *topLeftTree;
Quad *topRightTree;
Quad *botLeftTree;
Quad *botRightTree;

public:
Quad();
Quad(Point topL, Point botR);
void insert(Node*);
Node* search(Point);
bool inBoundary(Point);
};

Quad::Quad()
{
    topLeft = Point(0, 0);
    botRight = Point(0, 0);
    n = NULL;
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
}


Quad::Quad(Point topL, Point botR)
{
    n = NULL;
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    topLeft = topL;
    botRight = botR;
}

// Insert a node into the quadtree
void Quad::insert(Node *node)
{
if (node == NULL)
return;

// Current quad cannot contain it
if (!inBoundary(node->position))
return;

// We are at a quad of unit area
// We cannot subdivide this quad further
if (abs(topLeft.x - botRight.x) <= 1 &&
abs(topLeft.y - botRight.y) <= 1)
{
if (n == NULL)
n = node;
return;
}

if ((topLeft.x + botRight.x) / 2 >= node->position.x)
{
// Indicates topLeftTree
if ((topLeft.y + botRight.y) / 2 >= node->position.y)
{
if (topLeftTree == NULL)
topLeftTree = new Quad(
Point(topLeft.x, topLeft.y),
Point((topLeft.x + botRight.x) / 2,
(topLeft.y + botRight.y) / 2));
topLeftTree->insert(node);
}

// Indicates botLeftTree
else
{
if (botLeftTree == NULL)
botLeftTree = new Quad(
Point(topLeft.x,
(topLeft.y + botRight.y) / 2),
Point((topLeft.x + botRight.x) / 2,
botRight.y));
botLeftTree->insert(node);
}
}
else
{
// Indicates topRightTree
if ((topLeft.y + botRight.y) / 2 >= node->position.y)
{
if (topRightTree == NULL)
topRightTree = new Quad(
Point((topLeft.x + botRight.x) / 2,
topLeft.y),
Point(botRight.x,
(topLeft.y + botRight.y) / 2));
topRightTree->insert(node);
}

// Indicates botRightTree
else
{
if (botRightTree == NULL)
botRightTree = new Quad(
Point((topLeft.x + botRight.x) / 2,
(topLeft.y + botRight.y) / 2),
Point(botRight.x, botRight.y));
botRightTree->insert(node);
}
}
}

// Find a node in a quadtree
Node* Quad::search(Point p)
{
// Current quad cannot contain it
if (!inBoundary(p))
return NULL;

// We are at a quad of unit length
// We cannot subdivide this quad further
if (n != NULL)
return n;

if ((topLeft.x + botRight.x) / 2 >= p.x)
{
// Indicates topLeftTree
if ((topLeft.y + botRight.y) / 2 >= p.y)
{
if (topLeftTree == NULL)
return NULL;
return topLeftTree->search(p);
}

// Indicates botLeftTree
else
{
if (botLeftTree == NULL)
return NULL;
return botLeftTree->search(p);
}
}
else
{
// Indicates topRightTree
if ((topLeft.y + botRight.y) / 2 >= p.y)
{
if (topRightTree == NULL)
return NULL;
return topRightTree->search(p);
}

// Indicates botRightTree
else
{
if (botRightTree == NULL)
return NULL;
return botRightTree->search(p);
}
}
};

// Check if current quadtree contains the point
bool Quad::inBoundary(Point p)
{
return (p.x >= topLeft.x &&
p.x <= botRight.x &&
p.y >= topLeft.y &&
p.y <= botRight.y);
}

void createShops(Quad &);


/*void createShops(Quad&tree)
{

}*/

Node* searchNearby(Point &loc)
{
    if(topLeftTree=NULL && topRightTree=NULL && botLeftTree=NULL && botRightTree=NULL)
    {
        return
    }

    if ((topLeft.x + botRight.x) / 2 >= loc.x)
{
// Indicates topLeftTree
if ((topLeft.y + botRight.y) / 2 >= loc.y)
{
if (topLeftTree == NULL)
return NULL;
return topLeftTree->search(loc);
}

// Indicates botLeftTree
else
{
if (botLeftTree == NULL)
return NULL;
return botLeftTree->search(loc);
}
}
else
{
// Indicates topRightTree
if ((topLeft.y + botRight.y) / 2 >= p.y)
{
if (topRightTree == NULL)
return NULL;
return topRightTree->search(loc);
}

// Indicates botRightTree
else
{
if (botRightTree == NULL)
return NULL;
return botRightTree->search(loc);
}
}
}


// Driver program
int main()
{
Quad tree(Point(0, 0), Point(8, 8));
    int x,y;
    Node a(Point(1, 1), "shop1");
Node b(Point(2, 5), "shop2");
Node c(Point(7, 6), "shop3");
    Node d(Point(1, 6), "shop4");
    Node e(Point(5, 4), "shop5");
    Node f(Point(3, 3), "shop6");
    Node g(Point(7, 2), "shop7");
    Node h(Point(2, 5), "shop8");
tree.insert(&a);
tree.insert(&b);
tree.insert(&c);
    tree.insert(&d);
    tree.insert(&e);
    tree.insert(&f);
    tree.insert(&g);
    tree.insert(&h);
    //createShops(tree);
cout<<"\t\t\t\tHELLO"<<endl;
    cout<<"Enter your location coordinates: ";
    cin>>x>>y;
    //Point loc(x,y);
    cout<<"The coffee shop near you is: "<<tree.search(Point(x,y))->name<<endl;

return 0;
}
