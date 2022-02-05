#include "Interface.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

void Interface::handle_command(string cmd)
{
	if (cmd == EMPTY_LINE)
		throw Bad_request();

	stringstream buffer(cmd);
	string command;
	buffer >> command;

	if (command == POST_CMD)
		handle_post_command(buffer);

	else if (command == GET_CMD)
		handle_get_command(buffer);

	else if (command == DELETE_CMD)
		handle_delete_command(buffer);

	else
		throw Bad_request();
}

void Interface::handle_post_command(stringstream& buffer)
{
	string type;
	buffer >> type;
	if (type == LOGOUT_CMD)
	{
		utrip->logout_user();
		return;
	}

	check_argument_delim(buffer);
	if (type == SIGNUP_CMD)
	{
		auto signup_arguments = split_args(buffer);
		utrip->signup_user(signup_arguments);
	}
	else if (type == LOGIN_CMD)
	{
		auto login_arguments = split_args(buffer);
		utrip->login_user(login_arguments);
	}
	else if (type == RESERVE_CMD)
	{
		auto reserve_args = split_args(buffer);
		utrip->reserve(reserve_args);
	}
	else if (type == COMMENT_CMD)
	{
		auto args = split_args(buffer);
		utrip->add_comment(args);
	}
	else if (type == RATING_CMD)
	{
		auto args = split_args(buffer);
		utrip->add_rating(args);
	}
	else if (type == WALLET_CMD)
	{
		float amount;
		string arg;
		buffer >> arg >> amount;
		if (arg == AMOUNT_ARG)
			utrip->add_to_wallet(amount);
		else
			throw Bad_request();
	}
	else if (type == FILTER_CMD)
		get_filters(buffer);
	else
		throw Bad_request();
}

void Interface::handle_get_command(stringstream& buffer)
{
	string type;
	buffer >> type;

	if (type == HOTELS_CMD)
		handle_hotel_cmd(buffer);

	else if (type == RESERVE_CMD)
		utrip->print_reserves();

	else if (type == COMMENT_CMD)
	{
		check_argument_delim(buffer);
		utrip->show_comments(get_hotel_uid(buffer));
	}
	else if (type == RATING_CMD)
	{
		check_argument_delim(buffer);
		utrip->show_rating(get_hotel_uid(buffer));
	}
	else if (type == WALLET_CMD)
	{
		int count;
		string arg;
		check_argument_delim(buffer);
		buffer >> arg >> count;
		if (arg == COUNT_ARG)
			utrip->show_wallet(count);
		else
			throw Bad_request();
	}
	else
		throw Bad_request();
}

void Interface::handle_delete_command(stringstream& buffer)
{
	string type;
	buffer >> type;

	if (type == FILTER_CMD)
		utrip->delete_filter();

	else if (type == RESERVE_CMD)
	{
		check_argument_delim(buffer);
		int reserve_uid;
		string arg;
		buffer >> arg >> reserve_uid;
		if (arg == ID_ARG)
			utrip->delete_reserve(reserve_uid);
		else
			throw Bad_request();
	}
	else
		throw Bad_request();
}

void Interface::handle_hotel_cmd(stringstream& buffer)
{
	string arg, uid;
	int count = count_words(buffer.str());
	if (count == 2)
		utrip->show_hotels();
	else if (count == 5)
	{
		check_argument_delim(buffer);
		buffer >> arg >> uid;
		if (arg == ID_ARG)
			utrip->show_hotel(uid);
		else
			throw Bad_request();
	}
	else
		throw Bad_request();
}

int Interface::count_words(string buffer)
{
	stringstream s(buffer);
	string word;
	int count = 0;
	while (s >> word)
		count++;
	return count;
}

void Interface::get_filters(stringstream& buffer)
{
	string key, value;
	buffer >> key;
	if (key == CITY_FILTER)
	{
		while (buffer.peek() == ' ')
			buffer.ignore();
		getline(buffer, value);
		utrip->city_filter(value);
	}
	else
	{
		get_filter_args(key, buffer);
	}
}

map<string, string> Interface::split_args(stringstream& buffer)
{
	map<string, string> splitted;
	string key, value;
	while (buffer >> key >> value)
		splitted[key] = value;
	return splitted;
}

void Interface::check_hotel_args(string buffer)
{
	stringstream s(buffer);
	char args_delim;
	string id;
	s >> args_delim >> id;
	if (args_delim != ARGUMENT_DELIM || id != ID_ARG)
		throw Bad_request();
}

void Interface::check_argument_delim(stringstream& buffer)
{
	char c;
	buffer >> c;
	if (c != '?')
		throw Bad_request();
}

string Interface::get_hotel_uid(stringstream& buffer)
{
	string command, hotel_uid;
	buffer >> command >> hotel_uid;
	if (command != HOTEL_ARG)
		throw Bad_request();
	return hotel_uid;
}

void Interface::get_filter_args(string key, stringstream& buffer)
{
	string value;
	try
	{
		buffer >> value;
		map<string, string> args = split_args(buffer);
		args[key] = value;
		if (key == MIN_STAR_FILTER || key == MAX_STAR_FILTER)
		{

			int min = stoi(args.at(MIN_STAR_FILTER));
			int max = stoi(args.at(MAX_STAR_FILTER));
			utrip->stars_filter(min, max);
		}
		else if (key == MIN_PRICE_FILTER || key == MAX_PRICE_FILTER)
		{
			int min = stoi(args.at(MIN_PRICE_FILTER));
			int max = stoi(args.at(MAX_PRICE_FILTER));
			utrip->price_filter(min, max);
		}
		else if (key == TYPE_ARG || key == QUANTITY_ARG || key == CHECKIN_ARG || key == CHECKOUT_ARG)
		{
			string type = args.at(TYPE_ARG);
			int quantity = stoi(args.at(QUANTITY_ARG));
			int checkin = stoi(args.at(CHECKIN_ARG));
			int checkout = stoi(args.at(CHECKOUT_ARG));
			utrip->compound_filter(type, quantity, checkin, checkout);
		}
		else
			throw Bad_request();
	}
	catch (const out_of_range&)
	{
		throw Bad_request();
	}
}