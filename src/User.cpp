#include "User.h"
#include "Reservation.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void User::add_reservation(Reservation* reservation)
{
	float price = (float)reservation->get_price();
	wallet.push_back(-1 * price);
	reservations.push_back(reservation);
	reservation_uids++;
	reservation->print_success();
}

void User::print_reservations()
{
	if (reservations.empty())
		cout << EMPTY_MESSAGE << endl;
	else
		for (int i = reservations.size() - 1; i >= 0; i--)
			reservations[i]->print();
}

float User::all_money()
{
	float sum = 0;
	for (float transaction : wallet)
		sum += transaction;
	return sum;
}

bool User::has_money(int amount)
{
	return amount <= all_money();
}

void User::delete_reserve(int uid)
{
	vector<Reservation*> updated;
	for (Reservation*& reserve : reservations)
		if (reserve->get_uid() != uid)
			updated.push_back(reserve);
		else
		{
			wallet.push_back(float(reserve->get_price()) / 2);
			reserve->clean();
			delete reserve;
		}
	if (reservations.size() == updated.size())
		throw Not_found();
	else
		reservations = updated;
}

User::~User()
{
	for(Reservation*& reserve : reservations)
		delete reserve;
}

void User::show_wallet(int count)
{
	for (int i = 0; i < count; i++)
	{
		float stage_money = calculate_money(i);
		if (stage_money == -1)
		{
			cout << 0 << endl;
			break;
		}
		cout << int(round(stage_money)) << endl;
	}
}

float User::calculate_money(int stage)
{
	int wallet_size = wallet.size();
	if (stage >= wallet_size)
		return -1;
	float sum = 0;
	for (int i = 0; i < wallet_size - stage; i++)
		sum += wallet[i];
	return sum;
}