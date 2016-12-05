import string

# Remove pucntuations from the string.
def stripped_str(str):
    return str.translate(str.maketrans('', '', string.punctuation))

# Return the error rate of str2 given str1 as the correct text.
# Penalize extra words generated by the ASR, and the missing words.
# WER = (extra + missing) / (extra + missing + matching)
def error_rate(str1, str2):
    if str2 == '':
        return 1.0 # ASR returns empty string
    split1 = stripped_str(str1).lower().split()
    split2 = stripped_str(str2).lower().split()
    correct_count = 0
    wront_count = 0
    while split1:
        word = split1.pop(0)
        if word in split2:
            wront_count += 1
            split2.remove(word)
            correct_count += 1
    wront_count += len(split2)
    return wront_count / (correct_count + wront_count)

if __name__ == '__main__':
	print(error_rate('God, Yahoo Games has this truly-awful looking Da Vinci Code-themed skin on it\'s chessboard right now.', \
        'the yahoo games has that\'s true i also looking job and she could eat he needs to know and it\'s just bored right now.'))