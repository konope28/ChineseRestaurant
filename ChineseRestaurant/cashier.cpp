#include "cashier.h"
#include "customer_group.h"


Cashier::Cashier() : served_group_(nullptr)
{
}

Cashier::~Cashier()
{
	if (served_group_ != nullptr)
	{
		delete served_group_;
	}
}

bool Cashier::IsFree()
{
	return(served_group_ == nullptr);
}

void Cashier::AssignCustomers(CustomerGroup* c)
{
	served_group_ = c;
}

void Cashier::RemoveCustomers()
{
	served_group_ = nullptr;
}