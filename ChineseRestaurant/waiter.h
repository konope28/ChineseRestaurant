#ifndef MODEL_WAITER_H_
#define MODEL_WAITER_H_

class CustomerGroup;
class Agenda;
class Logger;
struct ChineseRestaurant;

class Waiter : public Process
{
public:
	Waiter(ChineseRestaurant* r, Agenda* a,int id);
	~Waiter();
	bool IsFree();
	bool IsTerminated() { return false; };
	void Execute(double current_time);

private:
	enum State
	{
		StartOfService,
		EndOfService
	};
	const int kWaiterID_;

	State state_;
	CustomerGroup* served_group_;
	ChineseRestaurant* restaurant_;
	Logger* logger_;
	bool terminated_;
};

#endif /*MODEL_WAITER_H_*/
