-- Keep a log of any SQL queries you execute as you solve the mystery.

--Get description of crime
SELECT description
    FROM crime_scene_reports WHERE year=2023 AND month=7 AND day=28 AND street='Humphrey Street';

--Get interviews transcripts of crime
SELECT name, transcript
    FROM interviews
        WHERE year=2023 AND month=7 AND day=28 AND transcript LIKE '%bakery%';

--Get an idea of what the Bakery security logs table look like
SELECT * FROM bakery_security_logs LIMIT 50;

--Get the license plates numbers from the cars that exited the bakery between 10:15 and 10:25
SELECT license_plate
    FROM bakery_security_logs
        WHERE year=2023 AND month=7 AND hour=10 AND day=28 AND minute>=15 AND minute<=25 AND activity='exit';

--Get an idea of what the atm transactions table looks like
SELECT * FROM atm_transactions LIMIT 50;

--Get the account numbers from the people who performed a withdraw the day of the theft
SELECT account_number
    FROM atm_transactions
        WHERE year=2023 AND month=7 AND day=28 AND transaction_type='withdraw' AND atm_location='Leggett Street';

--Get and idea of what the phone calls table looks like
SELECT * FROM phone_calls limit 50;

--Get the numbers of the people who made a call with duration of less than 1 minute in the day of the theft
SELECT caller
    FROM phone_calls
        WHERE year=2023 AND month=7 AND day=28 AND duration<60;

SELECT receiver
    FROM phone_calls
        WHERE year=2023 AND month=7 AND day=28 AND duration<60;

--Get the earliest possible flight leaving from Fiftyville on 29/07/2023
SELECT flight_id, full_name, hour, minute
    FROM passengers
        JOIN flights ON passengers.flight_id=flights.id
        JOIN airports ON flights.origin_airport_id=airports.id
    WHERE year=2023 AND month=7 AND day=29 AND city='Fiftyville' ORDER BY hour,minute LIMIT 10;

--Get the list of the passports on the first flight
SELECT passport_number
    FROM passengers
        JOIN flights ON passengers.flight_id=flights.id
        JOIN airports ON flights.origin_airport_id=airports.id
    WHERE flight_id=36 AND full_name='Fiftyville Regional Airport';

--Get the name of the city of destination of the first flight
SELECT city
    FROM airports
        JOIN flights ON airports.id=flights.destination_airport_id
            WHERE destination_airport_id IN
                (SELECT destination_airport_id
                    FROM passengers
                        JOIN flights ON passengers.flight_id=flights.id
                        JOIN airports ON flights.origin_airport_id=airports.id
                    WHERE flight_id=36 AND full_name='Fiftyville Regional Airport' LIMIT 1) LIMIT 1;

--Get the possible names and phone numbers of the thief by matching the bank accounts information with the license plates numbers, the account numbers, the phone numbers and the passport numbers
SELECT name, phone_number
    FROM people
        JOIN bank_accounts ON people.id=bank_accounts.person_id
            WHERE license_plate IN
                (SELECT license_plate
                    FROM bakery_security_logs
                        WHERE year=2023 AND month=7 AND hour=10 AND day=28 AND minute>=15 AND minute<=25 AND activity='exit')
            AND account_number IN
                (SELECT account_number
                    FROM atm_transactions
                        WHERE year=2023 AND month=7 AND day=28 AND transaction_type='withdraw' AND atm_location='Leggett Street')
            AND phone_number IN
                (SELECT caller
                    FROM phone_calls
                        WHERE year=2023 AND month=7 AND day=28 AND duration<60)
            AND passport_number IN
                (SELECT passport_number
                    FROM passengers
                        JOIN flights ON passengers.flight_id=flights.id
                        JOIN airports ON flights.origin_airport_id=airports.id
                            WHERE flight_id=36 AND full_name='Fiftyville Regional Airport');

--Get the name of the accomplice by searching for the receiving number of Bruce's call
SELECT name
    FROM people
        WHERE phone_number IN
            (SELECT receiver
                FROM phone_calls
                    WHERE year=2023 AND month=7 AND day=28 AND duration<60 AND caller='(367) 555-5533');
