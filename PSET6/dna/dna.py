import csv
import sys


def main():

    if (len(sys.argv) != 3):
        print("Invalid usage")
        sys.exit(1)

    dnaDatabase = []
    dnaSequences = {}
    with open(sys.argv[1]) as file:
        dict = csv.DictReader(file)
        for i in dict:
            dnaDatabase.append(i)

    with open(sys.argv[1]) as file:
        dict = csv.DictReader(file)
        for i in dict:
            dnaSequences = i
            break

    dnaSequence = ""
    with open(sys.argv[2]) as file:
        dnaSequence = file.read()

    matches = {}
    numberKeys = 0
    for keys in dnaSequences.keys():
        if keys != "name":
            match = longest_match(dnaSequence, keys)
            matches[keys] = str(match)
            numberKeys += 1

    for d in dnaDatabase:
        aux = 0
        for keys in matches.keys():
            if matches[keys] == d[keys]:
                aux += 1
            if aux == numberKeys:
                print(d["name"])
    else:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
