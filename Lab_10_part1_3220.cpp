#include <iostream>
#include <cmath> 
using namespace std; 

//Abstract Base Class Conic
 class Conic{
	protected: 
		double x,y;
	public: 
		Conic();
		~Conic();
		virtual void display() = 0; //All functions are virtual in order for the derived classes to have specific functions tailored towards preferred functionality
		virtual double area() =0;
		virtual void Move()=0;
		virtual void Reshape() = 0;
};
void Move(){
	
Conic::~Conic(){
	cout<<"\n*****************Conic Deleted******************"<<endl;
}
Conic::Conic(){
	cout<<"\n******************Conic Created******************";
	cout<<"\nEnter Center X-coordinate: ";
	cin>>x; 
	cout<<"\nEnter Center Y-coordinate: ";
	cin>>y; 
}

//Derived Class Ellipse	
class Ellipse:public Conic{
	private: 
		double semimajor,semiminor,ang,A;//private members declared when Ellipse is created
	public:
		Ellipse();
		void Reshape();
		void Move(){cout<<"\n===============Moving Ellipse======================\nEnter New Center X-coordinate: "; cin>>x;cout<<"\nEnter New Center Y-coordinate: "; cin>>y; cout<<"\nEllipse moved to "<<x<<","<<y<<endl;vertices();}
		void Rotate(){cout<<"Enter new angle of orientation: "; cin>>ang; }
		double area(){A = 3.14159 * semimajor * semiminor;}
		void vertices();
		void display(){cout<<"\n================Ellipse Paramters================\nSemi-minor: "<<semiminor<<"\nSemi-major: "<<semimajor<<"\nOrientation Angle: "<<ang<<"\nSurface Area: "<<A<<"\nCentered at "<<x<<","<<y<<endl;vertices();}
};

void Ellipse::Reshape(){
	
	cout<<"\nEnter New Semi-major: ";
	cin>>semimajor; 
	cout<<"\nEnter New Semi-minor: ";
	cin>>semiminor; 
	area();
}
			

void Ellipse::vertices(){
	cout<<"Major Vertices = (x + acos(angle),y + acos(angle)) = ("<<x+semimajor*cos(ang)<<","<<y+semimajor*cos(ang)<<")"<<endl;
	cout<<"Minor Vertices = (x + bcos(angle),y + bcos(angle)) = ("<<x + semiminor*cos(ang)<<","<<y + semiminor * cos(ang)<<")\n"<<endl;
}

//Ellipse constructor 
Ellipse::Ellipse(){
	cout<<"\n******************Ellipse Created*********************";
	cout<<"\nEnter Semi-minor axis: ";
	cin>>semiminor;
	cout<<"\nEnter Semi-major axis: ";
	cin>>semimajor;
	cout<<"\nEnter angle of orientation: ";
	cin>>ang;
	area();
	
}

//Second derived class Circle
class Circle: public Conic{
	private: 
		double r,A;//private member declared only when a circle is created
	public: 
		Circle();
		void display(){cout<<"\n==============Circle Parameters==========="<<"\nRadius: "<<r<<"m"<<"\nArea: "<<A<<" m^2"<<"\nCentered at (" <<x<<","<<y<<")"<<endl;}
		void Move(){cout<<"\n===================Moving Circle===================\nEnter New Center X-coordinate: "; cin>>x;cout<<"\nEnter New Center Y-coordinate: "; cin>>y; cout<<"\nCircle moved to "<<x<<","<<y<<endl;}
		double area(){ A= 3.14159 * r * r;}
		void inside_circle();
		void Reshape(); 
};
//Reshape function allows the user to reshape the size of the circle or ellipse created
void Circle::Reshape(){
	cout<<"\n==============Reshaping Circle================"<<endl;
	cout<<"\nEnter New Radius: ";
	cin>>r; 
	area();
}
//Function allows us to see if a specified point is either inside, on a the border, or outside of the created circle
void Circle::inside_circle(){
	cout<<"\n================Inside Circle Function=================="<<endl;
	double nx,ny,d;
	cout<<"\nEnter the x coordinate you would like to find: ";
	cin>>nx; 
	cout<<"\nEnter the y coordinate you would like to find: ";
	cin>>ny; 
	d = sqrt(pow((x-nx),2) + pow((y-ny),2)); //distance formula
	if(d < r){
		cout<<"\nPoint is inside of circle!"<<endl;
	}else if(d == r){
		cout<<"\nPoint lies on the circle!"<<endl;
	}else{
		cout<<"\nPoint lies outside of circle!"<<endl;
	}
}
//Circle constructor 
 Circle::Circle(){
	 cout<<"\n********************Circle Created***********************"<<endl;
	 cout<<"\nEnter Radius: ";
	 cin>>r;
	 area();
}

 int main(){
	Conic a;
	
	//Creating Circle through the base class Conic
	Conic *c = new Circle(); 
	c->display(); 
	c->Move(); 
	c->Reshape();
	c->display();
	delete c; //Calling Conic destructor to delete the object pointer
	
	//Creating Ellipse through the base class Conic
	Conic *e = new Ellipse(); 
	e->display();
	e->Move();
	e->Reshape();
	e->display(); 
	delete e;//Calling Conic destructor to delete the object pointer
	
	//Creating Circle by calling the derived class object
	Circle b; 
	b.display(); 
	b.Move();
	b.Reshape();
	b.display();
	b.inside_circle();
	
	//Creating Ellipse by calling the derived class object 
	Ellipse E;
	E.display();
	E.Move();
	E.Reshape();
	E.display();
	E.Rotate();
	E.display();
	return 0;
}
		