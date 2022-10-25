#include<iostream>
#include<ctime> 
#include<vector>

using namespace std;

static int count = 0;

class Customer
{
    string name;
    string phone;
    public:
        Customer()
        {
            cin.ignore(); 
            cout<<"Enter name: ";
            getline(cin,name);
            cout<<"Enter phone number: ";
            getline(cin,phone);
        }
        string getName()
        {
            return name;
        }
        string getPhone()
        {
            return phone;
        }
};

class Vehicle:public Customer
{
    string carNo;
    int slotNo, ticketNo, billNo, charges;
    time_t entryTime, exitTime;
    public:
        void getTicket(int slot)
        {
            slotNo=slot;
            cout<<"Enter car number: ";
            getline(cin,carNo);
            entryTime = time(0);
            count++;
            string t = ctime(&entryTime);
            ticketNo = count;
            system("cls"); // To clear the screen in Visual C++ ,utilize the code
            displayTicket();
        }
        void displayTicket()
        {
            cout<<"******** XYZ CAR PARKING TICKET ********";
            cout<<"\n\nTicket number: "<<ticketNo;
            cout<<"\nCar Number: "<<carNo;
            cout<<"\nEntry Time: "<<ctime(&entryTime);
            cout<<"\nParking Spot: "<<slotNo;
            cout<<"\nCurrent Status: UNPAID";
            cout<<"\n\nEnter any key to go back to main menu..";
            char c = getchar();
            system("cls");
        }
        void getBill() 
        {
            exitTime = time(0);
            billNo = ticketNo;
            calculateCharges();
        }
        int getTicketNo()
        {
            return ticketNo;
        }
        int getSlot()
        {
            return slotNo;
        }
        void calculateCharges()
        {
            long long duration = exitTime-entryTime;
            int mins = duration/60;
            int hours = mins/60;
            int extra_min = mins%60;
            if(hours==0 && extra_min<=30)
                charges = 20;
            else if(hours<=2 && extra_min==0)
                charges = 55;
            else if(hours<=7)
                charges = 55 + (hours-2)*10;
            else
                charges = 165;
            displayBill();
        }
        void displayBill()
        {
            cout<<"******** XYZ CAR PARKING BILL ********";
            cout<<"\n\nBill Number: "<<billNo;
            cout<<"\nCar Number: "<<carNo;
            cout<<"\nParking Spot: "<<slotNo;
            cout<<"\nEntry Time: "<<ctime(&entryTime);
            cout<<"\nExit Time: "<<ctime(&exitTime);
            cout<<"\nTotal Charges: Rs. "<<charges<<"/-";
            cout<<"\nCurrent Status: PAID";
            cout<<"\n\nEnter any key to go back to main menu..";
            char c = getchar();
        }

};

class ParkingLot
{
    int capacity;
    int totalFilled;
    vector<bool> parkingSpaces;
    vector<Vehicle> v;
    public:
        ParkingLot()
        {
            capacity = 100;
            totalFilled = 0;
            for(int i=0;i<capacity;++i)
                parkingSpaces.push_back(false);
        }
        bool ifSlotAvailable()
        {
            if(totalFilled==capacity)
                return false;
            else
                return true;
        }
        int getFreeSlot()
        {
            for(int i=0;i<capacity;++i)
            {
                if(parkingSpaces[i]==false)
                {
                    parkingSpaces[i]=true;
                    totalFilled++;
                    return i+1;
                }
            }
            return -1;
        }
        void newVehicle(Vehicle& x)
        {
            v.push_back(x);
        }
        void deleteVehicle(int slot)
        {
            parkingSpaces[slot-1] = false;
            totalFilled--;
        }
        Vehicle findDepartingCar(int t) // t = ticket number
        {
            for(int i=0;i<v.size();++i)
            {
                int s = v[i].getTicketNo();
                if(t == s)
                    return v[i];
            }
            return v[0];
        }
        int getCapacity()
        {
            return capacity;
        }
        int getTotalFilled()
        {
            return totalFilled;
        }
        void emptyParkingSpotsList() 
        {
            for(int i=0;i<parkingSpaces.size();++i)
            {
                if(parkingSpaces[i]==false)
                    cout<<i+1<<", ";
            }
        }
        void occupiedParkingSpotsList() // gives the list of occupied parking slots
        {
            for(int i=0;i<parkingSpaces.size();++i)
            {
                if(parkingSpaces[i]==true)
                    cout<<i+1<<", ";
            }
        }
};


void carArrival(ParkingLot& pl)
{
    if(pl.ifSlotAvailable())
    {
        int slot = pl.getFreeSlot();
        Vehicle obj;
        obj.getTicket(slot);
        pl.newVehicle(obj); 
    }
    else
    {
        cout<<"Sorry no empty parking space available!";
    }
}

void carDeparture(ParkingLot& pl)
{
    int ticketno;
    cout<<"Enter ticket number: ";
    cin>>ticketno;
    cin.ignore();
    Vehicle curr = pl.findDepartingCar(ticketno); 
    pl.deleteVehicle(curr.getSlot());
    system("cls");
    curr.getBill();
}

void displayDetails(ParkingLot& pl)
{
    cout<<"\n\n1. Get the total capacity of Parking Lot";
    cout<<"\n2. Get total number of occupied parking spots";
    cout<<"\n3. Get total number of empty parking spots";
    cout<<"\n4. Get list of empty parking spots";
    cout<<"\n5. Get list of occupied parking spots";
    cout<<"\n6. Get the total number of parkings";
    cout<<"\n7. Exit";
    int choice;
    do
    {
        cout<<"\nEnter your choice: ";
        cin>>choice;
        if(choice<1 || choice>7)
            cout<<"\nInvalid Input";
        else
            break;
    } while(true);
    system("cls");
    int c;
    switch(choice)
    {
        case 1:
            c = pl.getCapacity();
            cout<<"\nThe capacity of parking lot is "<<c;
            break;
        case 2:
            c = pl.getTotalFilled();
            cout<<"\nThe number of occupied parking spots is "<<c;
            break;
        case 3:
            c = pl.getCapacity()-pl.getTotalFilled();
            cout<<"\nThe number of empty parking spots is "<<c;
            break;
        case 4:
            cout<<"\nList of empty parking spots: ";
            pl.emptyParkingSpotsList();
            break;
        case 5:
            cout<<"\nList of occupied parking spots: ";
            pl.occupiedParkingSpotsList();
            break;
        case 6:
            cout<<"\nThe total number of parkings: "<<count;
            break;
        case 7:
            break;
    }
    cin.ignore();
    cout<<"\nEnter any key to return to main menu..";
    char ch = getchar();
}

int main()
{
    ParkingLot pl;
    int choice;
    do
    {   
        system("cls");
        cout<<"********* CAR PARKING MANAGEMENT SYSTEM *********";
        cout<<"\n\n1. Arrival of a car";
        cout<<"\n2. Departure of a car";
        cout<<"\n3. Display details";
        cout<<"\n4. Exit";
        cout<<"\nSelect an option (1,2 or 3): ";
        cin>>choice; 
        system("cls");
        switch(choice)
        {
            case 1:
                carArrival(pl);
                break;
            case 2:
                carDeparture(pl);
                break;
            case 3:
                displayDetails(pl);
                break;
            case 4:
                exit(0);
            default:
                cout<<"Invalid Choice!";
                break;
        }
    } while(true);
    return 0;
}