#ifndef HOTELS_H
#define HOTELS_H
#include "Rooms.h"
#include <vector>
#include <string>

#define NO_RATING "No Rating"

typedef struct Rating
{
	float location, cleanliness, staff, facilities, value_for_money, overall;
	User* user;
	Rating(float _location, float _cleanliness, float _staff, float _facilities, float v_for_money, float _overall, User* _user = NULL)
	{
		if (_location < 1 || _cleanliness < 1 || _staff < 1 || _facilities < 1 || v_for_money < 1 || _overall < 1
			|| _location > 5 || _cleanliness > 5 || _staff > 5 || _facilities > 5 || v_for_money > 5 || _overall > 5)
			throw Bad_request();
		location = _location; cleanliness = _cleanliness; staff = _staff; user = _user;
		facilities = _facilities; value_for_money = v_for_money; overall = _overall;
	}
	inline User* get_user() { return user; }
} Rating;

typedef std::string comment;
typedef std::string user_name;

class Hotel
{
public:
	Hotel(std::string _uid, std::string _name, int _stars, std::string _review,
		std::string _amenities, std::string _city, float _latitude, float _longtitude,
		std::string _image_url, Rooms_info _rooms_info, std::vector<Room*> _rooms);
	~Hotel();

	static inline bool uid_sort(Hotel*& h1, Hotel*& h2) { return h1->uid < h2->uid; }
	static int count_non_zero_rooms(Rooms_info rooms_info);

	inline std::string get_uid() { return uid; }
	inline std::string get_name() { return name; }
	inline std::string get_city() { return city; }
	inline int get_stars() { return stars; }
	inline double get_avg_price() { return average_price; }
	std::vector<Room*> get_room_by_type(std::string type);
	std::vector<Room*> find_available_rooms(int quantity, std::string type, const Reservation_date& rdate);
	void print_complete();
	void print();
	void clear();
	void add_comment(std::string user_name, std::string comment);
	void show_comments();
	void show_rating();
	void add_rating(Rating* rating);
private:
	std::string uid;
	std::string name;
	int stars;
	std::string review;
	std::string amenities;
	std::string city;
	float latitude;
	float longtitude;
	std::string image_url;	
	Rooms_info rooms_info;
	int total_rooms;
	int non_zero_rooms;
	double total_price;
	double average_price;
	std::vector<Room*> rooms;
	std::vector<Rating*> ratings;
	std::vector<std::pair<user_name, comment>> comments;
	Rating calculate_average_rating();
};

#endif