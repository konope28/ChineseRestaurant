#include "table.h"
#include "customer_group.h"
using namespace std;

Table::Table(int t_seats) : served_group_(nullptr), kSize_(t_seats)
{
}

Table::~Table()
{
	if (served_group_ != nullptr)
	{
		delete served_group_;
	}
}

int Table::GetSize() const
{
	return kSize_;
}

bool Table::IsEmpty()
{
	return(served_group_ == nullptr);
}

void Table::AssignCustomers(CustomerGroup* c)
{
	served_group_ = c;
}

void Table::RemoveCustomers()
{
	served_group_ = nullptr;
}