#ifndef UTRIP_H
#define UTRIP_H
#include "Hotel.h"
#include "User.h"
#include "Filter.h"
#include <string>
#include <vector>
#include <map>

#define COMMAND_EXECUTED std::cout << "OK" << std::endl
#define EMPTY_ERROR std::cout << "Empty" << std::endl
const char CSV_DELIM = ',';

const std::string EMAIL_ARG = "email";
const std::string USERNAME_ARG = "username";
const std::string PASS_ARG = "password";
const std::string TYPE_ARG = "type";
const std::string HOTEL_ARG = "hotel";
const std::string QUANTITY_ARG = "quantity";
const std::string CHECKIN_ARG = "check_in";
const std::string CHECKOUT_ARG = "check_out";
const std::string COMMENT_ARG = "comment";
const std::string LOCATION_ARG = "location";
const std::string CLEANLINESS_ARG = "cleanliness";
const std::string STAFF_ARG = "staff";
const std::string FACILITIES_ARG = "facilities";
const std::string VALUE_FOR_MONEY_ARG = "value_for_money";
const std::string OVERALL_ARG = "overall_rating";

enum HOTELS_DATA {
	ID, NAME, STARS, OVERVIEW, AMENITIES,
	CITY, LATITUDE, LONGTITUDE, IMAGE_URL,
	STD_ROOMS_COUNT, DELUXE_ROOMS_COUNT,
	LUX_ROOMS_COUNT, PREM_ROOMS_COUNT,
	STD_ROOMS_PRICE, DELUXE_ROOMS_PRICE,
	LUX_ROOMS_PRICE, PREM_ROOMS_PRICE,
};

typedef struct
{
	std::string hotel_uid, type;
	int quantity, checkin, checkout;
} Reserve_arguments;

class Utrip
{
public:
	Utrip() { signed_in = false; user_logged_in = NULL; }
	~Utrip();
	static std::vector<std::string> split(const std::string &str, char delim);

	void load_hotels(std::string assets_path);
	std::vector<Room*> read_rooms(Rooms_info& info);
	void signup_user(std::map<std::string, std::string> arguments);
	void login_user(std::map<std::string, std::string> arguments);
	void add_comment(std::map<std::string, std::string> arguments);
	void add_rating(std::map<std::string, std::string> arguments);
	void reserve(std::map<std::string, std::string> arguments);
	void logout_user();
	void add_to_wallet(float amount);
	bool user_exists(std::string email, std::string username);
	void show_hotels();
	void show_hotel(std::string id);
	void city_filter(std::string city);
	void stars_filter(int min, int max);
	void price_filter(int min, int max);
	void compound_filter(std::string type, int quantity, int checkin, int checkout);
	void delete_filter();
	void print_reserves();
	void delete_reserve(int uid);
	void show_comments(std::string hotel_uid);
	void show_rating(std::string hotel_uid);
	void show_wallet(int count);
private:
	User* find_user(std::string email);
	void check_signed_in();
	void check_room_type(std::string type);
	void initialize_filtered_hotels();
	void update_filtered_hotels(Filter* filter);
	void intersect_filters();
	std::vector<Hotel*> give_intersection(std::vector<std::vector<Hotel*>> all, int i = 0);
	std::vector<Hotel*> give_intersection(std::vector<Hotel*> v1, std::vector<Hotel*> v2);
	Hotel* find_hotel(std::string uid);
	bool filter_applied(std::string type);
	Reserve_arguments read_reservation_args(std::map<std::string, std::string> arguments);
	bool signed_in;
	std::vector<Hotel> hotels;
	std::vector<Hotel*> filtered_hotels;
	std::map<Filter*, std::vector<Hotel*>> all_filters;
	std::vector<User*> users;
	User* user_logged_in;
};

#endif