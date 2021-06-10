#ifndef MODEL_CASHIER_H_
#define MODEL_CASHIER_H_

class CustomerGroup;

class Cashier
{
public:
	Cashier();
	~Cashier();
	bool IsFree();
	void AssignCustomers(CustomerGroup* c);
	void RemoveCustomers();
private:
	CustomerGroup* served_group_;
};

#endif /*MODEL_CASHIER_H_*/
