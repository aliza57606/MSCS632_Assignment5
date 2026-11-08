#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class Ride {
private:
    string rideID, pickupLocation, dropoffLocation;
    double distance;
public:
    Ride(string id, string pickup, string dropoff, double miles)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(miles) {
        if (miles < 0) throw invalid_argument("Distance must be nonnegative");
    }
    virtual ~Ride() = default;
    double getDistance() const { return distance; }
    string getRideID() const { return rideID; }
    virtual string rideType() const = 0;
    virtual double fare() const = 0;
    virtual void rideDetails() const {
        cout << fixed << setprecision(2) << rideType() << " " << rideID
             << " | " << pickupLocation << " -> " << dropoffLocation
             << " | " << distance << " miles | Fare: $" << fare() << '\n';
    }
};

class StandardRide final : public Ride {
public:
    using Ride::Ride;
    string rideType() const override { return "Standard"; }
    double fare() const override { return 3.00 + getDistance() * 2.00; }
};

class PremiumRide final : public Ride {
public:
    using Ride::Ride;
    string rideType() const override { return "Premium "; }
    double fare() const override { return 6.00 + getDistance() * 3.50; }
};

class Driver {
private:
    string driverID, name;
    double rating;
    vector<shared_ptr<Ride>> assignedRides;
public:
    Driver(string id, string driverName, double stars)
        : driverID(id), name(driverName), rating(stars) {
        if (stars < 0 || stars > 5) throw invalid_argument("Rating must be from 0 to 5");
    }
    void addRide(shared_ptr<Ride> ride) { if (!ride) throw invalid_argument("Null ride"); assignedRides.push_back(ride); }
    void getDriverInfo() const {
        cout << fixed << setprecision(1) << "Driver " << driverID << ": " << name
             << " | Rating: " << rating << "/5 | Completed rides: " << assignedRides.size() << '\n';
    }
};

class Rider {
private:
    string riderID, name;
    vector<shared_ptr<Ride>> requestedRides;
public:
    Rider(string id, string riderName) : riderID(id), name(riderName) {}
    void requestRide(shared_ptr<Ride> ride) { if (!ride) throw invalid_argument("Null ride"); requestedRides.push_back(ride); }
    void viewRides() const {
        cout << "Ride history for " << name << " (" << riderID << "):\n";
        for (const auto& ride : requestedRides) ride->rideDetails();
    }
};

int main() {
    auto standard = make_shared<StandardRide>("R101", "Station", "Library", 5.0);
    auto premium = make_shared<PremiumRide>("R102", "Airport", "Hotel", 8.0);
    vector<shared_ptr<Ride>> rides{standard, premium};
    cout << "=== Polymorphic ride list ===\n";
    for (const auto& ride : rides) ride->rideDetails();
    Driver driver("D201", "Jordan", 4.8);
    driver.addRide(standard);
    driver.addRide(premium);
    cout << "\n=== Driver ===\n";
    driver.getDriverInfo();
    Rider rider("U301", "Taylor");
    rider.requestRide(standard);
    rider.requestRide(premium);
    cout << "\n=== Rider ===\n";
    rider.viewRides();
    return 0;
}
