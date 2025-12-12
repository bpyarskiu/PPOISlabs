README: Система управления туристической компанией (Tourism Management System)

    Классы: 51

    Поля: 185

    Методы: 315

    Исключения: 12

Исключения (12)

Все в классе CustomExceptions.hpp:

    PaymentProcessingException

    CurrencyConversionException

    VisaProcessingException

    GuideNotAvailableException

    TransportNotAvailableException

    DataValidationException

    ResourceNotFoundException

    DatabaseConnectionException

    AuthorizationException

    BookingConflictException

    InvalidDateException

    NetworkCommunicationException

Классы

Формат: Класс Поля Методы → Ассоциации (классы как поля/параметры)

Client 6 10 → Person, Discount, Passport

    Поля: clientId, preferences, discount, passport, + поля от Person

    Методы: getClientId, getPreferences, getDiscount, getPassport, setDiscount, setPassport, applyDiscountToPrice, hasValidPassport, displayClientInfo, getFullName

Employee 3 4 → Person

    Поля: employeeId, position, salary, + поля от Person

    Методы: getEmployeeId, getPosition, getSalary, displayInfo (pure virtual)

HumanResources 3 7 → Employee

    Поля: hrSpecializations, recruitedEmployees, recruitmentBonus, + поля от Employee

    Методы: getHrSpecializations, getRecruitedEmployees, getRecruitmentBonus, addHrSpecialization, calculateTotalBonus, displayInfo, display

Consultant 3 7 → Employee

    Поля: specializationAreas, successfulBookings, commissionRate, + поля от Employee

    Методы: getSpecializationAreas, getSuccessfulBookings, getCommissionRate, addSpecializationArea, calculateCommission, displayInfo, display

Manager 3 7 → Employee

    Поля: responsibilities, teamSize, performanceBonus, + поля от Employee

    Методы: getResponsibilities, getTeamSize, getPerformanceBonus, addResponsibility, calculateTotalCompensation, displayInfo, display

Supporter 4 9 → Employee, SupportLevel

    Поля: supportLevel, supportedLanguages, resolvedTickets, satisfactionRating, + поля от Employee

    Методы: getSupportLevel, getSupportedLanguages, getResolvedTickets, getSatisfactionRating, addSupportedLanguage, resolveTicket, displayInfo, getSupportLevelString, display

Driver 5 10 → Employee, License

    Поля: licenseCategory, permittedVehicleTypes, drivingExperience, safetyRating, license, + поля от Employee

    Методы: getLicenseCategory, getPermittedVehicleTypes, getDrivingExperience, getSafetyRating, getLicense, setLicense, hasValidLicense, canDriveVehicle, completeTrip, displayInfo

Guide 4 9 → Employee

    Поля: languages, specializations, experienceYears, rating, + поля от Employee

    Методы: getLanguages, getSpecializations, getExperienceYears, getRating, addLanguage, addSpecialization, speaksLanguage, displayInfo, display

Company 10 28 → Address, Employee, Client, Tour, Booking, Accommodation, Equipment, Complaint

    Поля: name, foundationYear, headquarters, employees, clients, tours, bookings, accommodations, equipment, complaints

    Методы: getName, getFoundationYear, getHeadquarters, getEmployees, getClients, getTours, getBookings, getAccommodations, getEquipment, getComplaints, addEmployee, addClient, addTour, addBooking, addAccommodation, addEquipment, addComplaint, resolveComplaint, findEquipment, displayCompanyInfo, displayAllEquipment, displayAllAccommodations, displayPendingComplaints

Booking 5 6 → Client, Tour, Employee

    Поля: bookingId, bookingDate, client, tour, manager

    Методы: getBookingId, getBookingDate, getClient, getTour, getManager, displayBookingInfo

Tour 11 20 → Price, DateRange, Accommodation, Transport, Review, Insurance, MealPlan

    Поля: tourId, name, destination, basePrice, dateRange, accommodations, transports, reviews, insurance, mealPlan

    Методы: getTourId, getName, getDestination, getBasePrice, getDateRange, getAccommodations, getTransports, getReviews, getInsurance, getMealPlan, addAccommodation, addTransport, addReview, setInsurance, setMealPlan, calculateTotalPrice, getAverageRating, isActive, displayTourInfo, displayReviews, getTourDurationDays

