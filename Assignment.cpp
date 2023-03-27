// Space Travel System
#include <bits/stdc++.h>
using namespace std;

// creating data structure for date
struct Date
{
    int day;
    int month;
    int year;
};

// creating class for traveller
class Traveller
{
    string traveller_id;

public:
    string name;
    string ID;
    string list_of_tickets;

    void getName()
    {
        cout << name << endl;
    }
    void getId()
    {
        cout << ID << endl;
    }

    void setTravellerId(string id)
    {
        traveller_id = id;
    }
};
vector<Traveller> traveller_vector;

class Astronaut : public Traveller
{
    int experience;

public:
    string licenseID;
    string list_of_astronauts;
    static int astronaut_count;

    void setExperience(int experience)
    {
        this->experience = experience;
    }
};
int Astronaut::astronaut_count = 0;
vector<Astronaut> astronaut_vector;

class Passenger : public Traveller
{
    int validity;

public:
    static int passenger_count;
    void setValidity(int validity)
    {
        this->validity = validity;
    }
    int getValidity()
    {
        return validity;
    }
};
int Passenger::passenger_count = 0;

class Commander : public Traveller
{
    string authority;
    int experience;

public:
    string licenseID;
    string list_of_commanders;
    static int commander_count;
    void setExperience(int experience)
    {
        this->experience = experience;
    }
};
int Commander::commander_count = 0;
vector<Commander> commander_vector;

class Ticket : public Passenger, public Astronaut, public Commander
{
    int price;

public:
    string source_station;
    string destination_station;
    Date date;
    string traveller_name;
    string traveller_id;
    static int ticket_count;

    void bookTicket() {}
    void cancelTicket() {}
    void setPrice(int price)
    {
        this->price = price;
    }
    int getPrice()
    {
        return price;
    }

    // declaring constructor
    Ticket()
    {
        ticket_count++;
    }
    // declaring destructor
    ~Ticket()
    {
        ticket_count--;
        // cout << "Ticket cancelled succesfully!" << endl;
    }
};
int Ticket::ticket_count = 0;

class Planet
{
public:
    int position_x;
    int position_y;
    int position_z;
    string name;
    static int planet_count;

    void getCoordinates() {}

    // declaring constructor
    Planet()
    {
        planet_count++;
    }
};
int Planet::planet_count = 0;

// creating class for travel
class Space_Travel
{
public:
    // list of travellers
    string travel_ID;
    Date date;
    string source;
    string destination;

    vector<Traveller> ST_traveller_vector;
    vector<Astronaut> ST_astronaut_vector;
    vector<Commander> ST_commander_vector;
};
vector<Space_Travel> ST_vector;

//function to calculate price of ticket
int calculatePrice(Date date)
{
    Date today;
    today.day = 21;
    today.month = 3;
    today.year = 2023;

    // Calculating the difference between the two dates
    int day_diff = date.day - today.day;
    int month_diff = date.month - today.month;
    int year_diff = date.year - today.year;
    // difference in days
    int days = day_diff + month_diff * 30 + year_diff * 365;
    // calculating the price
    int k = 10 * 365 * 1000; // arbitrary value
    int price = k / (days + 1);
    return price;
}

