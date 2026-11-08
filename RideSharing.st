"Ride Sharing System - GNU Smalltalk 3.x"
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance |
    initializeID: anID pickup: aPickup dropoff: aDropoff distance: miles [
        miles < 0 ifTrue: [ self error: 'Distance must be nonnegative' ].
        rideID := anID.
        pickupLocation := aPickup.
        dropoffLocation := aDropoff.
        distance := miles.
        ^self
    ]
    distance [ ^distance ]
    rideType [ self subclassResponsibility ]
    fare [ self subclassResponsibility ]
    rideDetails [
        Transcript
            show: self rideType; show: ' '; show: rideID;
            show: ' | '; show: pickupLocation;
            show: ' -> '; show: dropoffLocation;
            show: ' | '; show: distance printString;
            show: ' miles | Fare: $'; show: self fare printString;
            nl.
    ]
]

Ride subclass: StandardRide [
    rideType [ ^'Standard' ]
    fare [ ^3.0 + (self distance * 2.0) ]
]

Ride subclass: PremiumRide [
    rideType [ ^'Premium ' ]
    fare [ ^6.0 + (self distance * 3.5) ]
]

Object subclass: Driver [
    | driverID name rating assignedRides |
    initializeID: anID name: aName rating: stars [
        (stars < 0 or: [ stars > 5 ]) ifTrue: [ self error: 'Rating must be from 0 to 5' ].
        driverID := anID.
        name := aName.
        rating := stars.
        assignedRides := OrderedCollection new.
        ^self
    ]
    addRide: aRide [ assignedRides add: aRide ]
    getDriverInfo [
        Transcript show: 'Driver '; show: driverID; show: ': '; show: name;
            show: ' | Rating: '; show: rating printString;
            show: '/5 | Completed rides: '; show: assignedRides size printString; nl.
    ]
]

Object subclass: Rider [
    | riderID name requestedRides |
    initializeID: anID name: aName [
        riderID := anID.
        name := aName.
        requestedRides := OrderedCollection new.
        ^self
    ]
    requestRide: aRide [ requestedRides add: aRide ]
    viewRides [
        Transcript show: 'Ride history for '; show: name;
            show: ' ('; show: riderID; show: '):'; nl.
        requestedRides do: [:ride | ride rideDetails ].
    ]
]

Eval [
    | standard premium rides driver rider |
    standard := (StandardRide new)
        initializeID: 'R101' pickup: 'Station' dropoff: 'Library' distance: 5.0.
    premium := (PremiumRide new)
        initializeID: 'R102' pickup: 'Airport' dropoff: 'Hotel' distance: 8.0.
    rides := OrderedCollection with: standard with: premium.
    Transcript show: '=== Polymorphic ride list ==='; nl.
    rides do: [:ride | ride rideDetails ].
    driver := (Driver new) initializeID: 'D201' name: 'Jordan' rating: 4.8.
    driver addRide: standard.
    driver addRide: premium.
    Transcript nl; show: '=== Driver ==='; nl.
    driver getDriverInfo.
    rider := (Rider new) initializeID: 'U301' name: 'Taylor'.
    rider requestRide: standard.
    rider requestRide: premium.
    Transcript nl; show: '=== Rider ==='; nl.
    rider viewRides.
]
