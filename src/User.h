#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#define EMPTY_MESSAGE "Empty"

class Reservation;

class User
{
public:
	User(std::string _username, std::string _email, std::string _password)
	{
		username = _username; email = _email; password = _password;
		reservation_uids = 1;
	}
	~User();
	inline std::string get_email() { return email; }
	inline std::string get_username() { return username; }
	inline bool is_password_true(std::string pass) { return password == pass; }
	inline int get_reservation_uid() { return reservation_uids; }
	void add_to_wallet(float amount) { wallet.push_back(amount); }
	void print_reservations();
	bool has_money(int amount);
	void add_reservation(Reservation* reservation);
	void delete_reserve(int uid);
	void show_wallet(int count);
private:
	std::string username;
	std::string email;
	std::string password;
	std::vector<float> wallet;
	std::vector<Reservation*> reservations;
	float all_money();
	float calculate_money(int stage);
	int reservation_uids;
};

#endif