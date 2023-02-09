// C++FinalProject.cpp : Defines the entry point for the application.
//


#include <nana/gui.hpp>
#include <nana/gui/detail/general_events.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
//#include <range/v3/all.hpp>
#include <textbox.hpp>
#include "Customers.h"
#include "Vehicle.h"
#include "RentalLocation.h"
#include "Rental.h"
#include <iostream>
#include <array>
#include <string>
#include <algorithm>


int main()
{
    
    using namespace std;
    using namespace nana;
    int amount_to_pay = 0;
    bool isFormClosed = true;
    string numberOfDays = "0";
    string startDate;
    string endDate;
    combox* listOfCustomers;
    combox* listOfVehicles;
    combox* listOfLocations;
    combox* listOfRentals;
    combox* locationList;
    combox* listOfVehiclesGivenOnRental;
    combox* listOfLateCarRentals;
    combox* listOfRentalsOptForm;
    vector<Customer> allCustomers;
    vector<Vehicle> allVehicles;
    vector<RentalLocation> allLocations;
    vector<Rental>allRentals;
    vector<Vehicle>allvehiclesGivenOnRental;
    Customer* selectedCustomer = nullptr;
    Vehicle* selectedVehicle = nullptr;
    RentalLocation* selectedRentalLocation = nullptr;
    RentalLocation* vehicle_location = nullptr;
    Rental* selectedRental = nullptr;
    button* showRentalCars;
    button* lateRentals;
    button* customersRentals;
    //Define a form.
    form fm(rectangle(30, 30, 1600, 600));
    form addingCustomer;
    form removingCustomer;
    form addingVehicles;
    form addingRentalLocations;
    form dates;
    form vehicleNotAvailable;
    form optionForm;
    textbox dayNumberShow{ fm };
    cout << "I am all good!!!" << endl;
    // The GUI of the adding customers
    
    label firstName{ addingCustomer, "<bold blue size=16>First Name: </>" };
    textbox firstField{ addingCustomer };
    label lastName{ addingCustomer, "<bold blue size=16>Last Name: </>" };
    textbox lastNameField{ addingCustomer };
    label streetAddress{ addingCustomer, "<bold blue size=16>Street Address: </>" };
    textbox streetAddressField{ addingCustomer };
    label age{ addingCustomer, "<bold blue size=16>Age: </>" };
    textbox ageField{ addingCustomer };
    button *addButton;
    button cancelButton{ addingCustomer, "Cancel Customer" };
    label preferred{ addingCustomer, "<bold blue size=10>Preferred Customer (YES / NO): </>" };
    textbox preferredField{ addingCustomer };
    firstName.format(true);
    lastName.format(true);
    streetAddress.format(true);
    age.format(true);
    preferred.format(true);
    addingCustomer.div("vert <><<><weight=25% text01><>><><<><weight=25% text02><>><><<><weight=25% text03><>><><<><weight=25% text04><>><><<><weight=25% text05><>><><<><weight=25% text06><>><><<><weight=25% text07><>><><<><weight=25% text08><>><><<><weight=25% text09><>><><<><weight=25% text10><>><><<><weight=40% button01><><weight=40% button02><>><>");
    addingCustomer["text01"] << firstName;
    addingCustomer["text02"] << firstField;
    addingCustomer["text03"] << lastName;
    addingCustomer["text04"] << lastNameField;
    addingCustomer["text05"] << streetAddress;
    addingCustomer["text06"] << streetAddressField;
    addingCustomer["text07"] << age;
    addingCustomer["text08"] << ageField;
    addingCustomer["text09"] << preferred;
    addingCustomer["text10"] << preferredField;
    addingCustomer["button01"] << *(addButton = new button(addingCustomer, "Add Customer"));
    addingCustomer["button02"] << cancelButton;
 
    //..The GUI to create the dates
    label startDateEnter{ dates, "< bold blue size = 16 > Rental Start date </>" };
    textbox startingDate{ dates };
    textbox endingDate{ dates };
    label endDateEnter{ dates, "< bold blue size = 16 > Rental End date </>" };
    button* saveButton;
    dates.div("vert <><<><weight = 80% t1><>><><<><weight = 80% t2><>><><<><weight = 80% t3><>><><<><weight = 80% t4><>><><<><weight = 40% b1><>><>");
    dates["t1"] << startDateEnter;
    dates["t2"] << startingDate;
    dates["t3"] << endDateEnter;
    dates["t4"] << endingDate;
    dates["b1"] << *(saveButton = new button(dates, "OK"));
    startDateEnter.format(true);
    endDateEnter.format(true);
    //The GUI to add the rental locations   
    label locationName{ addingRentalLocations, "< bold blue size = 16 > Location Name : < / >" };
    textbox locationNameField{ addingRentalLocations };
    button addLocationButton{ addingRentalLocations, "Add Location" };
    button cancelLocationButton{ addingRentalLocations, "Cancel Location" };
    locationName.format(true);
    addingRentalLocations.div("vert <><<><weight=80% text01><>><><<><weight=80% text02><>><><<><weight=40% button01><><weight=40% button02><>><>");
    addingRentalLocations["text01"] << locationName;
    addingRentalLocations["text02"] << locationNameField;
    addingRentalLocations["button01"] << addLocationButton;
    addingRentalLocations["button02"] << cancelLocationButton;

    //THe GUI to show the optionFOrm
    optionForm.div("vert <><<><weight=20% showRC><><weight=50% listOfCarsRented><>><><<><weight=20% lateRC><><weight=50% lateCRentals><>><><<><weight=20% customersRentals><><weight=50% customers><>><>");
    optionForm["showRC"] << *(showRentalCars = new button(optionForm, "SHOW RENTED CARS"));
    optionForm["lateRC"] << *(lateRentals = new button(optionForm, "SHOW LATE CAR RENTALS"));
    optionForm["customersRentals"] << *(customersRentals = new button(optionForm, "SHOW CUSTOMERS"));
    optionForm["listOfCarsRented"] << *(listOfVehiclesGivenOnRental = new combox(optionForm));
    optionForm["lateCRentals"] << *(listOfLateCarRentals = new combox(optionForm));
    optionForm["customers"] << *(listOfRentalsOptForm = new combox(optionForm));
    //The GUI to add the vehicles
    label vehicleName{ addingVehicles, "<bold blue size=16>Vehicle Name: </>" };
    textbox vehicleNameField{ addingVehicles };
    label locationListName{ addingVehicles, "<bold blue size=16>Vehicle Name: </>" };
    
    button addVehicleButton{ addingVehicles, "Add Vehicle" };
    button cancelVehicleButton{ addingVehicles, "Cancel Vehicle" };
    vehicleName.format(true);
    addingVehicles.div("vert <><<><weight=80% textV01><>><><<><weight=80% textV02><>><><<><weight=80% textV03><>><><<><weight=80% locationlist><>><><<><weight=40% buttonV01><><weight=40% buttonV02><>><>");
    addingVehicles["textV01"] << vehicleName;
    addingVehicles["textV02"] << vehicleNameField;
    addingVehicles["textV03"] << locationListName;
    addingVehicles["locationlist"] << *(locationList = new combox(addingVehicles));
    addingVehicles["buttonV01"] << addVehicleButton;
    addingVehicles["buttonV02"] << cancelVehicleButton;


    //The GUI to print error message
    label vehNotAvailable{ vehicleNotAvailable, "<bold blue size=20> VEHICLE NOT AVAILABLE FOR RENTAL </>" };
    button* okayButton;
    vehNotAvailable.format(true);
    vehicleNotAvailable.div("vert <><<><weight=70% message><>><><<><weight=30% button><>><>");
    vehicleNotAvailable["message"] << vehNotAvailable;
    vehicleNotAvailable["button"] << *(okayButton = new button(vehicleNotAvailable, "OK"));
    
    okayButton->events().click([&] {
        vehicleNotAvailable.close();
        isFormClosed = true;
        });

    //Define a label and display a text.
    label lab{ fm, "<bold blue size=16>OTTAWA CAR RENTALS</>" };
   
    button addCustomer{ fm, "Add Customer" };
    

    button addVehicle{ fm, "Add Vehicle" };
    
    
    button addLocation{ fm, "Add Location" };
    button* addRental;
    button* returnRental;
    button removeCustomers{ fm, "Remove Customer" };
    button removeLocations{ fm, "Remove Location" };
    button removeVehicles{fm, "Remove Vehicle"};
    button* day;
    button* show;
   
    textbox amountEntered{ fm , "Enter the amount"};
    lab.format(true);

    //increase the day
    


    //Define a button and answer the click event.
    button btn{ fm, "Enter Dates" };
    btn.events().click([&] {
        dates.collocate();
        dates.show();
        saveButton->events().click([&] {
            startingDate.getline(0, startDate);
            endingDate.getline(0, endDate);
            });
        exec();
        });

    //<<><weight=40% button01><><weight=40% button02><>>
    //Layout management
    fm.div("vert <><<><weight=30% text><><weight=30% showB><>><><<><weight=20% customeraddbutton><><weight=20% locationaddbutton><><weight=20% vehicleaddbutton><><weight=20% rentaladdbutton><>><><<><weight=20% customerremovebutton><><weight=20% locationremovebutton><><weight=20% vehicleremovebutton><><weight=20% rentalreturnbutton><>><><<><weight=20% comboxcustomers><><weight=20% comboxlocations><><weight=20% comboxvehicles><><weight=20% comboxrentals><>><><<><weight=20% dayPlus><><weight=20% button><><weight=20% daytext><><weight=20% enteramount><>><>");
    fm["text"] << lab;//<weight=15%<><locationaddbutton><>><>
    fm["customeraddbutton"] << addCustomer;
    fm["button"] << btn;
    fm["vehicleaddbutton"] << addVehicle;
    fm["rentaladdbutton"] << *(addRental = new button(fm,"Add Rental"));
    fm["locationaddbutton"] << addLocation;
    fm["customerremovebutton"] << removeCustomers;
    fm["vehicleremovebutton"] << removeVehicles;
    fm["rentalreturnbutton"] << *(returnRental = new button(fm, "Return Rental"));
    fm["locationremovebutton"] << removeLocations;
    fm["comboxcustomers"] << *(listOfCustomers = new combox(fm));
    fm["comboxvehicles"] << *(listOfVehicles = new combox(fm));
    fm["comboxlocations"] << *(listOfLocations = new combox(fm));
    fm["comboxrentals"] << *(listOfRentals = new combox(fm));
    fm["dayPlus"] << *(day = new button(fm, "Day Plus"));
    fm["daytext"] << dayNumberShow;
    fm["enteramount"] << amountEntered;
    fm["showB"] << *(show = new button(fm, "SHOW"));
    day->events().click([&] {
        int day = stoi(numberOfDays);
        day++;
        numberOfDays = std::to_string(day);
        cout << numberOfDays << endl;
        dayNumberShow.select(true);
        dayNumberShow.del();
        dayNumberShow.append(numberOfDays, true);   
        
        });

    //adding the customer to the UI
    addCustomer.events().click([&] {
        string afirstNameText ;       
        string alastNameText;
        string astreetAddressText;
        string aageText;
        string aPreferredText;
        addingCustomer.collocate();
        addingCustomer.show();    
        addButton->events().click([&] {
            firstField.getline(0, afirstNameText);
            lastNameField.getline(0, alastNameText);
            streetAddressField.getline(0, astreetAddressText);
            ageField.getline(0, aageText);
            preferredField.getline(0, aPreferredText);
            //Customer* c = new Customer(firstNameText, lastNameText, streetAddressText, ageText);
            std::cout << "firstNameText = " + afirstNameText << endl;
            allCustomers.push_back(Customer(afirstNameText, alastNameText, astreetAddressText, aageText, aPreferredText));
            listOfCustomers->push_back(allCustomers.back().toString());
            std::cout << "Customer added \n " << endl;
            //addingCustomer.close();
            });
        cancelButton.events().click([&] {
            addingCustomer.close();
            std::cout << "Customer not added \n" << endl;
            });
        exec();
        //API::modal_window(addingCustomer);
    });

    //adding the rental location to the UI
    addLocation.events().click([&] {
        string locationNameText;
        addingRentalLocations.collocate();
        addingRentalLocations.show();

        addLocationButton.events().click([&] {
            locationNameField.getline(0, locationNameText);
            cout << "rental location = " + locationNameText << endl;
            RentalLocation* r = new RentalLocation(locationNameText);
            allLocations.push_back(RentalLocation(locationNameText));
            listOfLocations->push_back(allLocations.back().toString());
            locationList->push_back(allLocations.back().getLocationName());
            cout << "Location added successfully!\n" << endl;
            });
        cancelLocationButton.events().click([&] {
            addingRentalLocations.close();
            cout << "Location is not added! \n" << endl;
            });
        exec();
        });


    //adding the vehicle to the UI    
    addVehicle.events().click([&] {
        string vehicleNameText;
        string temporaryString;
        addingVehicles.collocate();
        addingVehicles.show();    
       
        locationList->events().selected([&] {
            //auto locationFilter = [&](auto locate) { return locate.toString().compare(txt) == 0; };
            vehicleNameField.getline(0, vehicleNameText);
            std::cout << "vehicle name = " + vehicleNameText << endl;
            auto locationTxt = locationList->text(locationList->option());
            for (auto& locate01 : allLocations)
            {
                cout << "Location chose:- " + (locate01.getLocationName()) << endl;
                if (locate01.getLocationName().compare(locationTxt) == 0) {
                    vehicle_location = &locate01; //store the pointer to the chosen vehicle;
                    cout << "selected location name for the vehicle:- " << locationTxt << endl;
                    cout << "selected location address for the vehicle:- " << vehicle_location << endl;

                }

            }
       
        });
        std::cout << "Going ahead to add the vehicle!\n" << endl;
        addVehicleButton.events().click([&] { 
            
            Vehicle* v = new Vehicle(vehicleNameText, vehicle_location);
          
            allVehicles.push_back(Vehicle(vehicleNameText, vehicle_location));
            
            listOfVehicles->push_back(allVehicles.back().toString());
            std::cout << "Vehicle added successfully!\n" << endl;
        });
        
        
        cancelVehicleButton.events().click([&] {
            addingVehicles.close();
            cout << "Vehicle is not added! \n" << endl;
            });
        exec();
    });

  

    //selecting the customer from the drop down list
    
    listOfCustomers->events().selected([&] {
        

        auto txt = listOfCustomers->text(listOfCustomers->option());
        //auto custFilter = [&](auto cust) { return cust.toString().compare(txt) == 0; };
        for (auto& cust : allCustomers)
        {
            if (cust.toString().compare(txt) == 0) {
                selectedCustomer = &cust; //store the pointer to the chosen customer;
                std::cout << "Selected customer = " << txt << endl;
                std::cout << "Selected Customer:- " << selectedCustomer << endl;
               

            }
        }
    });
    
    
    listOfVehicles->events().selected([&] {
        auto vehicleFilter = [&](auto veh) { return veh.toString().compare(txt) == 0; };

        auto txt = listOfVehicles->text(listOfVehicles->option());
        for (auto& veh : allVehicles)
        {
           
            for (auto& r_veh : allvehiclesGivenOnRental) {
                if (r_veh.toString().compare(txt) == 0) {
                    vehicleNotAvailable.collocate();
                    cout << "Is form closed:- " + isFormClosed << endl;
                    if (isFormClosed == true) {
                        vehicleNotAvailable.show();
                        isFormClosed = false;
                        cout << "Is form closed:- " + isFormClosed << endl;

                    }
                    
                    

                }
            }
            if (veh.toString().compare(txt) == 0) {
                selectedVehicle = &veh; //store the pointer to the chosen vehicle;
                cout << "selected vehicle = " + txt << endl;
                cout << "selected vehicle = " << selectedVehicle << endl;
            }               
        }
        //exec();
    });

    listOfLocations->events().selected([&] {
        auto locationFilter = [&](auto locate) { return locate.toString().compare(txt) == 0; };

        auto txt = listOfLocations->text(listOfLocations->option());
        for (auto& locate : allLocations)
        {
            if (locate.toString().compare(txt) == 0) {
                selectedRentalLocation = &locate; //store the pointer to the chosen vehicle;
                cout << "Selected Location:- " << txt << endl;
                cout << "Selected Location:- " << selectedRentalLocation << endl;

            }
               
        }
    });


    removeCustomers.events().click([&] {
        cout << selectedCustomer << endl;
        listOfCustomers->erase(listOfCustomers->option());
        //std::vector<Customer> vim = allCustomers | ranges::view::remove_if([](int i) {return i == 8; });
        /*for (int i = 0; i < allCustomers.size(); i++) {
            if ((*(&allCustomers[i])).toString().compare((*selectedCustomer).toString())) {
                (&allCustomers)->erase(selectedCustomer);
                cout << "Compared" << endl;
                

            }
        }

        vector<Customer>::iterator new_end;
        new_end = remove_if((allCustomers).begin(), allCustomers.end(), (selectedCustomer));
        for (int i = 0; i < allCustomers.size(); i++) {
            std::cout << allCustomers.at(i).toString() << " " << endl;
        }*/
    });

    removeLocations.events().click([&] {
        cout << selectedRentalLocation << endl;
        listOfLocations->erase(listOfLocations->option());
    });

    removeVehicles.events().click([&] {
        cout << selectedVehicle << endl;
        listOfVehicles->erase(listOfVehicles->option());
    });

    addRental->events().click([&] {
        string amountToPay;
        amountEntered.getline(0, amountToPay);
        amount_to_pay = stoi(amountToPay);
        if (stoi(selectedCustomer->getAge()) <= 25) {
            amount_to_pay = amount_to_pay + ((20 * stoi(amountToPay)) / 100);
        }
        if (selectedCustomer->getPreferredCustomer().compare("YES") == 0) {
            amount_to_pay = amount_to_pay - ((25 * stoi(amountToPay)) / 100);
        }
        Rental* r = new Rental(selectedCustomer, selectedVehicle, startDate, endDate, amount_to_pay);
        allRentals.push_back(Rental(selectedCustomer, selectedVehicle, startDate, endDate, amount_to_pay));
        listOfRentals->push_back(allRentals.back().toString());
        listOfRentalsOptForm->push_back(allRentals.back().toString());
        listOfVehiclesGivenOnRental->push_back((*r->getVehicle()).toString());
        allvehiclesGivenOnRental.push_back((*r->getVehicle()));
        //listOfVehicles->erase(listOfVehicles->option());
        to_string(listOfVehicles->option()) = "";
        cout << "--------RENTAL-------------" << endl;
        cout << r->toString() << endl;
        cout << "Rental added successfully" << endl;
        });

   

    listOfRentals->events().selected([&] {
        auto rentalF = [&](auto locate) { return locate.toString().compare(txt) == 0; };

        auto txt = listOfLocations->text(listOfLocations->option());
        for (auto& rental : allRentals)
        {
            if (rental.toString().compare(txt) == 0) {
                selectedRental = &rental; //store the pointer to the chosen vehicle;
                cout << "Selected Location:- " << txt << endl;
                cout << "Selected Location:- " << selectedRental << endl;

            }

        }
        });

    returnRental->events().click([&] {
        cout << " -----------REMOVING RENTAL-------- \n " + selectedVehicle->toString() << endl;
        cout << selectedVehicle << endl;
        listOfRentals->erase(listOfRentals->option());

        listOfRentalsOptForm = listOfRentals;
        });

    show->events().click([&] {     
        
        optionForm.collocate();
        optionForm.show();

    });

    
    




    fm.collocate();

    //Show the form
    fm.show();

    //Start to event loop process, it blocks until the form is closed.
    exec();
}
