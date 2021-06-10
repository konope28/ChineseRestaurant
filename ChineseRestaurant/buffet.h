#ifndef MODEL_BUFFET_H_
#define MODEL_BUFFET_H_

class CustomerGroup;

class Buffet
{
public:
	Buffet(int b_seats);
	~Buffet();
	void TakeSeats(int take_sts);
	void FreeSeats(int free_sts);
	bool IsFreeEnough(int ppl_in_grp);

private:
	int const kTotalSeats_;
	int empty_seats_;
};

#endif /*MODEL_BUFFET_H_*/