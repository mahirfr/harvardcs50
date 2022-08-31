from cs50 import get_string


def main():
    
    text = get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = calculate_average(letters, words)
    S = calculate_average(sentences, words)

    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(round(index))}")


def count_letters(text):
    letter = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letter += 1
    return letter

def count_words(text):
    word = 0
    for i in range(len(text)):
        if " " in text[i]:
            word += 1
    word += 1
    return word

def count_sentences(text):
    sentence = 0
    for i in range(len(text)):
        if ("." in text[i]) or ("!" in text[i]) or ("?" in text[i]):
            sentence += 1
    return sentence


def calculate_average(x , y):
    return x / y * 100;


if __name__ == "__main__":
    main()