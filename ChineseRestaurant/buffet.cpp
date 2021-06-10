#include "buffet.h"


Buffet::Buffet(int b_seats) :kTotalSeats_(b_seats)
{
	this->empty_seats_ = this->kTotalSeats_;
}

Buffet::~Buffet()
{
}

void Buffet::TakeSeats(int take_sts)
{
	empty_seats_ -= take_sts;
}

void Buffet::FreeSeats(int free_sts)
{
	empty_seats_ += free_sts;
}

bool Buffet::IsFreeEnough(int ppl_in_grp)
{
	return(empty_seats_ >= ppl_in_grp);
}