Transport 4 8 → Price

    Поля: transportId, type, description, price

    Методы: getTransportInfo, calculatePrice, getTransportId, getType, getDescription, getPrice, displayTransportInfo

Flight 5 12 → Transport, Route

    Поля: flightNumber, airline, route, hasMeal, baggageAllowance, + поля от Transport

    Методы: getTransportInfo, calculatePrice, getFlightNumber, getAirline, getRoute, getHasMeal, getBaggageAllowance, displayTransportInfo, getType, getTransportId, getDescription, getPrice

BusRide 6 11 → Transport, Route

    Поля: busNumber, company, route, hasWC, hasAirConditioning, capacity, + поля от Transport

    Методы: getTransportInfo, calculatePrice, displayTransportInfo, getBusNumber, getCompany, getRoute, getHasWC, getHasAirConditioning, getCapacity, getType, getTransportId, getDescription, getPrice

Excursion 6 12

    Поля: excursionId, title, description, city, durationHours, pricePerPerson

    Методы: getExcursionId, getTitle, getDescription, getCity, getDurationHours, getPricePerPerson, setExcursionId, setTitle, setDescription, setCity, setDurationHours, setPricePerPerson

Accommodation 8 11 → Address, Coordinates, Price, Rating, AccommodationType

    Поля: accommodationId, name, address, coordinates, type, pricePerNight, rating, capacity

    Методы: getAccommodationId, getName, getAddress, getCoordinates, getType, getPricePerNight, getRating, getCapacity, addRatingVote, calculateTotalCost, getTypeString, displayAccommodationInfo

Price 2 7

    Поля: amount, currency

    Методы: getAmount, getCurrency, add, multiply, display, validateAmount, validateCurrency

Route 3 6

    Поля: startPoint, endPoint, distanceKm

    Методы: getStartPoint, getEndPoint, getDistanceKm, getRouteDescription, setDistanceKm, displayRouteInfo

BusRoute 3 6 → Route, BusStop

    Поля: routeName, mainRoute, stops

    Методы: addStop, displayRouteInfo, getTotalStops, getTotalStopTime, listAllStops

BusStop 4 7

    Поля: name, location, stopDuration, sequenceNumber

    Методы: getName, getLocation, getStopDuration, getSequenceNumber, displayStopInfo, isLongStop, getStopSummary

MealPlan 3 5 → Price

    Поля: type, pricePerDay, description

    Методы: getType, getPricePerDay, getDescription, calculateTotalCost, display

Insurance 4 5 → Price, Duration

    Поля: type, price, coverage, duration

    Методы: getType, getPrice, getCoverage, getDuration, display

VisaService 9 13 → Client, VisaType, VisaStatus

    Поля: visaId, client, destinationCountry, type, status, applicationDate, decisionDate, serviceFee, requirements

    Методы: getVisaId, getClient, getDestinationCountry, getType, getStatus, getApplicationDate, getDecisionDate, getServiceFee, getRequirements, applyForVisa, approveVisa, rejectVisa, isVisaRequired, getProcessingDays, displayVisaInfo

PaymentSystem 0 2 → PaymentDetails, PaymentResult

    Поля: (нет)

    Методы: processPayment, generateTransactionId

CurrencyConverter 2 15 → CurrencyPair, Currency

    Поля: exchangeRates, baseCurrency

    Методы: setExchangeRate (2), getExchangeRate (2), updateRatesFromAPI, convert, convertToBase, convertFromBase, getCurrencySymbol, getCurrencyName, displayAllRates, hasExchangeRate, removeExchangeRate, clearAllRates

Statistics 1 9 → Company

    Поля: company

    Методы: getTotalClients, getTotalEmployees, getActiveTours, getAverageTourRating, getToursByDestination, getEquipmentCount, getResolvedComplaintsCount, displaySummary, displayTourStatistics

ReportGenerator 5 15 → Company, Booking, PaymentSystem, Driver, ServerStatus, ReportType

    Поля: company, type, startDate, endDate, serverStatus

    Методы: getCompany, getType, getStartDate, getEndDate, generateFinancialReport, generateBookingStatisticsReport, generateClientActivityReport, generateTourPerformanceReport, generateEmployeePerformanceReport, generateDriverWaybill, generateAllReports, displayReportSummary, checkSystemStatus, calculateTotalRevenueInPeriod, validateReportPeriod