// checking if the two passengers are travelling on same date and creating Space_Travel object
void check_space_travel(Ticket ticket)
{
    // checking if any existing space travel is on same date and same source and destination
    int found = 0;
    Space_Travel space_travel;
    for (int i = 0; i < ST_vector.size(); i++)
    {
        if (ST_vector[i].date.day == ticket.date.day && ST_vector[i].date.month == ticket.date.month && ST_vector[i].date.year == ticket.date.year && ST_vector[i].source == ticket.source_station && ST_vector[i].destination == ticket.destination_station)
        {
            found = 1;
            space_travel = ST_vector[i];
            // finding the traveller with same id
            Traveller traveller;
            for (int j = 0; j < traveller_vector.size(); j++)
            {
                if (traveller_vector[j].ID == ticket.traveller_id)
                {
                    traveller = traveller_vector[j];
                    break;
                }
            }
            // adding traveller to the space travel
            ST_vector[i].ST_traveller_vector.push_back(traveller);
            // cout << "Passenger " << ticket.traveller_name << " added to Space Travel " << ST_vector[i].travel_ID << endl;
            cout << "Hurray!! you are not alone! Another passenger(s) also booked same ticket like you, so you will be travelling with him/her." << endl;
            cout << "Space Travel is created for all you guys." << endl;
            found = 1;
            return;
        }
    }
    // if no space travel is found on same date and same source and destination
    if (found == 0)
    {
        // creating a new space travel
        Space_Travel space_travel;
        space_travel.date = ticket.date;
        space_travel.source = ticket.source_station;
        space_travel.destination = ticket.destination_station;
        // finding the traveller with same id
        Traveller traveller;
        for (int j = 0; j < traveller_vector.size(); j++)
        {
            if (traveller_vector[j].ID == ticket.traveller_id)
            {
                traveller = traveller_vector[j];
                break;
            }
        }
        // adding traveller to the space travel
        space_travel.ST_traveller_vector.push_back(traveller);
        // cout << "Passenger " << ticket.traveller_name << " added to Space Travel " << space_travel.travel_ID << endl;
        ST_vector.push_back(space_travel);
        // assigning the first astronaut to the space travel
        Astronaut astronaut = astronaut_vector[0];
        space_travel.ST_astronaut_vector.push_back(astronaut);

        // assigning the first commander to the space travel
        Commander commander = commander_vector[0];
        space_travel.ST_commander_vector.push_back(commander);
    }
}

