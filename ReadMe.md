# Advanced Programming - Assignment #7 - Phase #1 - Spring 2020
## University of Tehran
### UTRIP

This project summarizes what we have learned in the Advanced Programming course. Finally, we have to design a hotel reservation website that will have features such as hotel reservations and getting comments, and points from users.

In the first phase of this project, we will implement the logic of this site, which can be used using the command line interface. The process of using the program is such that the user enters a command using the command line interface with the necessary arguments to execute it, in the standard input. For example, to display the information of a specific hotel, enter the command `GET hotels` and after the command, enter the `id` of the hotel that you want to get its information.

Another point in the commands is that before entering the command, enter the phrase `GET` and `POST`, so that the commands are somehow separated. In this way, the commands that are more for receiving information from the system use `GET` and the commands that are more for sending information to the system use `POST`.

### How to Run:

```
./utrip.out <csvFile_relative_address>
```

### Commands:
* Authentication:
  * Sign Up:
    ```
    POST signup ? email <email> username <username> password <password>
    ```
  * Login:
    ```
    POST login ? email <email> password <password>
    ```
  * Logout:
    ```
    POST logout
    ```
* Increase wallet credit:
    ```
    POST wallet ? amount <amount>
    ```
* Get some recent transactions:
    ```
    GET wallet ? count <count>
    ```
* Get hotels information:
    ```
    input: GET hotels
    output: <unique_id> <name> <star_rating> <city> <total_num_of_rooms> <average_price> | Empty | Permission Denied
    ```
* Get information of a hotel:
    ```
    GET hotels ? id <id>
    ```
* Adding Filters:
  * City filter:
    ```
    POST filters ? city <city>
    ```
  * Stars filter:
    ```
    POST filters ? min_star <min_star> max_star <max_star>
    ```
  * Price filter:
    ```
    POST filters ? min_price <min_price> max_price <max_price>
    ```
  * Room type-count & Date-Time filter:
    ```
    POST filters ? type <room_type> quantity <quantity> check_in <check_in> check_out <check_out>
    ```
    ```
    example: POST filters ? type premium quantity 2 check_in 21 check_out 26
    ```
  * Delete all filters:
    ```
    DELETE filters
    ```
* Reserve rooms:
    ```
    POST reserves ? hotel <hotel_id> type <room_type> quantity  <quantity> check_in <check_in> check_out <check_out>
    ```
* Get all reservations of a user:
    ```
    GET reserves
    ```
* Cancel a reservation:
    ```
    DELETE reserves ? id <reservation_id>
    ```
* Add comment to hotel:
    ```
    POST comments ? hotel <hotel_id> comment <comment>
    ```
* Add rating to hotel:
    ```
    POST ratings ? hotel <hotel> location <location> cleanliness  <cleanliness> staff <staff> facilities <facilities> value_for_money <Value_for_money> overall_rating <overall_rating>
    ```
    ```
    example: POST ratings ? hotel ba7b9e7b9073e745d38122d74045be00 location 3.22 cleanliness 4.2 staff 5 facilities 5 value_for_money 1 overall_rating 4.77
    ```
* Get comments of a hotel:
    ```
    GET comments ? hotel <hotel_id>
    ```
* Get **average** rating of a hotel:
    ```
    GET ratings ? hotel <hotel_id>
    ```

