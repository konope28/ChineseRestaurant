#ifndef MODEL_TABLE_H_
#define MODEL_TABLE_H_
#include <iostream>

class CustomerGroup;

class Table
{
public:
	Table(int t_seats);
	~Table();
	int GetSize() const;
	bool IsEmpty();
	void AssignCustomers(CustomerGroup* c);
	void RemoveCustomers();

private:
	const int kSize_;
	CustomerGroup* served_group_;
};

#endif /*MODEL_TABLE_H_*/
