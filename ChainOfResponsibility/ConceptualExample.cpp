// ===========================================================================
// ConceptualExample.cpp // Chain of Responsibility
// ===========================================================================

#include <iostream>
#include <string>
#include <memory>
#include <array>

// using namespace std;

class Handler
{
protected:
	Handler* successor;

public:
	virtual ~Handler()		{ }
	virtual void handleRequest(int r) = 0;
	void setSuccessor(Handler* s){ successor = s; }
};

class ConcreteHandler1 : public Handler
{
public:
	void handleRequest(int r)	
	{ 
		if (r >= 0 && r < 10)
			std::cout << "ConcreteHandler1 bearbeitet: " << r << std::endl;
		else if(successor)
			successor->handleRequest(r);
	}
};

class ConcreteHandler2 : public Handler
{
public:
	void handleRequest(int r)	
	{ 
		if(r >= 10 && r < 20)
			std::cout << "ConcreteHandler2 bearbeitet: " << r << std::endl;
		else if(successor)
			successor->handleRequest(r);
	}
};

class ConcreteHandler3 : public Handler
{
public:
	void handleRequest(int r)	
	{ 
		if(r >= 20 && r < 30)
			std::cout << "ConcreteHandler3 bearbeitet: " << r << std::endl;
		else if(successor)
			successor->handleRequest(r);
	}
};

class Request
{
public:
	Request(int rt, std::string rp) : requestType(rt), requestParam(rp)	{ }
private:
	int requestType;
	std::string requestParam;
};

void test_conceptual_example() {

	Handler* h1 = new ConcreteHandler1();
	Handler* h2 = new ConcreteHandler2();
	Handler* h3 = new ConcreteHandler3();
	h1->setSuccessor(h2);
	h2->setSuccessor(h3);

	int requests[] = { 7, 25, 17, 21, 18, 3, 19, 20 };
	for(unsigned i = 0; i < sizeof(requests)/sizeof(int); ++i)
		h1->handleRequest(requests[i]);
}

// ===========================================================================
// End-of-File
// ===========================================================================