NotificationManager 1 7 → Company

    Поля: company

    Методы: sendTourReminders, sendPaymentReminders, sendSpecialOffers, sendSystemMaintenanceNotice, sendBirthdayGreetings, sendAllNotifications, getClientEmails, generateTourReminderMessage, generateSpecialOfferMessage

NotificationService 6 12 → Client, Booking, NotificationType

    Поля: notificationId, client, type, message, sentDate, isRead

    Методы: getNotificationId, getClient, getType, getMessage, getSentDate, getIsRead, sendNotification, markAsRead, markAsUnread, getNotificationTitle, displayNotification, sendBookingConfirmation, sendPaymentReminder, sendTourReminder

BackupManager 2 6 → Company

    Поля: company, backupDirectory

    Методы: createBackup, listBackups, restoreBackup, getBackupFiles, generateBackupFileName

Logger 2 8 → LogLevel

    Поля: logFileName, consoleOutput

    Методы: log, info, warning, error, setConsoleOutput, getCurrentTime, levelToString, writeToFile

Department 4 11 → Employee

    Поля: departmentId, name, budget, employees

    Методы: getDepartmentId, getName, getBudget, getEmployees, setDepartmentId, setName, setBudget, addEmployee, removeEmployee, findEmployeeById, calculateTotalSalary, isBudgetExceeded

Validator 0 12

    Поля: (статический класс)

    Методы: isValidEmail, isValidPhone, isValidName, isValidPrice, isValidRating, isValidId, validateEmail, validatePhone, validateName, validatePrice, validateRating, validateId

Person 4 7 → ContactInfo

    Поля: id, firstName, lastName, contact

    Методы: getId, getFirstName, getLastName, getContactInfo, getFullName, display, validateName

ContactInfo 2 6

    Поля: email, phone

    Методы: getEmail, getPhone, isValidEmail, isValidPhone, display, validateEmail, validatePhone

Address 4 5

    Поля: street, city, country, postalCode

    Методы: getStreet, getCity, getCountry, getPostalCode, getFullAddress, display, validateAddressComponents

Coordinates 2 7

    Поля: latitude, longitude

    Методы: getLatitude, getLongitude, calculateDistance, isValid, display, validateLatitude, validateLongitude

DateRange 2 5

    Поля: startDate, endDate

    Методы: getStartDate, getEndDate, getDurationDays, isDateInRange, displayDateRange

Duration 1 6

    Поля: hours

    Методы: getHours, getDays, addHours, getFormatted, display, validateHours

CurrencyPair 2 7 → Currency

    Поля: from, to

    Методы: getFrom, getTo, operator==, toString, getReversePair, Hash::operator()

Rating 2 6

    Поля: value, votesCount

    Методы: getValue, getVotesCount, addVote, isValid, display, validateVote

Review 4 7

    Поля: author, rating, comment, date

    Методы: getAuthor, getRating, getComment, getDate, isPositive, display, validateRating

Discount 2 7

    Поля: percentage, description

    Методы: getPercentage, getDescription, calculateDiscountedPrice, isValid, display, validatePercentage, validatePrice

License 3 6

    Поля: number, category, expirationDate

    Методы: getNumber, getCategory, getExpirationDate, isValid, canDriveCategory, display, validateNumber

Passport 3 5

    Поля: number, nationality, expirationDate

    Методы: getNumber, getNationality, getExpirationDate, isValid, display, validateNumber, validateDate

Equipment 3 8

    Поля: name, condition, quantity

    Методы: getName, getCondition, getQuantity, use, repair, addQuantity, isUsable, display, validateQuantity

Complaint 4 7

    Поля: title, description, status, date

    Методы: getTitle, getDescription, getStatus, getDate, resolve, escalate, isResolved, display

ServerStatus 3 8

    Поля: serverName, websiteUrl, simulateDelay

    Методы: checkServerStatus, checkWebsiteStatus, checkDatabaseStatus, systemReady, startServices, stopServices, getServerName, getWebsiteUrl

CustomExceptions (Вспомогательный класс)

    Методы: Конструкторы для 12 классов исключений.