int main()
{
    cout << "Welcome to Universe" << endl;
    cout << "Creation of the universe has begun..." << endl;
    // Addition of a new planets
    vector<Planet> planet_vector;
    Planet earth;
    earth.name = "Earth";
    earth.position_x = 0;
    earth.position_y = 0;
    earth.position_z = 0;
    planet_vector.push_back(earth);

    Planet mars;
    mars.name = "Mars";
    mars.position_x = 5;
    mars.position_y = 15;
    mars.position_z = 25;
    planet_vector.push_back(mars);

    Planet jupiter;
    jupiter.name = "Jupiter";
    jupiter.position_x = 10;
    jupiter.position_y = 20;
    jupiter.position_z = 30;
    planet_vector.push_back(jupiter);

    // Addition of Passengers
    vector<Passenger> passenger_vector;
    Passenger passengers[11];
    for (int i = 0; i < 11; i++)
    {
        passengers[i].name = "Passenger " + to_string(i + 1);
        passengers[i].ID = "P" + to_string(i + 1);
        passengers[i].setTravellerId(passengers[i].ID);
        passengers[i].setValidity(10);
        passenger_vector.push_back(passengers[i]);
    }

    // Addition of astronauts
    Astronaut astronauts[2];
    for (int i = 0; i < 2; i++)
    {
        astronauts[i].name = "Astronaut " + to_string(i + 1);
        astronauts[i].ID = "A" + to_string(i + 1);
        astronauts[i].setTravellerId(astronauts[i].ID);
        astronauts[i].setExperience(5);
        astronaut_vector.push_back(astronauts[i]);
    }

    // Addition of commanders
    Commander commanders[2];
    for (int i = 0; i < 2; i++)
    {
        commanders[i].name = "Commander " + to_string(i + 1);
        commanders[i].ID = "C" + to_string(i + 1);
        commanders[i].setTravellerId(commanders[i].ID);
        commanders[i].setExperience(10);
        commander_vector.push_back(commanders[i]);
    }

    vector<Ticket> ticket_vector;
    cout << "Universe created successfully" << endl;
    cout << "----------------------------------------" << endl;
    cout << " $$$ This universe has been created with 3 planets, 11 passengers, 2 astronauts and 2 commanders $$$ " << endl;
    cout << "----------------------------------------" << endl;

    // Start of the System interaction
    char response = 'y';
    while (response == 'y')
    {
        cout << "    Welcome to the Space Travel System" << endl;
        cout << "----------------------------------------" << endl;
        cout << "1. Book a ticket" << endl;
        cout << "2. Cancel a ticket" << endl;
        cout << "3. View a ticket" << endl;
        cout << "4. Update ticket details" << endl;
        cout << "5. Add a new passenger" << endl;
        cout << "6. Book a return ticket" << endl;
        cout << "7. Exit" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            // This option is for booking a ticket
            cout << "Welcome to STS Passenger Ticket Booking System" << endl;
            cout << "----------------------------------------" << endl;
            cout << " Please enter your details here: " << endl;

            // if passenger already exists
            cout << "Enter your ID: (P1, P2, P3, etc. upto P11)" << endl;
            string passenger_id;
            cin >> passenger_id;
            Passenger passenger;
            int found = 0;
            for (int i = 0; i < passenger_vector.size(); i++)
            {
                if (passenger_vector[i].ID == passenger_id)
                {
                    passenger = passenger_vector[i];
                    found = 1;
                    break;
                }
            }
            if (found == 0)
            {
                cout << "Passenger not found" << endl;
                cout << "Please enter in correct format" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;

                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
                // return 0;
            }
            // so we have passenger object now
            // creating traveller object
            cout << "Great! Let's now book your ticket" << endl;
            Traveller traveller;
            traveller.name = passenger.name;
            traveller.ID = passenger.ID;
            traveller.setTravellerId(traveller.ID);
            traveller_vector.push_back(traveller);

            // now we need to create ticket object
            Ticket ticket;
            ticket.traveller_name = passenger.name;
            ticket.traveller_id = passenger.ID;
            cout << "Enter the source station: (Earth, Mars, Jupiter, etc.): ";
            // cin >> ticket.source_station;
            string source;
            string destination;
            cin >> source;
            if (source == "Earth" || source == "earth" || source == "Mars" || source == "mars" || source == "Jupiter" || source == "jupiter")
            {
                // ticket.source_station = source;
                if (source == "Earth" || source == "earth")
                {
                    ticket.source_station = "Earth";
                }
                else if (source == "Mars" || source == "mars")
                {
                    ticket.source_station = "Mars";
                }
                else
                {
                    ticket.source_station = "Jupiter";
                }
            }
            else
            {
                cout << "Please enter in correct format" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;

                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            if (source == "Earth" || source == "earth")
            {
                cout << "You can travel to Mars or Jupiter" << endl;
                cout << "Enter your destination: " << endl;
                cin >> destination;
                if (destination == "Mars" || destination == "mars" || destination == "Jupiter" || destination == "jupiter")
                {
                    // ticket.destination_station = destination;
                    if (destination == "Mars" || destination == "mars")
                    {
                        ticket.destination_station = "Mars";
                    }
                    else
                    {
                        ticket.destination_station = "Jupiter";
                    }
                }
                else
                {
                    cout << "Please enter in correct format" << endl;
                    cout << "Do you want to begin again?[yes/no]: " << endl;
                    string choice;
                    cin >> choice;

                    if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                    {
                        response = 'y';
                        continue;
                    }
                    else
                        break;
                }
            }
            else if (source == "Mars" || source == "mars")
            {
                cout << "You can travel to Earth or Jupiter" << endl;
                cout << "Enter your destination: " << endl;
                cin >> destination;
                if (destination == "Earth" || destination == "earth" || destination == "Jupiter" || destination == "jupiter")
                {
                    // ticket.destination_station = destination;
                    if (destination == "Earth" || destination == "earth")
                    {
                        ticket.destination_station = "Earth";
                    }
                    else
                    {
                        ticket.destination_station = "Jupiter";
                    }
                }
                else
                {
                    cout << "Please enter in correct format" << endl;
                    cout << "Do you want to begin again?[yes/no]: " << endl;
                    string choice;
                    cin >> choice;

                    if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                    {
                        response = 'y';
                        continue;
                    }
                    else
                        break;
                }
            }
            else if (source == "Jupiter" || source == "jupiter")
            {
                cout << "You can travel to Earth or Mars" << endl;
                cout << "Enter your destination: " << endl;
                cin >> destination;
                if (destination == "Earth" || destination == "earth" || destination == "Mars" || destination == "mars")
                {
                    // ticket.destination_station = destination;
                    if (destination == "Earth" || destination == "earth")
                    {
                        ticket.destination_station = "Earth";
                    }
                    else
                    {
                        ticket.destination_station = "Mars";
                    }
                }
                else
                {
                    cout << "Please enter in correct format" << endl;
                    cout << "Do you want to begin again?[yes/no]: " << endl;
                    string choice;
                    cin >> choice;

                    if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                    {
                        response = 'y';
                        continue;
                    }
                    else
                        break;
                }
            }

            cout << "Great!! Now enter the date of travel: " << endl;

            cout << "Enter the year: " << endl;
            int year;
            // cin >> ticket.date.year;
            cin >> year;
            if (year >= 2023)
            {
                ticket.date.year = year;
            }
            else
            {
                cout << "Please enter in correct format/Only 2023 or future year is accepted" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;

                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            cout << "Enter the month: {1 to 12 in number}: " << endl;
            int month;
            // cin >> ticket.date.month;
            cin >> month;
            if (month >= 1 && month <= 12)
            {
                ticket.date.month = month;
            }
            else
            {
                cout << "Please enter in correct format/1 to 12 is allowed" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;

                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }

            cout << "Enter the day: " << endl;
            int day;
            // cin >> ticket.date.day;
            cin >> day;
            if (day >= 1 && day <= 31)
            {
                ticket.date.day = day;
            }
            else
            {
                cout << "Please enter in correct format/1 to 31 is allowed" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;

                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }

            // Now we need to check if the passenger has enough validity
            if (passenger.getValidity() < 10)
            {
                cout << "Sorry, you do not have enough validity to travel" << endl;
                break;
            }

            // Now setting the price of the ticket
            int ticket_price;
            ticket_price = calculatePrice(ticket.date);
            ticket.setPrice(ticket_price);
            cout << "Your ticket price is: $" << ticket_price << endl;
            cout << "Do you want to continue?[yes/no]: " << endl;
            string choice;
            cin >> choice;
            if ((choice == "no") || (choice == "No") || (choice == "NO") || (choice == "n") || (choice == "N"))
            {
                response = 'y';
                continue;
            }
            ticket_vector.push_back(ticket);
            cout << "Ticket booked successfully" << endl;
            check_space_travel(ticket);
            break;
        }
        case 2:
        {
            // Cancelling a ticket
            cout << " Welcome to STS Ticket Cancellation System" << endl;
            cout << "----------------------------------------" << endl;
            cout << "Enter your ID: (P1, P2, P3, etc. upto P11): " << endl;
            string passenger_id;
            cin >> passenger_id;
            Passenger passenger;
            int found = 0;
            for (int i = 0; i < passenger_vector.size(); i++)
            {
                if (passenger_vector[i].ID == passenger_id)
                {
                    passenger = passenger_vector[i];
                    found = 1;
                    break;
                }
            }
            if (found == 0)
            {
                cout << "Passenger not found" << endl;
                cout << "Please enter in correct format" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            // so we have passenger object now
            Ticket ticket;
            // searching the ticket of the passenger
            int ticket_found = 0;
            int index;
            for (int i = 0; i < ticket_vector.size(); i++)
            {
                if (ticket_vector[i].traveller_id == passenger.ID)
                {
                    ticket = ticket_vector[i];
                    ticket_found = 1;
                    index = i;
                    break;
                }
            }
            if (ticket_found == 0)
            {
                cout << "No ticket found for this passenger" << endl;
                cout << "Please enter in correct ID" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            // Now deleting the ticket
            cout << passenger.name << ", your ticket ID " << ticket.traveller_id << " was booked." << endl;
            cout << "Do you really want to cancel it?[yes/no]: " << endl;
            string choice;
            cin >> choice;
            if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
            {
                ticket_vector.erase(ticket_vector.begin() + index);
                cout << "Ticket cancelled successfully" << endl;
                continue;
            }
            else
            {
                cout << "Ticket not cancelled" << endl;
                continue;
            }
        }

        case 3:
        {
            // this option is to view a ticket
            cout << " Welcome to STS Ticket Viewing System" << endl;
            cout << "----------------------------------------" << endl;
            cout << "Enter your ID: (P1, P2, P3, etc. upto P11): " << endl;
            string passenger_id;
            cin >> passenger_id;
            Passenger passenger;
            int found = 0;
            for (int i = 0; i < passenger_vector.size(); i++)
            {
                if (passenger_vector[i].ID == passenger_id)
                {
                    passenger = passenger_vector[i];
                    found = 1;
                    break;
                }
            }
            if (found == 0)
            {
                cout << "Passenger not found" << endl;
                cout << "Please enter in correct format" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            // so we have passenger object now
            // searching for ticket of this passenger
            Ticket ticket;
            int ticket_count = 0;
            for (int i = 0; i < ticket_vector.size(); i++)
            {
                if (ticket_vector[i].traveller_id == passenger.ID)
                {
                    ticket = ticket_vector[i];
                    ticket_count++;
                    break;
                }
            }
            if (ticket_count == 0)
            {
                cout << "No ticket found for this passenger" << endl;
                cout << "Please enter in correct ID" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            // Now displaying the ticket
            cout<<"you have booked the following ticket:"<<endl;
            int count = 0;
            for (int i = 0; i < ticket_vector.size(); i++)
            {
                if (ticket_vector[i].traveller_id == passenger.ID)
                {
                    ticket = ticket_vector[i];
                    cout<<"Ticket "<<(count+1)<<":"<<endl;
                     cout << "Ticket ID: " << ticket.traveller_id << endl;
                    cout << "Ticket price: $" << ticket.getPrice() << endl;
                    cout << "Source: " << ticket.source_station << endl;
                    cout << "Destination: " << ticket.destination_station << endl;
                    cout << "Date of journey: " << ticket.date.day << "-" << ticket.date.month << "-" << ticket.date.year << endl;
                    cout << "-------------------------------------------" << endl;
                    count++;
                }
            }
           
            continue;
        }
        case 4:
        { // this option is to update the ticket details
            cout << "Welcome to STS Ticket Updating System" << endl;
            cout << "----------------------------------------" << endl;
            cout << "Enter your ID: (P1, P2, P3, etc. upto P11): " << endl;
            string passenger_id;
            cin >> passenger_id;
            Passenger passenger;
            int found = 0;
            for (int i = 0; i < passenger_vector.size(); i++)
            {
                if (passenger_vector[i].ID == passenger_id)
                {
                    passenger = passenger_vector[i];
                    found = 1;
                    break;
                }
            }
            if (found == 0)
            {
                cout << "Passenger not found" << endl;
                cout << "Please enter in correct format" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            // so we have passenger object now
            // searching for ticket of this passenger
            Ticket ticket;
            int ticket_found = 0;
            for (int i = 0; i < ticket_vector.size(); i++)
            {
                if (ticket_vector[i].traveller_id == passenger.ID)
                {
                    ticket = ticket_vector[i];
                    ticket_found = 1;
                    break;
                }
            }
            if (ticket_found == 0)
            {
                cout << "No ticket found for this passenger" << endl;
                cout << "Please enter in correct ID" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            // Now displaying the ticket
            cout << "Your ticket was booked as follows: " << endl;
            cout << "Passenger name: " << passenger.name << endl;
            cout << "Ticket ID: " << ticket.traveller_id << endl;
            cout << "Ticket price: $" << ticket.getPrice() << endl;
            cout << "Source: " << ticket.source_station << endl;
            cout << "Destination: " << ticket.destination_station << endl;
            cout << "Date of journey: " << ticket.date.day << "-" << ticket.date.month << "-" << ticket.date.year << endl;
            cout << "-------------------------------------------" << endl;
            cout << "Enter the new source station: " << endl;
            string new_source;
            cin >> new_source;
            // checking if the source is valid
            int source_found = 0;
            for (int i = 0; i < planet_vector.size(); i++)
            {
                if (planet_vector[i].name == new_source)
                {
                    source_found = 1;
                    break;
                }
            }
            if (source_found == 0)
            {
                cout << "Source station not found" << endl;
                cout << "Please enter in correct format" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }

            cout << "Enter the new destination station: " << endl;
            string new_destination;
            cin >> new_destination;
            // checking if the destination is valid
            int destination_found = 0;
            for (int i = 0; i < planet_vector.size(); i++)
            {
                if (planet_vector[i].name == new_destination)
                {
                    destination_found = 1;
                    break;
                }
            }
            if (destination_found == 0)
            {
                cout << "Destination station not found" << endl;
                cout << "Please enter in correct format" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            // checking if the source and destination are same
            if (new_source == new_destination)
            {
                cout << "Source and destination cannot be same" << endl;
                cout << "Please enter in correct details again!" << endl;
                cout << "Do you want to begin again?[yes/no]: " << endl;
                string choice;
                cin >> choice;
                if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
                {
                    response = 'y';
                    continue;
                }
                else
                    break;
            }
            cout << "Enter the new date of journey" << endl;
            int new_day, new_month, new_year;
            cout << "Enter the year: " << endl;
            cin >> new_year;
            cout << "Enter the month: " << endl;
            cin >> new_month;
            cout << "Enter the day: " << endl;
            cin >> new_day;
            Date new_date;
            new_date.day = new_day;
            new_date.month = new_month;
            new_date.year = new_year;
            // finding previous ticket
            Ticket new_ticket;
            cout << "Great! Do you wish to update the ticket with these details[yes/no]: " << endl;
            string choice;
            cin >> choice;
            if ((choice == "no") || (choice == "No") || (choice == "NO") || (choice == "n") || (choice == "N"))
            {
                continue;
            }

            for (int i = 0; i < ticket_vector.size(); i++)
            {
                if (ticket_vector[i].traveller_id == passenger.ID)
                {
                    new_ticket = ticket_vector[i];
                    break;
                }
            }
            // Updating new ticket
            new_ticket.traveller_id = passenger.ID;
            new_ticket.source_station = new_source;
            new_ticket.destination_station = new_destination;
            new_ticket.date = new_date;
            ticket_vector.push_back(new_ticket);
            cout << "Ticket updated successfully!" << endl;
            cout << "-------------------------------------------" << endl;
            continue;
        }
        case 5:
        { // this option is to add a passenger
            Passenger passenger;
            cout << "Enter the name of the passenger: ";
            cin >> passenger.name;
            passenger.ID = "P" + to_string(passenger_vector.size() + 1);
            cout << "Your generated ID is: " << passenger.ID << endl;
            passenger.setTravellerId(passenger.ID);
            passenger.setValidity(10);
            cout << "Passenger " << passenger.name << " added with ID " << passenger.ID << endl;
            passenger_vector.push_back(passenger);
            cout << "-------------------------------------------" << endl;
            continue;
        }

        case 6:
        { // this option is to book to a return ticket;
            cout<<"Enter the your ID: "<<endl;
            string id;
            cin>>id;
            int found=0;
            // searching for passenger
            Passenger passenger;
            for(int i=0;i<passenger_vector.size();i++){
                if(passenger_vector[i].ID==id){
                    passenger=passenger_vector[i];
                    found=1;
                    break;
                }
            }
            if(found==0){
                cout<<"ID not found"<<endl;
                cout<<"Please enter in correct Detail"<<endl;
                cout<<"Do you want to begin again?[yes/no]: "<<endl;
                string choice;
                cin>>choice;
                if((choice=="yes")||(choice=="Yes")||(choice=="YES")||(choice=="y")||(choice=="Y")){
                    response='y';
                    continue;
                }
                else
                    break;
            }
            // searching for ticket of the passenger
            Ticket ticket;
            int ticket_found=0;
            for(int i=0;i<ticket_vector.size();i++){
                if(ticket_vector[i].traveller_id==id){
                    ticket=ticket_vector[i];
                    ticket_found=1;
                    break;
                }
            }
            if(ticket_found==0){
                cout<<"No previous ticket was found!"<<endl;
                cout<<"You can't book a return ticket."<<endl;
                cout<<"Do you want to begin again?[yes/no]: "<<endl;
                string choice;
                cin>>choice;
                if((choice=="yes")||(choice=="Yes")||(choice=="YES")||(choice=="y")||(choice=="Y")){
                    response='y';
                    continue;
                }
                else
                    break;
            }
            // showing the previous ticket
            cout<<"Your previous ticket details are: "<<endl;
            cout<<"Source: "<<ticket.source_station<<endl;
            cout<<"Destination: "<<ticket.destination_station<<endl;
            cout<<"Date of journey: "<<ticket.date.day<<"/"<<ticket.date.month<<"/"<<ticket.date.year<<endl;
            cout<<"Do you want to book a return ticket for this travel[yes/no]: "<<endl;
            string choice;
            cin>>choice;
            if((choice=="no")||(choice=="No")||(choice=="NO")||(choice=="n")||(choice=="N")){
                continue;
            }
            // creating a new ticket
            cout<<"Enter the return date of journey"<<endl;
            int new_day,new_month,new_year;
            cout<<"Enter the year of return: "<<endl;
            cin>>new_year;
            cout<<"Enter the month of return: "<<endl;
            cin>>new_month;
            cout<<"Enter the day of return: "<<endl;
            cin>>new_day;
            Date new_date;
            new_date.day=new_day;
            new_date.month=new_month;
            new_date.year=new_year;
            Ticket new_ticket;
            new_ticket.traveller_id=passenger.ID;
            new_ticket.source_station=ticket.destination_station;
            new_ticket.destination_station=ticket.source_station;
            new_ticket.date=new_date;
            int price = calculatePrice(new_date);
            new_ticket.setPrice(price);
            ticket_vector.push_back(new_ticket);
            cout<<"Return ticket booked successfully!"<<endl;
            cout<<"-------------------------------------------"<<endl;
            //showing the return ticket
            cout<<"Your return ticket details are: "<<endl;
            cout<<"Source: "<<new_ticket.source_station<<endl;
            cout<<"Destination: "<<new_ticket.destination_station<<endl;
            cout<<"Date of journey: "<<new_ticket.date.day<<"/"<<new_ticket.date.month<<"/"<<new_ticket.date.year<<endl;
            cout<<"Price: $"<<new_ticket.getPrice()<<endl;

            cout<<"-------------------------------------------"<<endl;
            continue;

        }
        case 7:
        {
            cout << "Thank you for using the Space Travel System" << endl;
            cout << "-------------------------------------------" << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice" << endl;
            cout << "Please enter a valid choice(1 to 6)" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "Do you want to begin again?[yes/no]" << endl;
            string choice;
            cin >> choice;
            if ((choice == "yes") || (choice == "Yes") || (choice == "YES") || (choice == "y") || (choice == "Y"))
            {
                response = 'y';
                continue;
            }
            else
                break;
        }
        }
    }
    return 0;
}